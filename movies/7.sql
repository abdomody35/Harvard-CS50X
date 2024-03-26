--SELECT title, rating FROM movies, ratings
--WHERE year = 2010 AND movies.id = ratings.movie_id
--ORDER BY rating DESC, title;

SELECT title, rating FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2010
ORDER BY rating DESC, title;
