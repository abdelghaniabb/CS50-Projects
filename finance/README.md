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
CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 10000.00);
CREATE TABLE sqlite_sequence(name,seq);
CREATE UNIQUE INDEX username ON users (username);
~~~