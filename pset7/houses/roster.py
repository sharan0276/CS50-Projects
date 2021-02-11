# TODO
import cs50
from sys import argv, exit
import csv


if (len(argv) != 2):
    print("Error Occured........")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

rows = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", argv[-1])

for row in rows:

    if(row["middle"] != None):
        name = row["first"] + " " + row["middle"] + " " + row["last"]
    else:
        name = row["first"] + " " + row["last"]

    print(name, end=",")
    print(" born", row["birth"])