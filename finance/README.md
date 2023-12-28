# C$50 Finance

* [article link](https://cs50.harvard.edu/x/2023/psets/9/finance/)

## TODO
- register
- quote
- buy
- index
- sell
- history
- Personal Touch

## Description
### Background
what it means to buy and sell stocks (i.e., shares of a company), [tutorial](https://www.investopedia.com/articles/basics/06/invest1000.asp).

We’re about to implement C$50 Finance, a web app via which you can manage portfolios of stocks. Not only will this tool allow us to check real stocks’ actual prices and portfolios’ values, it will also let us buy (okay, “buy”) and sell (okay, “sell”) stocks by querying for stocks’ prices.
## instalation
~~~bash
pip install Flask-Session
pip install requests
pip install pytz
~~~

## personal touch
Implement at least one personal touch of your choice:

- Allow users to change their passwords.
- Allow users to add additional cash to their account.
- Allow users to buy more shares or sell shares of stocks they already own via index itself, without having to type stocks symbols manually.
- Require users’ passwords to have some number of letters, numbers, and/or symbols.
- Implement some other feature of comparable scope.

### Data
~~~bash
CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    username TEXT NOT NULL,
    hash TEXT NOT NULL,
    cash NUMERIC NOT NULL DEFAULT 10000.00);
    CREATE TABLE sqlite_sequence(name,seq);
    CREATE UNIQUE INDEX username ON users (username);
~~~

### extra data to store information about the purchases
- trsaction 

~~~bash
CREATE TABLE transactions (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER NOT NULL,
    trans TEXT NOT NULL,
    symbol TEXT NOT NULL,
    price NUMERIC NOT NULL,
    shares NUMERIC NOT NULL,
    total_price NUMERIC NOT NULL,
    date DATETIME NOT NULL);
~~~
- stocks
~~~bash
CREATE TABLE stocks (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER NOT NULL,
    symbol TEXT NOT NULL,
    shares NUMERIC NOT NULL);

SELECT * FROM stocks WHERE user_id = 4 AND symbol = 'h';
INSERT INTO stocks (user_id, symbol, shares) VALUES ({}, '{}', {});
UPDARE stokes SET shares = {} WHERE user_id {};
UPDATE stocks SET shares = {} WHERE user_id {};
SELECT symbol, shares FROM stocks WHERE user_id = {} AND symbol = '{}';
~~~
- not used
    - purchases
    ~~~bash
    CREATE TABLE purchases (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
        user_id INTEGER NOT NULL,
        symbol TEXT NOT NULL,
        price NUMERIC NOT NULL,
        shares NUMERIC NOT NULL,
        total_price NUMERIC NOT NULL,
        date DATETIME NOT NULL);

    INSERT INTO purchases (user_id, symbol, price, shares, total_price, date) VALUES ({}, {}, {}, {}, {}, {});

    UPDATE users SET cash = {} WHERE id = {};

    SELECT SUM(price) FROM purchases WHERE user_id = 4;
    SELECT symbol, price, shares, total_price FROM purchases WHERE user_id = 4;
    ~~~

    - sell
    ~~~bash
    CREATE TABLE sells (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
        user_id INTEGER NOT NULL,
        symbol TEXT NOT NULL,
        price NUMERIC NOT NULL,
        shares NUMERIC NOT NULL,
        total_price NUMERIC NOT NULL,
        date DATETIME NOT NULL);
    ~~~



