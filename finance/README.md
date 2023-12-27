# C$50 Finance


## TODO
- register
- quote
- buy
- index
- sell
- gistory
- Personal Touch

## Description
### Background
what it means to buy and sell stocks (i.e., shares of a company), [tutorial](https://www.investopedia.com/articles/basics/06/invest1000.asp).

We’re about to implement C$50 Finance, a web app via which you can manage portfolios of stocks. Not only will this tool allow us to check real stocks’ actual prices and portfolios’ values, it will also let us buy (okay, “buy”) and sell (okay, “sell”) stocks by querying for stocks’ prices.


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
