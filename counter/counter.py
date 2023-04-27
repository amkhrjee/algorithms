# customers = [10, 20, 30, 40, 5]
try:
    with open("randpts.txt", "r") as file:
        customers = [int(line.strip()) for line in file.readlines()]
except IOError as ioerr:
    print("File error: " + str(ioerr))


def get_min(optimal_list):
    min_counter = [float('inf')]
    for each_counter in optimal_list:
        if sum(min_counter) > sum(each_counter):
            min_counter = each_counter
    return min_counter


def get_optimal_allocation(customers, num_of_counters):
    sorted_customers = sorted(customers, reverse=True)
    optimal_list = {}
    for each_counter in range(num_of_counters):
        optimal_list.update({
            each_counter: []
        })

    index = 0
    for each_counter in optimal_list:
        optimal_list[each_counter].append(sorted_customers[index])
        index += 1

    for each_customer in sorted_customers[index:]:
        min_counter = get_min([optimal_list[x]
                              for x in range(num_of_counters)])
        min_counter.append(each_customer)
    return optimal_list


def print_optimal_list(customers, optimal_list):
    for each_counter in optimal_list:
        print(str(each_counter) + " -> ", end=" ")
        print(optimal_list[each_counter])


def get_max_time(optimal_list):
    max_time = 0
    for counter in optimal_list:
        if max_time < sum(optimal_list[counter]):
            max_time = sum(optimal_list[counter])
    return max_time


optimal_list = get_optimal_allocation(customers, 10)
# print_optimal_list(customers, optimal_list)
print(get_max_time(optimal_list))
