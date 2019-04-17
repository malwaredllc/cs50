import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # get cash remaining for the current user
    users = db.execute("SELECT cash FROM users WHERE user_id = :user_id", user_id=session["user_id"])
    cash = users[0]["cash"]

    # get stocks for current user
    stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0", user_id=session["user_id"])

    # lookup quotes for stocks
    quotes = {stock["symbol"] : lookup(stock["symbol"]) for stock in stocks}

    # display portfolio
    return render_template("portfolio.html", quotes=quotes, stocks=stocks, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # handle POST requests
    if request.method == 'POST':

        # get quote for symbol
        quote = lookup(request.form.get("symbol"))
        price = quote["price"]

        if not quote:
            return apology("invalid symbol", 400)

        # get number of shares
        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                raise Exception
        except:
            return apology("invalid number of shares", 400)

        # get remaining cash balance
        users = db.execute("SELECT cash FROM users WHERE user_id = :user_id", user_id=session["user_id"])
        cash = users[0]["cash"]

        # calculate total cost
        cost = shares * price

        # check if user has sufficient funds for purchase
        if cost > cash:
            return apology("insufficient funds for purchase", 400)

        # purchase shares and update user cash balance
        db.execute("UPDATE users SET cash = cash - :cost WHERE user_id = :user_id", cost=cost, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES(:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"],
                   symbol=request.form.get("symbol"),
                   shares=shares,
                   price=price)

        flash("Purchase was successful.")

        return redirect(url_for("index"))

    # handle GET requests
    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    if request.args.get("username") and len(request.args.get("username")) and db.execute("SELECT * FROM users WHERE user_id = :user_id", user_id=request.args.get("username")):
        return jsonify(True)
    return jsonify(False)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT symbol, shares, price, created_at FROM transactions WHERE user_id = :user_id ORDER BY created_at ASC", user_id=session["user_id"])
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
        rows = db.execute("SELECT * FROM users WHERE user_id = :user_id",
                          user_id=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["user_id"]

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

    # handle POST request
    if request.method == 'POST':

        # get symbol from POST request data and check for error
        if not request.form.get('symbol'):
            return apology("please enter a stock symbol to lookup", 400)

        # lookup quote for symbol
        symbol = lookup(request.form.get('symbol'))

        if not symbol:
            return apology("invalid symbol", 400)

        return render_template("quoted.html", quote=symbol)

    # handle GET request
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # handle POST request
    if request.method == 'POST':

        # check for username
        if not request.form.get("username"):
            return apology("must submit username", 400)

        # check for password
        elif not request.form.get("password"):
            return apology("must submit password", 400)

        # check confirmed password matches
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords do not mach", 400)

        # add new user to database
        new_user_id = db.execute("INSERT INTO users (user_id, hash) VALUES (:user_id, :hash)", user_id=request.form.get("username"), hash=generate_password_hash(request.form.get("password")))

        # return apology message if username is taken
        if not new_user_id:
            return apology("username is taken", 400)

        # create new session for user
        session["user_id"] = new_user_id

        # display successful regisration message
        flash("You have successfully registered!")

        # redirect user to home page
        redirect(url_for("index"))

    # handle GET request
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # handle POST requests
    if request.method == 'POST':

        # get quote for symbol
        quote = lookup(request.form.get("symbol"))
        price = quote["price"]

        # get number of shares
        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                raise ValueError
        except:
            return apology("invalid number of shares", 400)

        # check if user has enough shares to make the sale
        stock = db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id AND symbol = :symbol GROUP BY symbol",
                            user_id=session["user_id"],
                            symbol=request.form.get("symbol"))

        if len(stock) != 1 or stock[0]["total_shares"] <= 0 or stock[0]["total_shares"] < shares:
            return apology("insufficient shares to make sale", 400)

        # get user cash balance
        cash = db.execute("SELECT cash FROM users WHERE user_id = :user_id", user_id=session["user_id"])

        # calculate total price
        total = shares * price

        # sell shares and update user cash balance
        db.execute("UPDATE users SET cash = cash + :price WHERE user_id = :user_id", price=total, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES(:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"],
                   symbol=request.form.get("symbol"),
                   shares=-shares,
                   price=price)

        flash("Sale was successful.")

        return redirect(url_for("index"))

    # handle GET requests
    else:
        stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
                             user_id=session["user_id"])

        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
