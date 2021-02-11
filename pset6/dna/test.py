import csv

d = {}

with open('databases/small.csv', 'r') as file:
    spamread = csv.DictReader(file);
    #for row in spamread:
     #   d[row["name"]] = int(row["AGATC"]);
    with open('databases.csv','w') as script:
        writer = csv.writer(script, delimiter = '\t')
        writer.writerow(["name","AGATC"])
        for scrip in spamread:
            writer.writerow([scrip["name"], scrip["AGATC"]])
    #print(spamread)

#print(d)