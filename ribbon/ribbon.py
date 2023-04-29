fragments = [
    "GOYG",
    "WGO",
    "YGGW",
    "GWY",
    "GOYW",
    "WYOG",
    "OGOY"
]

# bruteforce


def get_minimal_ribbon(fragments):
    sorted_frags = sorted(fragments, key=lambda frag: len(frag), reverse=True)
    final_ribbon = ""
    for each_frag in sorted_frags:
        flag = False
        sorted_frags.remove(each_frag)
        for another_frag in sorted_frags:
            max_common_chars = min(len(each_frag), len(another_frag)) - 1
            while (max_common_chars):
                if each_frag[-max_common_chars:] is another_frag[:max_common_chars]:
                    final_ribbon += each_frag + another_frag[max_common_chars:]
                    flag = True
                    sorted_frags.remove(another_frag)
                    sorted_frags.insert(0, another_frag)
                    break
                else:
                    max_common_chars -= 1
            if flag is True:
                break
    return final_ribbon


complete_ribbon = get_minimal_ribbon(fragments)
print(complete_ribbon)
print((len(complete_ribbon)))
