-- In 6.sql, write a SQL query to determine the average rating of all movies released in 2012.
-- Your query should output a table with a single column and a single row (not counting the header) containing the average rating.
SELECT AVG(r.rating) FROM movies m
INNER JOIN ratings r ON r.movie_id = m.id
WHERE m.year = 2012;