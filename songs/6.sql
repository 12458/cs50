-- In 6.sql, write a SQL query that lists the names of songs that are by Post Malone.
SELECT s.name
FROM songs s
     INNER JOIN artists a ON a.id = s.artist_id
WHERE a.name = 'Post Malone';