import os

from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd



# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute(
        "SELECT symbol, name, sum(shares) as sumshares, price FROM history WHERE user_id = ? GROUP BY symbol",
        session["user_id"],
    )
    cash = db.execute("SELECT cash FROM users WHERE id = ?",
                      session["user_id"])
    total = 0
    for item in stocks:
        item["price"] = lookup(item["symbol"])["price"]
        total += float(item["price"])*int(item["sumshares"])
        item["total"] = usd(total)
        item["price"] = usd(float(item["price"]))

    # print(stocks, usd(cash[0]["cash"]))
    total += cash[0]["cash"]
    return render_template("index.html", stocks=stocks, cash=usd(cash[0]["cash"]), total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        shares = request.form.get("shares")
        if not symbol:
            return apology("missing symbol")
        elif not shares:
            return apology("missing shares")
        elif not quote:
            return apology("invalid symbol")
        else:
            try:
                shares = float(shares)
                if not shares or shares <= 0 or not float.is_integer(shares):
                    raise ValueError
            except ValueError:
                return apology("invalid shares")

        row = db.execute("SELECT cash FROM users where id = ?",
                         session["user_id"])
        cash = row[0]["cash"]
        balance = cash - shares * quote["price"]
        if balance < 0:
            return apology("CAN'T AFFORD")

        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"]
        )
        db.execute(
            "INSERT INTO history (user_id, symbol, name,shares, price, timestamp) VALUES (?, ?, ?, ?, ?, ?)",
            session["user_id"],
            symbol.upper(),
            quote["name"],
            shares,
            quote["price"],
            datetime.now(),
        )
        flash("Bought!")
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute(
        "SELECT symbol, shares, price, timestamp FROM history WHERE user_id = ?",
        session["user_id"],
    )
    for item in history:
        item["price"]= usd(item["price"])
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not symbol:
            return apology("missing symbol")
        if not quote:
            return apology("invalid symbol")
        return render_template("quoted.html", quote=quote)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        name = request.form.get("username")
        pass1 = request.form.get("password")
        pass2 = request.form.get("confirmation")
        if not name:
            return apology("Please type in username")
        if not pass1:
            return apology("Please set password")
        if pass1 != pass2:
            return apology("Two password didn't match")
        if db.execute("SELECT * FROM users WHERE username = ?", name):
            return apology("user already exists")

        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            name,
            generate_password_hash(pass1),
        )
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        stocks = db.execute(
            "SELECT symbol FROM history WHERE user_id = ? GROUP BY symbol",
            session["user_id"],
        )
        return render_template("sell.html", stocks=stocks)
    else:
        symbol = request.form.get("symbol")
        m_share = db.execute("SELECT sum(shares) as sumshares FROM history WHERE user_id = ? and symbol =  ?",
                             session["user_id"],
                             symbol,
                             )
        shares = request.form.get("shares")
        if not symbol:
            return apology("missing symbol")
        elif not shares:
            return apology("missing shares")
        elif m_share == 0:
            return apology("invalid symbol")
        else:
            try:
                shares = float(shares)
                if not shares or shares <= 0 or shares > m_share[0]["sumshares"] or not float.is_integer(shares):
                    raise ValueError
            except ValueError:
                return apology("invalid shares")

        row = db.execute("SELECT cash FROM users where id = ?",
                         session["user_id"])
        cash = row[0]["cash"]
        balance = cash + shares * lookup(symbol)["price"]
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"]
        )
        db.execute(
            "INSERT INTO history (user_id, symbol, name,shares, price, timestamp) VALUES (?, ?, ?, ?, ?, ?)",
            session["user_id"],
            symbol.upper(),
            lookup(symbol)["name"],
            -shares,
            lookup(symbol)["price"],
            datetime.now(),
        )
        flash("Sold!")
        return redirect("/")
