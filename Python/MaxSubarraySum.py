"""
Provide solutions for the Maximum Subarray Sum problem
"""


__all__ = [
    "BruteForce",
    "Recursive",
    "Kadane",
]


def BruteForce(arr):
    """
    Solution for the Maximum Subarray Sum problem

    Exhaustively tries all possibilities for the solution to the problem

    Parameters
    ----------
    arr : array-like
        A one dimensional array of numbers.

    Returns
    -------
    max_sum : number
        The maximum subarray sum.

    Examples
    --------
    >>> from MaxSubarraySum import BruteForce
    >>> BruteForce([-2, 11, -4, 13, -5, -2])
    20
    >>> BruteForce([-5, -6, -7, -8, -9, -3, -6, -7])
    -3
    """

    length = len(arr)
    max_sum = arr[0]
    for i in range(length):
        temp = 0
        for j in range(i, length):
            temp += arr[j]
            if temp > max_sum:
                max_sum = temp
    return max_sum


def _Recursive_Helper(arr, left, right):
    if left == right:
        return arr[left]

    center = (left + right) // 2
    left_max = _Recursive_Helper(arr, left, center)
    right_max = _Recursive_Helper(arr, center + 1, right)
    temp = 0
    left_border_max = arr[center]
    for i in range(center, left-1, -1):
        temp += arr[i]
        if temp > left_border_max:
            left_border_max = temp
    temp = 0
    right_border_max = arr[center+1]
    for i in range(center+1, right+1, 1):
        temp += arr[i]
        if temp > right_border_max:
            right_border_max = temp
    return max(left_max, left_border_max + right_border_max, right_max)


def Recursive(arr):
    """
    Solution for the Maximum Subarray Sum problem

    This algorithm uses a "Divide-and-Conquer" strategy.

    Parameters
    ----------
    arr : array-like
        A one dimensional array of numbers.

    Returns
    -------
    max_sum : number
        The maximum subarray sum.

    Examples
    --------
    >>> from MaxSubarraySum import Recursive
    >>> Recursive([-2, 11, -4, 13, -5, -2])
    20
    >>> Recursive([-5, -6, -7, -8, -9, -3, -6, -7])
    -3
    """

    return _Recursive_Helper(arr, 0, len(arr) - 1)


def Kadane(arr):
    """
    Solution for the Maximum Subarray Sum problem

    Implementation of Kadane's algorithm

    Parameters
    ----------
    arr : array-like
        A one dimensional array of numbers.

    Returns
    -------
    max_sum : number
        The maximum subarray sum.

    Examples
    --------
    >>> from MaxSubarraySum import Kadane
    >>> Kadane([-2, 11, -4, 13, -5, -2])
    20
    >>> Kadane([-5, -6, -7, -8, -9, -3, -6, -7])
    -3
    """

    temp = 0
    max_sum = arr[0]
    for item in arr:
        temp += item
        if temp > max_sum:
            max_sum = temp
        if temp < 0:
            temp = 0
    return max_sum


# This is a test of this module
if __name__ == "__main__":
    import numpy as np

    from time import time

    size = 1000
    low = -size//2
    high = size//2
    array = np.random.randint(low, high, size)
    # array = [-2, 11, -4, 13, -5, -2]
    # array = (-5, -6, -7, -8, -9, -3, -6, -7)

    algorithms = {
        "Kadane": Kadane,
        "Recursive": Recursive,
        "Brute Force": BruteForce,
    }

    info0 = "The time spend on the {0} algorithm: {1:.3f}ms"
    info1 = "The result of the {0} algorithm: {1}"
    separator = "=" * max(len(info0), len(info1)) + '\n'

    buff = []
    for algorithm, func in algorithms.items():
        start = time()
        res = func(array)
        end = time()
        buff.append(res)
        print(info0.format(algorithm, 1000*(end-start)))
        print(info1.format(algorithm, res))
        print(separator)

    # Assert all the algorithms give the same answer
    for item in buff:
        assert item == buff[0]
