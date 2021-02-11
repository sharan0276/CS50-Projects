from cs50 import SQL
from flask import Flask, render_template, request, session, redirect
from flask_session import Session
from werkzeug.security import generate_password_hash

app = Flask(__name__)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///project.db")

@app.route("/tasks")
def tasks():
    if "todos" not in session:
        session["todos"] = []

    return render_template("tasks.html", todos=session["todos"])


@app.route("/todo", methods = ["POST"] )
def addtask():
    if request.method == "POST":
        todo = request.form.get("task")
        session["todos"].append(todo)
        return redirect("/tasks")

@app.route("/")
def route():
    return redirect("/login")


@app.route("/login", methods=["GET", "POST"])
def index():
    """Log user in """

    #forget any user id
    session.clear()


    if request.method == "GET":
        return  render_template("signin.html")

    else:
        rows = db.execute("SELECT * FROM users WHERE username=:username",
                            username = request.form.get("username"))

        #if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
         #   print("Error invalid UserName or password")
        session['user_id'] = rows[0]["id"]
        return redirect("/home")


@app.route("/register", methods=["GET", "POST"])
def reg():
    if request.method == "GET":
        return render_template("register.html")

    else:

        name = request.form.get("username")
        password = request.form.get("password")
        confirm = request.form.get("confirm")

        #search = db.execute("SELECT COUNT(*) FROM users WHERE ")
        prim_key = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                                username = name,
                                hash = generate_password_hash(password))

        '''if prim_key is None:
            print("Error in register")

        '''
        #Check it out
        session['user_id'] = prim_key

        return redirect("/home")   #need to change


@app.route("/home")
def home():
    username = db.execute("SELECT username FROM users WHERE id=:user_id",
                            user_id = session['user_id']);

    username = username[0]["username"];

    return render_template("home.html", username = username.upper());


@app.route("/calc")
def calculator():
    return render_template("calc.html");


@app.route("/timer")
def timer():
    return render_template("timer.html");

@app.route("/logout")
def logout():
     session.clear()
     return redirect("/")
