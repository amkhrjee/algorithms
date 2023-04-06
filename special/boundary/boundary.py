from matlplotlib import pyplot as plt

point_list = []
min_dist = float('inf')
try:
    with open("randpts.txt", "r") as randf:
        length = int(randf.readline())
        for i in range(length):
            x, y = map(float, randf.readline().split(" "))
            point_list.append(
                [x, y]
            )
except IOError as ioerr:
    print("File error: " + str(ioerr))

boundary_pts = []
max_x_covered = 0

x_list = []
y_list = []

for each_point in sorted(point_list, key=lambda point: point[1], reverse=True):
    x_list.append(each_point[0])
    y_list.append(each_point[1])
    if each_point[0] >= max_x_covered:
        max_x_covered = each_point[0]
        boundary_pts.append(each_point)

# dirty hack
boundary_pts.insert(0, [0, boundary_pts[0][1]])
boundary_pts.append([boundary_pts[len(boundary_pts) - 1][0], 0])

plt.plot(x_list, y_list)
plt.show()

for each_point in boundary_pts:
    print(each_point)
