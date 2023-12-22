# Lab 7: Songs
* [Article link](https://cs50.harvard.edu/x/2023/labs/7/)
* [code](https://symmetrical-guide-9766xv445wjhr4q.github.dev/?autoStart=true&folder=%2Fworkspaces%2F123995767&vscodeChannel=stable)

## description
The challenge ahead of you is to write SQL queries to answer a variety of different questions by selecting data from one or more of these tables. After you do so, you’ll reflect on the ways Spotify might use this same data in their annual [Spotify Wrapped](https://en.wikipedia.org/wiki/Spotify_Wrapped) campaign to characterize listeners’ habits.

## about test
~~~bash
CREATE TABLE songs (
    id INTEGER,
    name TEXT,
    artist_id INTEGER,
    danceability REAL,
    energy REAL,
    key INTEGER,
    loudness REAL,
    speechiness REAL,
    valence REAL,
    tempo REAL,
    duration_ms INTEGER
);
CREATE TABLE artists (
    id INTEGER,
    name TEXT
);
~~~

1. In 1.sql, write a SQL query to list the names of all songs in the database.
    - Your query should output a table with a single column for the name of each song.
2. In 2.sql, write a SQL query to list the names of all songs in increasing order of tempo.
    - Your query should output a table with a single column for the name of each song.
3. In 3.sql, write a SQL query to list the names of the top 5 longest songs, in descending order of length.
    - Your query should output a table with a single column for the name of each song.
4. In 4.sql, write a SQL query that lists the names of any songs that have danceability, energy, and valence greater than 0.75.
    - Your query should output a table with a single column for the name of each song.
5. In 5.sql, write a SQL query that returns the average energy of all the songs.
    - Your query should output a table with a single column and a single row containing the average energy.
6. In 6.sql, write a SQL query that lists the names of songs that are by Post Malone.
    - Your query should output a table with a single column for the name of each song.
    - You should not make any assumptions about what Post Malone’s artist_id is.
7. In 7.sql, write a SQL query that returns the average energy of songs that are by Drake.
    - Your query should output a table with a single column and a single row containing the average energy.
    - You should not make any assumptions about what Drake’s artist_id is.
8. In 8.sql, write a SQL query that lists the names of the songs that feature other artists.
    - Songs that feature other artists will include “feat.” in the name of the song.
    - Your query should output a table with a single column for the name of each song.


### 9. Spotify Wrapped
[Spotify Wrapped](https://en.wikipedia.org/wiki/Spotify_Wrapped) is a feature presenting Spotify users’ 100 most played songs from the past year. In 2021, Spotify Wrapped calculated an “[Audio Aura](https://newsroom.spotify.com/2021-12-01/learn-more-about-the-audio-aura-in-your-spotify-2021-wrapped-with-aura-reader-mystic-michaela/)” for each user, a “reading of [their] two most prominent moods as dictated by [their] top songs and artists of the year.” Suppose Spotify determines an audio aura by looking at the average energy, valence, and danceability of a person’s top 100 songs from the past year. In answers.txt, reflect on the following questions:

If songs.db contains the top 100 songs of one listener from 2018, how would you characterize their audio aura?
Hypothesize about why the way you’ve calculated this aura might not be very representative of the listener. What better ways of calculating this aura would you propose?