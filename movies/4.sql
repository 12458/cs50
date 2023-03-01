-- In 4.sql, write a SQL query to determine the number of movies with an IMDb rating of 10.0.
-- Your query should output a table with a single column and a single row (not counting the header) containing the number of movies with a 10.0 rating.
SELECT COUNT(*) FROM movies m
INNER JOIN ratings r ON r.movie_id = m.id
WHERE r.rating = 10.0;