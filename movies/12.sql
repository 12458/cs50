-- In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Johnny Depp.
-- You may assume that there is only one person in the database with the name Helena Bonham Carter.
SELECT m.title FROM movies m
INNER JOIN stars s ON m.id = s.movie_id
INNER JOIN people p ON p.id = s.person_id
WHERE p.name = 'Johnny Depp' OR p.name = 'Helena Bonham Carter'
GROUP BY m.title
HAVING COUNT(m.title) = 2;