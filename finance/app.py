import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

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
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Require that a user input a stock’s symbol, implemented as a text field whose name is symbol. Render an apology if the input is blank or the symbol does not exist (as per the return value of lookup).
    # Require that a user input a number of shares, implemented as a text field whose name is shares. Render an apology if the input is not a positive integer.
    # Submit the user’s input via POST to /buy.
    # Upon completion, redirect the user to the home page.
    # Odds are you’ll want to call lookup to look up a stock’s current price.
    # Odds are you’ll want to SELECT how much cash the user currently has in users.
    # Add one or more new tables to finance.db via which to keep track of the purchase. Store enough information so that you know who bought what at what price and when.
    # Use appropriate SQLite types.
    # Define UNIQUE indexes on any fields that should be unique.
    # Define (non-UNIQUE) indexes on any fields via which you will search (as via SELECT with WHERE).
    # Render an apology, without completing a purchase, if the user cannot afford the number of shares at the current price.
    # You don’t need to worry about race conditions (or use transactions).

    if request.method == "POST":
        symbol = request.form.get("symbol").strip()
        shares = request.form.get("shares").strip()
        if symbol is None or shares is None:
            return apology("Must provide symbol and shares", 400)
        quote = lookup(symbol)
        if quote is None:
            return apology("Invalid symbol", 400)
        try:
            shares = int(shares)
            assert shares > 0
        except ValueError:
            return apology("Shares must be a positive integer", 400)
        
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        cash = rows[0]["cash"]
        price = quote["price"]
        total = price * shares
        if total > cash:
            return apology("Insufficient funds", 400)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, type, timestamp) VALUES (?, ?, ?, ?, ?, ?)", 
                                        session["user_id"], symbol, shares, price, "BUY", datetime.now())
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total, session["user_id"])
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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    # Require that a user input a stock’s symbol, implemented as a text field whose name is symbol.
    # Submit the user’s input via POST to /quote.
    # Odds are you’ll want to create two new templates (e.g., quote.html and quoted.html). When a user visits /quote via GET, render one of those templates, inside of which should be an HTML form that submits to /quote via POST. In response to a POST, quote can render that second template, embedding within it one or more values from lookup.

    if request.method == "POST":
        symbol = request.form.get("symbol").strip()
        if symbol is None:
            return apology("Must provide symbol", 400)
        quote = lookup(symbol)
        if quote is None:
            return apology("Invalid symbol", 400)
        return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Complete the implementation of register in such a way that it allows a user to register for an account via a form.
    # Require that a user input a username, implemented as a text field whose name is username. Render an apology if the user’s input is blank or the username already exists.
    # Require that a user input a password, implemented as a text field whose name is password, and then that same password again, implemented as a text field whose name is confirmation. Render an apology if either input is blank or the passwords do not match.
    # Submit the user’s input via POST to /register.
    # INSERT the new user into users, storing a hash of the user’s password, not the password itself. Hash the user’s password with generate_password_hash Odds are you’ll want to create a new template (e.g., register.html) that’s quite similar to login.html.

    if request.method == "POST":
        username = request.form.get("username").strip()
        password = request.form.get("password").strip()
        confirmation = request.form.get("confirmation").strip()
        if username is None or password is None or confirmation is None:
            return apology("Must provide username, password and confirmation", 400)
        if password != confirmation:
            return apology("Passwords do not match", 400)
        hash = generate_password_hash(password)
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) > 0:
            return apology("Username already exists", 400)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
