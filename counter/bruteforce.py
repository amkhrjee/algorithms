import random


# customers = [10, 20, 30, 40, 5]
try:
    with open("randpts.txt", "r") as file:
        customers = [int(line.strip()) for line in file.readlines()]
except IOError as ioerr:
    print("File error: " + str(ioerr))


def get_optimal_list(customers_list, num_of_counters):
    customers = list(customers_list)
    max_time = 0
    optimal_list = {}
    for each_counter in range(num_of_counters):
        optimal_list.update({
            each_counter: []
        })
    index = 0
    while len(customers):
        random_choice = random.choice(customers)
        optimal_list[index % num_of_counters].append(random_choice)
        customers.remove(random_choice)
        index += 1
    for counter in range(num_of_counters):
        if max_time < sum(optimal_list[counter]):
            max_time = sum(optimal_list[counter])
    return max_time


time_list = []
for i in range(1000):
    time_list.append(get_optimal_list(customers, 10))

# print(time_list)
print(min(time_list))
