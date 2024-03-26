--SELECT AVG(energy) FROM songs
--JOIN artists ON artists.id = songs.artist_id
--WHERE artists.name = 'Drake';

SELECT AVG(energy) FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Drake');
