import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, strong_password
from datetime import datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get user’s current cash balance along with a grand total
    user_id = int(session.get("user_id"))
    user_cash = db.execute("SELECT cash FROM users WHERE id = {}".format(user_id))[0]['cash']

    # stocks the user owns
    stock_data = db.execute("SELECT symbol, shares FROM stocks WHERE user_id = {};".format(user_id))

    stock_total_value = 0
    for item in stock_data:
        item['price'] = lookup(item['symbol'])['price']
        item['total_price'] = item['price'] * item['shares']
        stock_total_value += item['total_price']
        # Format value as USD.
        item['price'] = usd(item['price'])
        item['total_price'] = usd(item['total_price'])

    return render_template("index.html", user_cash=usd(user_cash), stock_total_value=usd(user_cash + stock_total_value), stock_data=stock_data)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # check statements
        if not symbol or not shares:
            return apology("Blank input")

        result = lookup(symbol)
        if result is None:
            return apology("symbol does not exist")
        if not shares.isdigit():
            return apology("shares is not an integer")
        if int(shares) < 0:
            return apology("shares is not a positive integer")

        # check if the user can afford the number of shares
        user_id = int(session.get("user_id"))
        user_cash = db.execute("SELECT cash FROM users WHERE id = {}".format(user_id))[0]['cash']
        symbol_price = lookup(symbol)['price']
        full_price = symbol_price * int(shares)
        date = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

        if full_price > user_cash:
            return apology("can't afford that number of shars")

        # save the purchases information
        data = "({}, 'buy', '{}', {}, {}, {}, '{}')".format(user_id, symbol, symbol_price, int(shares), full_price, date)
        db.execute("INSERT INTO transactions (user_id, trans, symbol, price, shares, total_price, date) VALUES {};".format(data))

        # change the cash value for the user by reducing the user's payment
        db.execute("UPDATE users SET cash = {} WHERE id = {};".format(user_cash - full_price, user_id))

        # change the stocks by adding the symbol
        if len(db.execute("SELECT * FROM stocks WHERE user_id = {} AND symbol = '{}';".format(user_id, symbol))) < 1:
            db.execute("INSERT INTO stocks (user_id, symbol, shares) VALUES ({}, '{}', {});".format(user_id, symbol, int(shares)))
        else:
            old_shares = db.execute("SELECT shares FROM stocks WHERE user_id = {} AND symbol = '{}';".format(user_id, symbol))[0]['shares']
            db.execute("UPDATE stocks SET shares = {} WHERE user_id = {} AND symbol = '{}';".format(old_shares + int(shares), user_id, symbol))

        return redirect("/")

    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = int(session.get("user_id"))
    data = db.execute("SELECT trans, symbol, price, shares FROM transactions WHERE user_id = {};".format(user_id))
    for item in data:
        item['price'] = usd(item['price'])
    return render_template("history.html", data=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        symbol = request.form.get("symbol")

        # Check statements
        if not symbol:
            return apology("No symbol entered")

        result = lookup(symbol)
        if result is None:
            return apology("No symbol found")

        name = result['name']
        price = result['price']
        symbol = result['symbol']
        return render_template("quoted.html", name=name, price=price, symbol=symbol)

    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Get user's information for the registration
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check statements
        if not username:
            return apology("No username entered")
        
        users_dict = db.execute("SELECT username FROM users")
        users = list()
        for item in users_dict:
            users.append(item['username'])

        if username in users:
            return apology("username already exists")
        if not password or not confirmation:
            return apology("No password entered")
        if not strong_password(password):
            return apology("Not a Strong password")
        if password != confirmation:
            return apology("passwords do not match")

        # save registration information
        _hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES ('{}', '{}');".format(username, _hash))

        return redirect("/")

    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = int(session.get("user_id"))
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # check statements
        if not symbol or not shares:
            return apology("Blank input")

        own_shares = db.execute("SELECT shares FROM stocks WHERE user_id = {} AND symbol = '{}';".format(user_id, symbol))
        if len(own_shares) == 0:
            return apology("symbol does not exist")
        if not shares.isdigit():
            return apology("shares is not an integer")
        if int(shares) < 0:
            return apology("shares is not a positive integer")
        shares = int(shares)
        if shares > own_shares[0]['shares']:
            return apology("too many shares")

        # update the stock
        db.execute("UPDATE stocks SET shares = {} WHERE user_id = {} AND symbol = '{}';".format(own_shares[0]['shares'] - shares, user_id, symbol))

        # update the user's cash
        price = lookup(symbol)['price']
        cash = db.execute("SELECT cash FROM users WHERE id = {};".format(user_id))[0]['cash'] + shares * price
        db.execute("UPDATE users SET cash = {} WHERE id = {};".format(cash, user_id))

        # register the sell information
        date = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        full_price = price * shares
        data = "({}, 'sell', '{}', {}, {}, {}, '{}')".format(user_id, symbol, price, shares, full_price, date)
        db.execute("INSERT INTO transactions (user_id, trans, symbol, price, shares, total_price, date) VALUES {};".format(data))

        return redirect("/")

    else:
        symbols = db.execute("SELECT symbol FROM stocks WHERE user_id = {};".format(user_id))
        return render_template("sell.html", symbols=symbols)


@app.route("/settings", methods=["GET", "POST"])
@login_required
def settings():
    """account settings"""
    user_id = int(session.get("user_id"))
    if request.method == "POST":
        # Get user's information for the registration
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check statements
        if not username:
            return apology("No username entered")
        
        users_dict = db.execute("SELECT username FROM users WHERE id = {};".format(user_id))

        if username != users_dict[0]['username']:
            return apology("wrong username")
        if not password or not confirmation:
            return apology("No password entered")
        if not strong_password(password):
            return apology("Not a Strong password")
        if password != confirmation:
            return apology("passwords do not match")

        # save registration information
        _hash = generate_password_hash(password)
        db.execute("UPDATE users SET hach = '{}' WHERE id = {};".format(_hash, user_id))

        return redirect("/")
    
    else:
        return render_template("settings.html")
    return apology("to do")