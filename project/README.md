# remote practical experiences

## Backgrand
- if the user didn't have an acount there is a request in witch the user can send a submition request

### Data
~~~bash
CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    username TEXT NOT NULL,
    hash TEXT NOT NULL,
    program TEXT NOT NULL,
    grade NUMERIC NOT NULL DEFAULT 0.00);

CREATE UNIQUE INDEX username ON users (username);
~~~