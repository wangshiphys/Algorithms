"""
Implementation of some common sorting algorithms
"""


__all__ = [
    "insertion_sort",
    "selection_sort",
    "bubble_sort",
    "shell_sort",
    "heap_sort",
    "merge_sort",
    "quick_sort",
    "bucket_sort",
]


# Used by shell_sort and quick_sort
# If the length of `arr` is less than this value, the sort algorithm will
# treat `arr` as a special case
SORT_CUTOFF = 10


# The core algorithm for insertion_sort and shell_sort
def _insertion_sort_core(arr, increment):
    for i in range(increment, len(arr)):
        temp = arr[i]
        j = i
        while j >= increment and arr[j-increment] > temp:
            arr[j] = arr[j-increment]
            j -= increment
        arr[j] = temp


def insertion_sort(arr):
    """
    Implementation of the insertion sort algorithm

    Parameters
    ----------
    arr : iterable
        A collection of items to be sorted in `increasing sorted order`

    Returns
    -------
    res : list
        A new sorted list from the items in `iterable`

    Examples
    --------
    >>> from sorting import insertion_sort
    >>> insertion_sort(range(20, 0, -1))
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
    """

    arr = list(arr)
    _insertion_sort_core(arr, increment=1)
    return arr


def bubble_sort(arr):
    """
    Implementation of the bubble sort algorithm

    Parameters
    ----------
    arr : iterable
        A collection of items to be sorted in `increasing sorted order`

    Returns
    -------
    res : list
        A new sorted list from the items in `iterable`

    Examples
    --------
    >>> from sorting import bubble_sort
    >>> bubble_sort(range(20, 0, -1))
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
    """

    arr = list(arr)
    length = len(arr)
    for i in range(length - 1, 0, -1):
        for j in range(0, i):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr


def selection_sort(arr):
    """
    Implementation of the selection sort algorithm

    Parameters
    ----------
    arr : iterable
        A collection of items to be sorted in `increasing sorted order`

    Returns
    -------
    res : list
        A new sorted list from the items in `iterable`

    Examples
    --------
    >>> from sorting import selection_sort
    >>> selection_sort(range(20, 0, -1))
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
    """

    arr = list(arr)
    length = len(arr)
    for i in range(0, length-1):
        min_index = i
        for j in range(i + 1, length):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]
    return arr


# The following three internal function is used to generate different
# `increment sequence`
def _shell_increments(length):
    if length >= SORT_CUTOFF:
        increments = []
        inc = length // 2
        while inc:
            increments.append(inc)
            inc //= 2
    else:
        increments = [1]
    return increments


