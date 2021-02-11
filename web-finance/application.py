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

def provided(field):
    if not request.form.get(field):
        return apology(f"must provide {field}", 403)

@app.route("/")
@login_required
def portfolio():
    return redirect("/index")


@app.route("/index")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("""SELECT symbol, SUM(shares) AS totalShares, MAX(price) AS maxAcqPriceShare, SUM(price * shares) AS Investment
                        FROM transactions WHERE user_id=:id
                        GROUP BY symbol
                        HAVING SUM(shares) > 0""",
                        id=session["user_id"])
    holdings=[]
    grand_total = 0
    for row in rows:
        stock = lookup(row["symbol"])
        holdings.append({
            "symbol": stock["symbol"],
            "company": stock["name"],
            "shares": row["totalShares"],
            "acqPrice": usd(row["maxAcqPriceShare"]),
            "currPrice": usd(stock["price"]),
            "invested": usd(row["Investment"]),
            "total": usd(stock["price"] * float(row["totalShares"]))
        })
        grand_total += stock["price"] * float(row["totalShares"])

    rows = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=session["user_id"])
    cash = rows[0]["cash"]

    return render_template("index.html", holdings= holdings, cash= usd(cash), grand_total = usd(grand_total), net_worth = usd(grand_total + cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        result_check = provided("stock") or provided("shares")
        shares = request.form.get("shares")

        if result_check is not None:
            return result_check

        elif not shares.isdigit():
            return apology("Invalid Value of Shares", 403)

        symbol = request.form.get("stock").upper()
        stock = lookup(symbol)

        if stock is None:
            return apology("invalid company symbol", 403)

        # to obtain the cash available with this user
        rows = db.execute("SELECT cash FROM users WHERE id=:id", id = session["user_id"])
        cash = rows[0]["cash"]

        updated_cash = cash - float(shares) * stock['price']

        if updated_cash < 0:
            return apology("Can't afford these shares.", 403)

        db.execute("UPDATE users SET cash=:updated_cash WHERE id=:id",
                    updated_cash = updated_cash,
                    id=session["user_id"])

        #""" are given to perform a multi line sql query
        db.execute("""INSERT INTO transactions (user_id, symbol, shares, price) VALUES
                    (:user_id, :symbol, :shares, :price)""",
                    user_id= session["user_id"],
                    symbol= stock['symbol'],
                    shares= int(shares),
                    price= stock['price'])

        #flash is already imported
        flash("BOUGHT!")
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("""SELECT * FROM transactions
                            WHERE user_id=:id
                            ORDER BY time DESC""",
                            id=session["user_id"])

    return render_template("history.html", history=history)



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
    if request.method == "GET":
        return render_template("quote.html")

    else:
        result_check = provided("stock")
        if result_check is not None:
            return result_check

        company = request.form.get("stock").upper()
        stock = lookup(company)
        if stock is None:
            return apology("invalid stock symbol", 400)

        #return render_template("quoted.html", stock = stock)

        return render_template("quoted.html", stockName = { "company": stock['name'],
                                                            "symbol": stock['symbol'],
                                                           "price": usd(stock['price'])})

    #return apology("TODO")


def checkpass(password, confirmation):
    if password != confirmation:
        return apology("passwords don't match", 403)

'''def checkdup(name):
    rows = db.execute("SELECT username from users")
    #name = request.form.get(field)
    for row in rows:
        if name == row:
            return apology(f"The username already exists {name}", 403)'''


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        name = request.form.get("name")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        result_check = provided("username") or provided("password") or provided("confirmation")
        # to check if the inputs are provided
        if result_check != None:
            return result_check

        #to check if the username is unique and the passwords match
        result_check = checkpass(password, confirmation)
        if result_check != None:
            return result_check

        else:
            try:
                prim_key = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)" ,
                    username=request.form.get("username"),
                    hash = generate_password_hash(request.form.get("password")))
            except:
                return apology("The username already exists", 403)

        if prim_key is None:
            return apology("Error in insert", 403)

        session["user_id"] = prim_key

        return redirect("/")
    #return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    symbols = []
    if request.method == "GET":
        rows = db.execute("""SELECT symbol FROM transactions
                      WHERE user_id=:user_id
                      GROUP BY symbol
                      HAVING SUM(shares) > 0""",
                     user_id=session["user_id"])

        for row in rows:
            symbols.append(row["symbol"])

        return render_template("sell.html", symbols= symbols)


    else:
        result_check = provided("shares") or provided("stock")
        shares = request.form.get("shares")

        if result_check is not None:
            return result_check

        elif not shares.isdigit():
            return apology("Invalid Value of Shares", 403)

        symbol = request.form.get("stock").upper()
        stock = lookup(symbol)

        # to obtain the cash available with this user
        cash = db.execute("SELECT cash FROM users WHERE id=:id", id = session["user_id"])
        cash = cash[0]["cash"]

        sharesOwn = db.execute("""SELECT SUM(shares) as totalShares FROM transactions
                               WHERE user_id=:id AND symbol=:symbol
                               GROUP BY symbol""",
                               id=session["user_id"],
                               symbol = symbol)

        sharesOwn = sharesOwn[0]["totalShares"]

        if sharesOwn < int(shares) :
            return apology(f" You don't own {shares} shares in {stock['symbol']}.", 403)

        #elif sharesOwn is None:
          #  return apology(f" You don't own {shares} shares in {stock['symbol']}.", 403)

        updated_cash = cash + float(shares) * stock['price']

        db.execute("UPDATE users SET cash =:updated_cash WHERE id=:user_id",
                    updated_cash = updated_cash,
                    user_id=session["user_id"])

        #""" are given to perform a multi line sql query
        db.execute("""INSERT INTO transactions (user_id, symbol, shares, price) VALUES
                    (:user_id, :symbol, :shares, :price)""",
                    user_id= session["user_id"],
                    symbol= stock['symbol'],
                    shares= int(shares) * -1,
                    price= stock['price'])

        #flash is already imported
        flash(f"SOLD {shares} shares in {stock['name']} ({stock['symbol']})!")
        return redirect("/")

#def val(cash):
#    cash = cash.replace("$","")
 #   cash = cash.replace(",","")
  #  return float(cash)

@app.route("/cash", methods=["GET", "POST"])
@login_required
def add():
    "Add Cash to your account"
    if request.method == "GET":
        return render_template("addCash.html")

    else:
        result_check = provided("amount")
        if result_check is not None:
            return result_check

        amount = request.form.get("amount")

        db.execute("UPDATE users SET cash = cash + :amount WHERE id=:user_id", amount = amount, user_id=session["user_id"])
        flash("Amount Added to Account")
        return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
