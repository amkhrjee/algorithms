# current  problem: generates duplicate values for large(>10**5) data sets

import random
point_list = []
num_of_pts = int(input("Enter number of points: "))

for i in range(num_of_pts):
    point_list.append({
        "x": random.random()*random.randint(0, 100),
        "y": random.random()*random.randint(0, 100)
    })

try:
    with open("randpts.txt", "w") as randf:
        randf.write(str(num_of_pts) + '\n')
        for point in point_list:
            randf.write(str(point["x"]) + " " + str(point["y"]) + '\n')
except IOError as ioerr:
    print("File error: " + str(ioerr))