def _hibbard_increments(length):
    if length >= SORT_CUTOFF:
        increments = []
        inc = 1
        while inc < (length // 2):
            increments.append(inc)
            inc = 2 * inc + 1
        increments.reverse()
    else:
        increments = [1]
    return increments


def _sedgewick_increments(length):
    if length >= SORT_CUTOFF:
        increments = []
        for i in range(length):
            inc = 9 * (4 ** i - 2 ** i) + 1
            if inc < (length // 2):
                increments.append(inc)
            else:
                break
            inc = 4 ** (i + 2) - 3 * (2 ** (i + 2)) + 1
            if inc < (length // 2):
                increments.append(inc)
            else:
                break
        increments.reverse()
    else:
        increments = [1]
    return increments


def shell_sort(arr, which="sedgewick"):
    """
    Implementation of the shell sort algorithm

    Parameters
    ----------
    arr : iterable
        A collection of items to be sorted in `increasing sorted order`
    which : "shell" | "hibbard" | "sedgewick", optional
        which kind of `increment sequence` to use
        default : "sedgewick"

    Returns
    -------
    res : list
        A new sorted list from the items in `iterable`

    Notes
    -----
    If the length of `arr` is less than `SORT_CUTOFF(default: 10)`,then the
    `increment sequence` is `[1]` and the shell sort algorithm is the same
    as insertion sort algorithm.

    Examples
    --------
    >>> from sorting import shell_sort
    >>> shell_sort(range(20, 0, -1))
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
    """

    arr = list(arr)
    length = len(arr)
    if which == "shell":
        increments = _shell_increments(length)
    elif which == "hibbard":
        increments = _hibbard_increments(length)
    else:
        increments = _sedgewick_increments(length)
    for increment in increments:
        _insertion_sort_core(arr, increment)
    return arr


# A heap can be implemented using a complete binary tree
# A complete binary tree can be represented in an array
# For any element in array position `i`, the left child is in position `2i+1`
#  and right child is in position `2(i+1)`
def _left_child(index):
    return 2 * index + 1


def _right_child(index):
    return _left_child(index) + 1


def _percolate_down(arr, index, length):
    temp = arr[index]
    # Check is `index` has a left child
    while _left_child(index) < length:
        child = _left_child(index)
        # Check if `index` has right_child
        # If has right child and right child is larger than left child then
        # the right child is chosen as `child`
        if (child + 1) < length and arr[child + 1] > arr[child]:
            child += 1
        if temp < arr[child]:
            arr[index] = arr[child]
        else:
            break
        index = child
    arr[index] = temp


def heap_sort(arr):
    """
    Implementation of the heap sort algorithm

    Parameters
    ----------
    arr : iterable
        A collection of items to be sorted in `increasing sorted order`

    Returns
    -------
    res : list
        A new sorted list from the items in `iterable`

    Examples
    --------
    >>> from sorting import heap_sort
    >>> heap_sort(range(20, 0, -1))
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
    """

    arr = list(arr)
    length = len(arr)
    # The elements in sub-array `array[(length//2+1):length]` are all leaf nodes
    for i in range(length // 2, -1, -1):
        _percolate_down(arr, i, length)
    for i in range(length - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        _percolate_down(arr, 0, i)
    return arr


def _merge(arr, buffer, left_start, right_start, right_end):
    left_end = right_start - 1
    index0 = left_start
    index1 = right_start
    index = left_start
    while index0 <= left_end and index1 <= right_end:
        if arr[index0] <= arr[index1]:
            buffer[index] = arr[index0]
            index0 += 1
        else:
            buffer[index] = arr[index1]
            index1 += 1
        index += 1

    # At most one of the following two `if statement` can be executed
    if index0 <= left_end:
        buffer[index:right_end+1] = arr[index0:left_end+1]
    if index1 <= right_end:
        buffer[index:right_end+1] = arr[index1:right_end+1]
    arr[left_start:right_end+1] = buffer[left_start:right_end+1]


def _msort(arr, buffer, left, right):
    if left < right:
        center = (left + right) // 2
        _msort(arr, buffer, left, center)
        _msort(arr, buffer, center+1, right)
        _merge(arr, buffer, left, center+1, right)


def merge_sort(arr):
    """
    Implementation of the merge sort algorithm

    Parameters
    ----------
    arr : iterable
        A collection of items to be sorted in `increasing sorted order`

    Returns
    -------
    res : list
        A new sorted list from the items in `iterable`

    Examples
    --------
    >>> from sorting import merge_sort
    >>> merge_sort(range(20, 0, -1))
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
    """

    arr = list(arr)
    length = len(arr)
    buffer = [None] * length
    _msort(arr, buffer, 0, length-1)
    del buffer
    return arr


def _median3(arr, left, right):
    center = (left + right) // 2
    if arr[left] > arr[center]:
        arr[left], arr[center] = arr[center], arr[left]
    if arr[left] > arr[right]:
        arr[left], arr[right] = arr[right], arr[left]
    if arr[center] > arr[right]:
        arr[center], arr[right] = arr[right], arr[center]
    arr[center], arr[right-1] = arr[right-1], arr[center]
    return arr[right-1]


def _qsort(arr, left, right):
    if (right - left) >= SORT_CUTOFF:
        pivot = _median3(arr, left, right)
        i = left
        j = right - 1
        while True:
            i += 1
            j -= 1
            while arr[i] < pivot: i += 1
            while arr[j] > pivot: j -= 1
            if i < j:
                arr[i], arr[j] = arr[j], arr[i]
            else:
                break
        arr[i], arr[right - 1] = arr[right-1], arr[i]
        _qsort(arr, left, i-1)
        _qsort(arr, i+1, right)
    else:
        # If the length of `arr` is less than `SORT_CUTOFF` use selection
        # sort algorithm instead
        for i in range(left, right):
            min_index = i
            for j in range(i+1, right+1):
                if arr[j] < arr[min_index]:
                    min_index = j
            arr[i], arr[min_index] = arr[min_index], arr[i]


def quick_sort(arr):
    """
    Implementation of the quick sort algorithm

    Parameters
    ----------
    arr : iterable
        A collection of items to be sorted in `increasing sorted order`

    Returns
    -------
    res : list
        A new sorted list from the items in `iterable`

    Examples
    --------
    >>> from sorting import quick_sort
    >>> quick_sort(range(20, 0, -1))
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
    """

    arr = list(arr)
    length = len(arr)
    _qsort(arr, 0, length-1)
    return arr


# Find the minimum and maximum of the given `arr`
def _find_extreme(arr):
    min_item = arr[0]
    max_item = arr[0]
    for item in arr:
        if item < min_item:
            min_item = item
        if item > max_item:
            max_item = item
    return min_item, max_item


def bucket_sort(arr):
    """
    Implementation of the bucket sort algorithm

    Parameters
    ----------
    arr : iterable
        A collection of integers to be sorted in `increasing sorted order`

    Returns
    -------
    res : list
        A new sorted list from the integers in `iterable`

    Examples
    --------
    >>> from sorting import bucket_sort
    >>> bucket_sort(range(20, 0, -1))
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
    """

    min_item, max_item = _find_extreme(arr)
    buffer = [0] * (max_item - min_item + 1)
    for item in arr:
        buffer[item - min_item] += 1
    res = [
        index
        for index, count in enumerate(buffer, start=min_item)
        for j in range(count)
    ]
    del buffer
    return res
