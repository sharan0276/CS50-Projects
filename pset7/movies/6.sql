--write a SQL query to determine the average rating of all movies released in 2012.

SELECT AVG(rating)
FROM ratings JOIN movies on movies.id = ratings.movie_id
WHERE movies.year = 2012;