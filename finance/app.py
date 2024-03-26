import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
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
    symbols = db.execute("SELECT stock FROM buys WHERE user_id = ? ORDER BY stock", session["user_id"])
    prices = []
    shares = []
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    grandTotal = cash[0]["cash"]
    count = 0
    for symbol in symbols:
        tempshares = db.execute("SELECT shares FROM buys WHERE user_id = ? AND stock = ?",
                                session["user_id"], symbol["stock"])
        shares.append(tempshares[0]["shares"])
        temp = lookup(symbol["stock"])["price"]
        prices.append(temp)
        grandTotal += float(tempshares[0]["shares"]) * float(temp)
        count += 1
    return render_template("index.html", cash=cash[0]["cash"], grandTotal=grandTotal, symbols=symbols, shares=shares, prices=prices, count=count)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        elif not request.form.get("shares"):
            return apology("must provide shares", 400)
        symbol = request.form.get("symbol")
        if not lookup(symbol):
            return apology("symbol not found", 400)
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("must provide integer shares", 400)
        if shares < 0 or shares > 100:
            return apology("must provide valid integer shares", 400)
        price = lookup(symbol)["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        if cash[0]["cash"] - price * shares < 0:
            return apology("must have enough money", 400)
        db.execute(
            "INSERT INTO buys (user_id, shares, stock, price_at_purchase, time_of_purchase) VALUES (?, ?, ?, ?, datetime('now'))",
            session["user_id"], shares, symbol, price
        )
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash[0]["cash"] - price * shares, session["user_id"])
        timeOfPurchase = db.execute("SELECT time_of_purchase FROM buys WHERE user_id = ? AND stock = ?",
                                    session["user_id"], symbol)
        db.execute("INSERT INTO history VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], symbol, shares, price, "buy", timeOfPurchase[0]["time_of_purchase"])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    if not transactions:
        return apology("no transactions made", 400)
    return render_template("history.html", transactions=transactions)


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
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        stockQuote = lookup(request.form.get("symbol"))
        if not stockQuote:
            return apology("must provide valid symbol", 400)
        return render_template("quoted.html", stockQuote=stockQuote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif not request.form.get("confirmation"):
            return apology("must provide password in both places", 400)
        username = request.form.get("username")
        password = request.form.get("password")
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )
        if len(rows) != 0:
            return apology("invalid username", 400)
        if password != request.form.get("confirmation"):
            return apology("passwords don't match", 400)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        elif not request.form.get("shares"):
            return apology("must provide shares", 400)
        symbol = request.form.get("symbol")
        if not lookup(symbol):
            return apology("symbol not found", 400)
        ownedStocks = db.execute("SELECT stock FROM buys WHERE user_id = ?", session["user_id"])
        for ownedStock in ownedStocks:
            if symbol == ownedStock["stock"]:
                break
        else:
            return apology("must provide owned symbol", 400)
        ownedShares = db.execute("SELECT shares FROM buys WHERE user_id = ? AND stock = ?",
                                 session["user_id"], symbol)
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("must provide integer shares", 400)
        if shares < 0 or shares > 100 or shares > ownedShares[0]["shares"]:
            return apology("must provide valid integer shares", 400)
        price = lookup(symbol)["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        priceAtPurchase = db.execute("SELECT price_at_purchase FROM buys WHERE user_id = ? AND stock = ?",
                                     session["user_id"], symbol)
        db.execute("INSERT INTO history VALUES (?, ?, ?, ?, ?, datetime('now'))",
                   session["user_id"], symbol, shares, priceAtPurchase[0]["price_at_purchase"], "sell")
        if shares - ownedShares[0]["shares"] == 0:
            db.execute(
                "DELETE FROM buys WHERE user_id = ? AND shares = ? AND stock = ? AND price_at_purchase = ?",
                session["user_id"], shares, symbol, priceAtPurchase[0]["price_at_purchase"]
            )
        else:
            db.execute(
                "UPDATE buys SET shares = ? WHERE user_id = ? AND shares = ? AND stock = ? AND price_at_purchase = ?",
                ownedShares[0]["shares"] -
                shares, session["user_id"], ownedShares[0]["shares"], symbol, priceAtPurchase[0]["price_at_purchase"]
            )
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   cash[0]["cash"] + price * shares, session["user_id"])
        return redirect("/")
    else:
        ownedStocks = db.execute("SELECT stock FROM buys WHERE user_id = ?", session["user_id"])
        if not ownedStocks:
            return apology("must own shares to sell", 400)
        return render_template("sell.html", ownedStocks=ownedStocks)
