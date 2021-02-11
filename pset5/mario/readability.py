from cs50 import get_string

string = get_string("Text: ")
letters = 0
words = 0
sentences = 0

for i in range(len(string)):
    ch = string[i]
    if ch.isalpha():
        letters += 1
    if ch in [".", "?", "!"]:
        sentences += 1
    if ch is " " and (string[i + 1].isalpha() or string[i + 1] is "\""):
        words += 1

# to include the last word
words += 1
L = letters * 100 / words
S = sentences * 100 / words

grade = 0.0588 * L - 0.296 * S - 15.8
# print(grade)

if grade < 1:
    print("Before Grade 1")

elif grade > 16:
    print("Grade 16+")

else:
    print(f"Grade {round(grade)}")
