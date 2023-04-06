from matplotlib import pyplot as plt


def plot(boundary_pts):
    plt_list = []
    prev_y = float('-inf')
    prev_x = 0
    for each_point in boundary_pts:
        if each_point[1] > prev_y:
            plt_list.append(each_point)
            prev_x = each_point[0]
            prev_y = each_point[1]
        elif each_point[1] == prev_y:
            plt_list.append(each_point)
            prev_x = each_point[0]
        else:
            plt_list.append([prev_x, each_point[1]])
            prev_x = each_point[0]
            plt_list.append(each_point)

    plt_x_list = []
    plt_y_list = []
    for each_point in plt_list:
        plt_x_list.append(each_point[0])
        plt_y_list.append(each_point[1])
    plt.style.use('bmh')
    plt.scatter(x_list, y_list)
    plt.scatter(bound_x_list, bound_y_list, c='g')
    plt.fill_between(plt_x_list, plt_y_list,  color='g', alpha=0.5)
    plt.title("Boundary Problem")
    plt.show()


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
boundary_pts.append([0, 0])

bound_x_list = []
bound_y_list = []

for each_point in boundary_pts:
    bound_x_list.append(each_point[0])
    bound_y_list.append(each_point[1])
    print(each_point)

plot(boundary_pts=boundary_pts)
