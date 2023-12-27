import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
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
    # user’s current cash balance along with a grand total 
    user_id = int(session.get("user_id"))
    user_cash = db.execute("SELECT cash FROM users WHERE id = {}".format(user_id))[0]['cash']
    stock_total_value = db.execute("SELECT SUM(price) AS sum FROM purchases WHERE user_id = {};".format(user_id))[0]['sum']

    # stocks the user owns
    stock_data = db.execute("SELECT symbol, price, shares, total_price FROM purchases WHERE user_id = {};".format(user_id))
    
    return render_template("index.html", user_cash=usd(user_cash), stock_total_value=usd(stock_total_value), stock_data=stock_data)
    return apology("--TODO")


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
        data = "({}, '{}', {}, {}, {}, '{}')".format(user_id, symbol, symbol_price, int(shares), full_price, date)
        db.execute("INSERT INTO purchases (user_id, symbol, price, shares, total_price, date) VALUES {};".format(data))

        # change the cash value for the user by reducing the user's payment
        db.execute("UPDATE users SET cash = {} WHERE id = {};".format(user_cash - full_price, user_id))
        
        return redirect("/")
    else:
        return render_template("buy.html")
    


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

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
        if password != confirmation:
            return apology("passwords do not match")

        _hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES ('{}', '{}');".format(username, _hash))
    else:
        return render_template("register.html")

    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        pass
    else:
        return render_template("sell.html")
    return apology("2TODO")
