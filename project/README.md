# remote practical experiences

## Backgrand
- if the user didn't have an acount there is a request in witch the user can send a submition request
- send email (not implemented yet)

### Data
~~~bash
CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    username TEXT NOT NULL,
    hash TEXT NOT NULL);

CREATE UNIQUE INDEX username ON users (username);


CREATE TABLE IF NOT EXISTS users_information (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    email TEXT NOT NULL,
    establishment TEXT NOT NULL,
    sector TEXT NOT NULL,
    phone TEXT NOT NULL,
    contry TEXT NOT NULL);

CREATE TABLE IF NOT EXISTS temperature (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    temperature NUMERIC,
    humidity NUMERIC,
    date DATETIME NOT NULL);
~~~