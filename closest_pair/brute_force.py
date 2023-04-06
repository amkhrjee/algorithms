# Checks the correct answer via brute force
import math
point_list = []
min_dist = float('inf')
try:
    with open("randpts.txt", "r") as randf:
        len = int(randf.readline())
        for i in range(len):
            x, y = map(float, randf.readline().split(" "))
            point_list.append({
                "x": x,
                "y": y
            })
except IOError as ioerr:
    print("File error: " + str(ioerr))

for point_1 in point_list:
    for point_2 in point_list:
        if point_1 != point_2:
            dist = math.sqrt((point_1["x"] - point_2["x"])
                             ** 2 + (point_1["y"] - point_2["y"])**2)
            if dist < min_dist:
                min_dist = dist
                final_pair = [point_1, point_2]

print("Closest Pair: " + str(final_pair[0]) + " and " + str(final_pair[1]))
print("distance = " + str(min_dist))
