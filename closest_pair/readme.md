- `closest_pair_for_eval.c` as the name suggests, is meant for evaluation for the assignment. Compile it with the `-lm` flag as it used the builtin `math.h` header. Please keep in mind if you are trying to use your own file as input, the file must be named `randpts.txt`, or you will have to change the macro value `filename` at the top of the file.

- `randpts.txt` contains 20 points. Use `randptsgen.py` to change this.

-  `randptsgen.py` contains script for generating random  numbers according to the specified input format. Produces unique values for upto 10^4 points (as per my rough tests).

- `closestpairstl.cpp` contains implementation of the CP algorithm utilizing the C++ STL. The code structure does *not* adhere to the template provided in the question. I did it to improve my understanding of the algorithm.

- `brute_force.py` contains a straightfrowards brute force algorithm for finding the closest points. I have used this to check the correctness of the other implementations.