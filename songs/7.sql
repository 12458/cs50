-- In 7.sql, write a SQL query that returns the average energy of songs that are by Drake.
SELECT AVG(s.energy)
FROM songs s
     INNER JOIN artists a ON a.id = s.artist_id
WHERE a.name = 'Drake';