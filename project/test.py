from cs50 import SQL
import RPi.GPIO as GPIO
import os

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///information.db")

db.execute("""CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    a NUMERIC,
    b NUMERIC);""")

    
import measure_temperature_DHT