import random
point_list = []
num_of_customers = int(input("Enter number of customers: "))

for i in range(num_of_customers):
    point_list.append(
        int(random.random()*random.randint(0, 100)))


try:
    with open("randpts.txt", "w") as randf:
        for point in point_list:
            randf.write(str(point) + '\n')
except IOError as ioerr:
    print("File error: " + str(ioerr))
