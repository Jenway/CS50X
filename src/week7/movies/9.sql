SELECT distinct(people.name)
    FROM movies, stars, people
    WHERE movies.id = stars.movie_id
    AND people.id = stars.person_id
    AND movies.year = 2004
    ORDER BY people.birth;