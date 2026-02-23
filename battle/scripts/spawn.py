import random as r

x = ['A', 'B', 'C', 'D']
y = [6, 7, 8, 9, 10]

print(x[r.randint(0, len(x) - 1)], y[r.randint(0, len(y) - 1)])