import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    #reached via post
    if request.method == "POST":

        #No symbol input
        if request.form.get("symbol") is None:
            return apology("Input a symbol", 403)

        #Invalid shares input
        if request.form.get("shares") <= 0:
            return apology("Invalid number for shares", 403)

        #Lookup and store quote
        quote = lookup(request.form.get("symbol"))

        #symbol doesn't exist
        if quote is None:
            return apology("Symbol doesn't exist", 403)
        else:
            #Search database for matching id
            rows = db.execute("SELECT * FROM users where id = :id",
                              id = session["user_id"])
            money = rows[0]["cash"]

            if request.form.get("shares")*quote["price"] > money:
                return apology("Not enough cash", 403)
            else:
                money = money - request.form.get("shares") * quote["price"]

                #Update user's cash
                db.execute("UPDATE users SET cash = :cash WHERE id = :id",
                            cash = money, id = session["user_id"])

                #Updates history table
                db.execute("INSERT INTO history (id,symbol,shares,price) VALUES(:id,:symbol,:shares,:price)",
                            id = session["user_id"], symbol = request.form.get("symbol"),
                            shares = request.form.get("shares"), price = quote["price"])

                #Adds stocks to users profile
                rows = db.execute("SELECT * FROM stocks where id = :id AND symbol=:symbol",
                                id = session["user_id"], symbol=request.form.get("symbol"))

                #User has no stocks from this symbol
                if rows is None:
                    db.execute("INSERT INTO stocks (id,symbol,shares) VALUES(:id, :symbol, :shares)",
                            id=session["user_id"], symbol=request.form.get("symbol"),
                            shares=request.form.get("shares"))

                else:
                #User has stocks from this symbol
                    db.execute("UPDATE stocks SET shares = :shares WHERE id = :id AND symbol = :symbol",
                                shares = rows[0]["shares"] + request.form.get("shares"),
                                id=session["user_id"], symbol=request.form.get("symbol"))


    #Route was from GET
    else:
        return render_template("buy.html")
    return apology("TODO")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    return jsonify("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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
        quote=lookup(request.form.get("symbol"))
        if quote is None:
            return apology("Invalid Symbol", 403)
        else:
            return render_template("quoted.html", quote = quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match", 403)
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Password field(s) has been left blank", 403)

        #Query database for username
        rows = db.execute("Select * FROM users WHERE username= :username",
                          username=request.form.get("username"))

        #Checks if username is duplicate
        if len(rows) == 1:
            return apology("Username is already taken", 403)

        else:
            db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                        username=request.form.get("username"), hash=generate_password_hash(request.form.get("password")))
            session["user_id"] = db.execute("SELECT last_insert_rowid()")
            return redirect("/")

    #if method == GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
