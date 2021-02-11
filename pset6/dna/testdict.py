import csv
d = {}
with open("databases/small.csv", newline='') as file:
    spamreader = csv.DictReader(file)
    with open("sample.csv", "w") as new_file:
        fieldnames = ["name", "AGATC"]
        csv_writer = csv.DictWriter(new_file, fieldnames=fieldnames, delimiter = "\t")
        csv_writer.writeheader()
        for line in spamreader:
            del line["AATG"]
            del line["TATC"]
            csv_writer.writerow(line)