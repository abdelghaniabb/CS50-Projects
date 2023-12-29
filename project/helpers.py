from flask import redirect, render_template, session
from functools import wraps
import RPi.GPIO as GPIO

def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/0.12/patterns/viewdecorators/
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
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code

def strong_password(password):
    """Check for a strong password"""
    if len(password) < 4:
        return False

    check_number = False
    check_char = False
    check_symbol = False

    special_characters = """!@#$%^&*()-+?_=,<>/"""
    for char in password:
        if char.isdigit():
            check_number = True
        if char.isalpha():
            check_char = True
        if char in special_characters:
            check_symbol = True
    if check_char and check_number and check_symbol:
        return True
    return False

def change_gpio(pin, status):
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, status)

def get_state_gpio(pin):
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(pin, GPIO.OUT)
    return GPIO.input(pin)