-- In 8.sql, write a SQL query to list the names of all people who starred in Toy Story.
-- Your query should output a table with a single column for the name of each person.
-- You may assume that there is only one movie in the database with the title Toy Story.
SELECT p.name FROM movies m
INNER JOIN stars s ON m.id = s.movie_id
INNER JOIN people p ON p.id = s.person_id
WHERE m.title = 'Toy Story';