SELECT distinct(people.name)
    FROM ratings,directors, people
    WHERE directors.movie_id = ratings.movie_id
    AND people.id = directors.person_id
    AND ratings.rating >= 9.0;