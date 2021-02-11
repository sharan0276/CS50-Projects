# TODO
import cs50
from sys import argv, exit
import csv


if len(argv) != 2:
    print("\nError Occurred.......")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

with open(argv[-1], "r") as file:
    spamread = csv.DictReader(file)

    for row in spamread:
        name = row["name"]  # stores name
        name = name.split()
        last = name[-1]  # last word goes to last
        if len(name) == 3:   # if there is a middle
            middle = name[1]
        else:
            middle = None
        first = name[0]
        house = row["house"]
        birth = row["birth"]
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", first, middle, last, house, birth)

print("Insert Complete")
