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

    #Grabs a list of stocks owned by the user
    rows = db.execute("SELECT * FROM stocks WHERE id=:id",
                id=session["user_id"])

    #Obtains user info from 'users'
    user = db.execute("SELECT * FROM users where id =:id",
                    id=session["user_id"])
    cash = user[0]["cash"]

    grand = cash

    for row in rows:
        quote = lookup(row["symbol"])
        row["price"] = quote["price"]

        total = quote["price"] * row["shares"]
        row["total"] = total

        grand = grand + total

    return render_template("index.html", rows=rows, cash=cash,grand=grand)


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
        shares= int(request.form.get("shares"))
        if shares <= 0:
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

            if shares*quote["price"] > money:
                return apology("Not enough cash", 403)
            else:
                money = money - shares * quote["price"]

                #Update user's cash
                db.execute("UPDATE users SET cash = :cash WHERE id = :id",
                            cash = money, id = session["user_id"])

                #Updates history table
                db.execute("INSERT INTO history (id,symbol,shares,price) VALUES(:id,:symbol,:shares,:price)",
                            id = session["user_id"], symbol = quote["symbol"],
                            shares = shares, price = quote["price"])

                #Adds stocks to users profile
                rows = db.execute("SELECT * FROM stocks where id = :id AND symbol=:symbol",
                                id = session["user_id"], symbol=quote["symbol"])

                #User has no stocks from this symbol
                if len(rows) != 1:
                    db.execute("INSERT INTO stocks (id,symbol,shares) VALUES(:id, :symbol, :shares)",
                            id=session["user_id"], symbol=quote["symbol"],
                            shares=shares)

                else:
                #User has stocks from this symbol
                    db.execute("UPDATE stocks SET shares = :shares WHERE id = :id AND symbol = :symbol",
                                shares = rows[0]["shares"] + shares,
                                id=session["user_id"], symbol=quote["symbol"])

                flash("Stock successfully purchased!")
                return redirect("/")

    #Route was from GET
    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    q = request.args.get("q")

    if len(q) >= 1:
        rows = db.execute("SELECT * FROM users where username=:q", q=q)
        if len(rows) == 0:
            return jsonify(True)
        else:
            return jsonify(False)



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM history where id=:id",
                        id=session["user_id"])

    return render_template("history.html", rows=rows)


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

            rows = db.execute("SELECT id FROM users WHERE username = :username",
                                            username=request.form.get("username"))

            session["user_id"] = rows[0]["id"]
            return redirect("/")

    #if method == GET
    else:
        return render_template("register.html")


@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    """Let's user make account changes"""
    if request.method == "POST":

        if not request.form.get("old"):
            return apology("Please enter old password", 403)
        elif not request.form.get("password"):
            return apology("Please enter a new password", 403)
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("New password and confirmation do not match", 403)
        elif request.form.get("old") == request.form.get("password"):
            return apology("Old password and new password must be different", 403)

        rows = db.execute("SELECT * FROM users where id=:id",
                            id = session["user_id"])

        if not check_password_hash(rows[0]["hash"], request.form.get("old")):
            return apology("Old password is incorrect", 403)
        else:
            db.execute("UPDATE users SET hash=:password where id=:id",
                        password = generate_password_hash(request.form.get("password")), id = session["user_id"])
            flash("Password has been changed!")
            return redirect("/")

    else:
        return render_template("account.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Please select a stock", 403)

        if not request.form.get("shares"):
            return apology("Please input shares", 403)

        shares = int(request.form.get("shares"))
        quote = lookup(request.form.get("symbol"))

        if shares < 0:
            return apology("Please input a non-negative integer", 403)

        #Look up id and symbol from stocks
        rows=db.execute("SELECT * FROM stocks WHERE id=:id AND symbol=:symbol",
                        id=session["user_id"], symbol=quote["symbol"])

        #Not enough shares
        if rows[0]["shares"]-shares < 0:
            return apology("Not enough shares to sell", 403)


        #New history entry
        db.execute("INSERT INTO history (id,symbol,shares,price) VALUES(:id,:symbol,:shares,:price)",
                    id=session["user_id"], symbol=quote["symbol"],
                    shares=-shares, price=quote["price"])


        #Delete entry if selling means no stocks
        if rows[0]["shares"]-shares == 0:
            db.execute("DELETE FROM stocks WHERE id=:id AND symbol=:symbol",
                        id=session["user_id"], symbol=quote["symbol"])

        #Modify stocks entry
        else:
            db.execute("UPDATE stocks SET shares=:shares WHERE id=:id AND symbol=:symbol",
                        shares=rows[0]["shares"]-shares, id=session["user_id"],
                        symbol=quote["symbol"])

        #Modify cash
        db.execute("UPDATE users SET cash=cash+:money WHERE id=:id",
                    money=shares*quote["price"], id=session["user_id"])

        flash("Stock successfully sold!")
        return redirect("/")

    #Arrived using GET
    else:
        rows = db.execute("SELECT * FROM stocks WHERE id = :id", id = session["user_id"])
        return render_template("sell.html", rows = rows)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
