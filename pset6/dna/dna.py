from sys import argv, exit
import csv
import cs50

if len(argv) != 3:
    print("Error!! Usage : python dna.py database.csv sequence.txt")
    exit(1)

file = open(argv[2], 'r')

sequence = file.read()

# print(sequence)

people = {}
with open(argv[1], newline='\n') as database:
    spamread = csv.reader(database, delimiter='\n')

    index = 0
    for row in spamread:
        if index == 0:
            SPR = tuple([strand for strand in row[0].strip().split(',') if strand != "name"])

        else:
            people[row[0].strip().split(',')[0]] = (tuple(int(x) for x in [strand for strand in row[0].strip().split(',')][1:]))

        index += 1

# print(SPR)
# print(people)
count_seq = []

for strand in SPR:
    i = 0
    max_value = -1
    curr_value = 0

    while i < len(sequence):
        seq = sequence[i:i+len(strand)]
        # print(seq)
        if seq == strand:
            curr_value += 1
            i += len(strand)
            max_value = max(max_value, curr_value)
        else:
            curr_value = 0
            i += 1

    if max_value == -1:
        max_value = 0

    count_seq.append(max_value)

count_seq = tuple(count_seq)

flag = 0

for name in people:
    if people[name] == count_seq:
        flag = 1
        print(name)

if flag == 0:
    print("No match")
