"""
A test script for the `sorting` module
"""


from time import time

import numpy as np
import sorting


# These sorting algorithms set to `True` will be test
sort_algorithm_controller = {
    "bucket_sort": True,
    # "bucket_sort": False,
    "quick_sort": True,
    # "quick_sort": False,
    "merge_sort": True,
    # "merge_sort": False,
    "shell_sort": True,
    # "shell_sort": False,
    "heap_sort": True,
    # "heap_sort": False,
    "selection_sort": True,
    # "selection_sort": False,
    "insertion_sort": True,
    # "insertion_sort": False,
    "bubble_sort": True,
    # "bubble_sort": False,
}

# These set to `True` will be used in shell_sort algorithm
shell_increments_controller = {
    "sedgewick": True,
    # "sedgewick": False,
    # "hibbard": True,
    "hibbard": False,
    # "shell": True,
    "shell": False,
}


msg0 = "The time spend on generating random array: {0:.3f}ms"
msg1 = "The time spend on {0}: {1:.3f}ms"
separator = '=' * max(len(msg0), len(msg1)) + '\n'


size = int(1e3)
low = -size//2
high = size//2
start = time()
# np.random.seed(0)
array = np.random.randint(low, high, size=size)
end = time()
print(msg0.format(1000*(end-start)))
print(separator)


start = time()
builtin_res = sorted(array)
end = time()
if size <= 40:
    print("The original array:")
    print(list(array))
    print("The sorted array:")
    print(builtin_res)
    print(separator)
print(msg1.format("builtin sorted", 1000*(end-start)))
print(separator)


for sort_algorithm in sort_algorithm_controller:
    if sort_algorithm_controller[sort_algorithm]:
        sort_algorithm_func = getattr(sorting, sort_algorithm)
        if sort_algorithm == "shell_sort":
            for which in shell_increments_controller:
                if shell_increments_controller[which]:
                    start = time()
                    res = sort_algorithm_func(array, which=which)
                    end = time()
                    temp = which + '_' + sort_algorithm
                    assert res == builtin_res
                    print(msg1.format(temp, 1000*(end-start)))
                    print(separator)
        else:
            start = time()
            res = sort_algorithm_func(array)
            end = time()
            assert res == builtin_res
            print(msg1.format(sort_algorithm, 1000*(end-start)))
            print(separator)
