--SELECT songs.name FROM songs
--JOIN artists ON artists.id = songs.artist_id
--WHERE artists.name = 'Post Malone';

SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Post Malone');
