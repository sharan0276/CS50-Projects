from cs50 import get_float

while True:
    cents = get_float("Enter the change:")
    if cents > 0:
        break

cents = (int)(cents * 100)
coins = 0

if cents > 25:
    coins = cents // 25
    cents = cents - coins * 25

if cents >= 10:
    coinsT = cents // 10
    cents -= coinsT * 10
    coins += coinsT

if cents >= 5:
    coinsF = cents // 5
    cents -= coinsF * 5
    coins += coinsF

coins += cents

print(coins)
