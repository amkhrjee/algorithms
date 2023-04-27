input_tuples = [
    (1, 10, 5),
    (2, 20, 3),
    (3, 10, 3),
    (4, 15, 3),
    (5, 14, 5),
    (6, 40, 4),
    (7, 18, 5),
    (8, 5, 7),
    (9, 20, 5),
    (10, 25, 4)
]


def find_optimal_score(input_tuples):
    optimum_list = {}
    sorted_input_tuples = sorted(
        input_tuples, key=lambda input: input[1], reverse=True)
    temp_list = list(sorted_input_tuples)
    exam_duration = sorted(
        input_tuples, key=lambda input: input[2], reverse=True)[0][2]
    time_elapsed = 0
    score = 0
    for each_minute in range(1, exam_duration + 1):
        question_to_attempt = None
        time_elapsed += 1
        if sorted_input_tuples[each_minute - 1][2] >= time_elapsed:
            question_to_attempt = sorted_input_tuples[each_minute - 1][0]
            score += sorted_input_tuples[each_minute - 1][1]
            temp_list.remove(sorted_input_tuples[each_minute - 1])
        else:
            for each_item in temp_list:
                if each_item[2] >= time_elapsed:
                    question_to_attempt = each_item[0]
                    score += each_item[1]
                    temp_list.remove(each_item)
                    break
        optimum_list.update({
            each_minute: question_to_attempt
        })

    print(optimum_list)
    print("Score = ", score)


find_optimal_score(input_tuples)
