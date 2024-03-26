from cs50 import SQL
from flask import Flask, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from functools import wraps

# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///quizzzy.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/latest/patterns/viewdecorators/
    """

    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)

    return decorated_function


def apology(message, code=400):
    """Render message as an apology to user."""

    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    return render_template("apology.html", top=code, bottom=escape(message)), code


@app.route("/")
def index():
    return render_template("index.html")


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
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   username, generate_password_hash(password))
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/make", methods=["GET", "POST"])
@login_required
def make():
    if request.method == "POST":
        mcq_questions = request.form.getlist("mcq")
        mcq_answers = request.form.getlist("mcq-answer")
        text_questions = request.form.getlist("text")
        text_answers = request.form.getlist("text-answer")
        tf_questions = request.form.getlist("tf")
        tf_answers = request.form.getlist("tf-answer")
        mcq_answer_counts = request.form.getlist("mcq-answer-count")
        corrects = request.form.getlist("mcq-correct")

        if not any([mcq_questions, text_questions, tf_questions]):
            return apology("Please enter at least one question")

        if mcq_questions:
            if not all(mcq_questions):
                return apology("All MCQ questions must be filled")
            if not all(mcq_answers):
                return apology("All MCQ answers must be filled")
            if not any(corrects):
                return apology("Please select at least one correct answer for MCQ questions")

        if tf_questions:
            if not all(tf_questions):
                return apology("All True/False questions must be filled")
            if not all(tf_answers):
                return apology("Please select an answer for each True/False question")

        if text_questions:
            if not all(text_questions):
                return apology("All Text questions must be filled")
            if not all(text_answers):
                return apology("Please provide an answer for each Text question")

        quiz_id = db.execute("INSERT INTO quizzes (user_id) VALUES (?)", session["user_id"])

        for question, answer_count in zip(mcq_questions, mcq_answer_counts):
            question_id = db.execute("INSERT INTO questions (quiz_id, question) VALUES (?, ?)", quiz_id, question)
            correct = corrects.pop(0)
            for i in range(int(answer_count)):
                answer = mcq_answers.pop(0)
                answer_id = db.execute("INSERT INTO answers (question_id, answer) VALUES (?, ?)", question_id, answer)
                if i + 1 == int(correct):
                    db.execute("INSERT INTO correct_answers (answer_id) VALUES (?)", answer_id)


        for question, answer in zip(tf_questions, tf_answers):
            question_id = db.execute("INSERT INTO questions (quiz_id, question) VALUES (?, ?)",
                                     quiz_id, question)
            db.execute("INSERT INTO answers (question_id, answer) VALUES (?, ?)", question_id, answer)

        for question, answer in zip(text_questions, text_answers):
            question_id = db.execute("INSERT INTO questions (quiz_id, question) VALUES (?, ?)",
                                     quiz_id, question)
            db.execute("INSERT INTO answers (question_id, answer) VALUES (?, ?)", question_id, answer)

        return redirect("/")
    else:
        return render_template("make.html")


@app.route("/quizzes", methods=["GET"])
@login_required
def quizzes():
    quizzes = db.execute("SELECT * FROM quizzes WHERE user_id = ?", session["user_id"])
    return render_template("quizzes.html", quizzes=quizzes)


@app.route("/view/<int:quiz_id>", methods=["GET"])
@login_required
def view(quiz_id):
    quiz = db.execute("SELECT * FROM quizzes WHERE id = ?", quiz_id)
    if not quiz:
        return apology("Quiz not found", 404)

    questions = db.execute("SELECT * FROM questions WHERE quiz_id = ?", quiz_id)
    if not questions:
        return apology("No questions found for this quiz", 404)

    answers = {}
    for question in questions:
        question_id = question["id"]
        answers[question_id] = db.execute("SELECT * FROM answers WHERE question_id = ?", question_id)

    return render_template("view.html", quiz=quiz, questions=questions, answers=answers)


@app.route("/delete/<int:quiz_id>", methods=["POST"])
@login_required
def delete(quiz_id):

    db.execute("DELETE FROM correct_answers WHERE answer_id IN (SELECT id FROM answers WHERE question_id IN (SELECT id FROM questions WHERE quiz_id = ?))", quiz_id)
    db.execute(
        "DELETE FROM answers WHERE question_id IN (SELECT id FROM questions WHERE quiz_id = ?)", quiz_id)
    db.execute("DELETE FROM questions WHERE quiz_id = ?", quiz_id)
    db.execute("DELETE FROM quizzes WHERE id = ?", quiz_id)

    return redirect("/quizzes")
