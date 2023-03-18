SELECT people.name
    FROM people,stars
    WHERE stars.person_id = people.id
    AND people.name != "Kevin Bacon"
    AND stars.movie_id IN
        (
            SELECT stars.movie_id
            FROM stars, people
            WHERE people.id = stars.person_id
            AND people.name = "Kevin Bacon"
            AND people.birth = 1958
        );