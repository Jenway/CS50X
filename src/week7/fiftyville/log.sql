-- Keep a log of any SQL queries you execute as you solve the mystery.

-- All you know is that the theft took place on July 28, 2021
-- and that it took place on Humphrey Street.

-- what had happend?

SELECT *
    FROM crime_scene_reports
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND street = "Humphrey Street";

-- get two reports , id 295 is useful
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

SELECT id,name,transcript
    FROM interviews
    WHERE year = 2021
    AND month =7
    AND day =28;

-- 3 witnesses
/* | 161 | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.  */

/* | 162 | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.  */

/* | 163 | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. | */

-- what we got from witness?
--eraly this morning  thief withdrew money,         ATM on Leggett Street
-- 10:15am            THEFT took place,             Humphrey Street bakery
-- within  a min      thief call accomplice for buying earliest flight out of Fiftyville tomorrow.   Humphrey Street bakery
-- within 10 min      thief drive away              bakery parking lot

SELECT *
    FROM people
    WHERE license_plate
    IN(
        SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND activity ="exit"
    );

-- now we got 9 people exit the bakery possible be the thief

-- let's consider the call

SELECT p.id,p.name,p.phone_number,p.passport_number
    FROM phone_calls as pc,people as p
    WHERE p.phone_number = pc.caller
    AND year =2021
    AND month = 7
    AND day =28
    AND duration < 60
    AND caller IN
    (
        SELECT phone_number
            FROM people
            WHERE license_plate IN
            (
                SELECT license_plate
                FROM bakery_security_logs
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND activity ="exit"
            )
    );

-- and consider the atm

SELECT p.id,p.name,p.passport_number
    FROM phone_calls as pc,people as p,atm_transactions as a,bank_accounts as b
    WHERE p.phone_number = pc.caller
    AND b.person_id = p.id
    AND b.account_number = a.account_number
    AND a.year =2021
    AND a.month =7
    AND a.day = 28
    AND a.atm_location ="Leggett Street"
    AND a.transaction_type = "withdraw"
    AND pc.year =2021
    AND pc.month = 7
    AND pc.day =28
    AND pc.duration < 60
    AND pc.caller IN
    (
        SELECT phone_number
            FROM people
            WHERE license_plate IN
            (
                SELECT license_plate
                FROM bakery_security_logs
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND activity ="exit"
            )
    );
/*
+--------+--------+-----------------+
|   id   |  name  | passport_number |
+--------+--------+-----------------+
| 686048 | Bruce  | 5773159633      |
| 514354 | Diana  | 3592750733      |
| 449774 | Taylor | 1988161715      |
+--------+--------+-----------------+ */

-- now let's consider the flight

SELECT f.id,f.destination_airport_id
    FROM flights as f,airports
    WHERE origin_airport_id = airports.id
    AND airports.city LIKE "%Fiftyville%"
    AND year =2021
    AND month = 7
    AND day =29
    ORDER BY hour,minute
    LIMIT 1;

/*
+----+------------------------+
| id | destination_airport_id |
+----+------------------------+
| 36 | 4                      |
+----+------------------------+ */

SELECT *
    FROM passengers as p
    WHERE p.flight_id =(
        SELECT f.id
            FROM flights as f,airports
            WHERE origin_airport_id = airports.id
            AND airports.city LIKE "%Fiftyville%"
            AND year =2021
            AND month = 7
            AND day =29
            ORDER BY hour,minute
            LIMIT 1
    );

-- now sum them up

SELECT p.id,p.name,p.passport_number
    FROM phone_calls as pc,people as p,atm_transactions as a,bank_accounts as b
    WHERE p.passport_number IN
    (
        SELECT p.passport_number
        FROM passengers as p
        WHERE p.flight_id =(
            SELECT f.id
                FROM flights as f,airports
                WHERE origin_airport_id = airports.id
                AND airports.city LIKE "%Fiftyville%"
                AND year =2021
                AND month = 7
                AND day =29
                ORDER BY hour,minute
                LIMIT 1
            )
    )
    AND p.phone_number = pc.caller
    AND b.person_id = p.id
    AND b.account_number = a.account_number
    AND a.year =2021
    AND a.month =7
    AND a.day = 28
    AND a.atm_location ="Leggett Street"
    AND a.transaction_type = "withdraw"
    AND pc.year =2021
    AND pc.month = 7
    AND pc.day =28
    AND pc.duration < 60
    AND pc.caller IN
    (
        SELECT phone_number
            FROM people
            WHERE license_plate IN
            (
                SELECT license_plate
                FROM bakery_security_logs
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND activity ="exit"
            )
    );


/*
+--------+--------+-----------------+
|   id   |  name  | passport_number |
+--------+--------+-----------------+
| 686048 | Bruce  | 5773159633      |
| 449774 | Taylor | 1988161715      |
+--------+--------+-----------------+
 */
 -- hmm~~ what had i forget ...

 SELECT p.id,p.name,p.phone_number,p.passport_number,b.hour,b.minute
    FROM people as p,bakery_security_logs as b
    WHERE p.license_plate = b.license_plate
    AND b.year = 2021
    AND b.month = 7
    AND b.day = 28
    AND b.hour = 10
    AND (p.id = 686048 OR p.id =449774)
    AND b.activity ="exit";

/*
+--------+--------+----------------+-----------------+------+--------+
|   id   |  name  |  phone_number  | passport_number | hour | minute |
+--------+--------+----------------+-----------------+------+--------+
| 449774 | Taylor | (286) 555-6063 | 1988161715      | 10   | 35     |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 10   | 18     |
+--------+--------+----------------+-----------------+------+--------+
*/

-- hmm, then it should be Bruce because  Taylor exit way too late;

--THE THIEF IS Bruce (id = 686048)

SELECT city
    FROM airports
    WHERE airports.id =(
        SELECT f.destination_airport_id
            FROM flights as f,airports
            WHERE origin_airport_id = airports.id
            AND airports.city LIKE "%Fiftyville%"
            AND year =2021
            AND month = 7
            AND day =29
            ORDER BY hour,minute
            LIMIT 1
    );
-- The city the thief ESCAPED TO: New York City

/*
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+
*/

SELECT *
    FROM people as p
    WHERE p.phone_number =
    (
        SELECT pc.receiver
        FROM phone_calls as pc,people as p
        WHERE p.phone_number = pc.caller
        AND year =2021
        AND month = 7
        AND day =28
        AND duration < 60
        AND caller IN
        (
            SELECT phone_number
                FROM people
                WHERE id=686048
        )
    );

/*
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
+--------+-------+----------------+-----------------+---------------+
*/

-- The ACCOMPLICE is: Robin