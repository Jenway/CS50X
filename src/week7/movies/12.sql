SELECT movies.title
    FROM movies,people,stars
    WHERE movies.id = stars.movie_id
    AND stars.person_id = people.id
    AND people.name="Johnny Depp"
    AND movies.id IN
        (
            SELECT movies.id
            FROM movies, stars, people
            WHERE movies.id = stars.movie_id
            AND people.id = stars.person_id
            AND people.name = "Helena Bonham Carter"
        );