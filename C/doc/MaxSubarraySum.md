# Maximum Subarray Sum Problem
This module provides several solutions for the **Maximum Subarray Sum** problem

## Definition
The **Maximum Subarray Sum** problem is the task of finding the **contiguous 
subarray** within a one dimensional array of numbers which has the **largest 
sum**.

![MaxSubarraySumDefinition](figures/MaxSubarraySumDefinition.png)

Examples:
> For input [-2, 11, -4, 13, -5, -2] the answer is 20 (A[2] through A[4])

This module provides **three** algorithms to solve this problem:

* int **BruteForce**(*int arr[], int N*)

    This solution exhaustively tries all possible subarray and find the one 
    with maximum sum. The running time of this algorithm is `O(N^2)`.

* int **Recursive**(*int arr[], int N*)

    This is a recursive solution and the running time is `O(NlogN)`.

    The algorithm uses a "divide-and-conquer" strategy. The idea is to split 
    the problem into two roughly equal subproblems, which are then solved 
    recursively. This is the "divide" part. The "conquer" stage consist of 
    patching together the two subproblems and possibly doing a small amount 
    of additional work, to arrive at a solution for the whole problem.

    In our case, the **Maximum Subarray Sum** can be in one of three places. 
    Either it occurs entirely in the left half of the input, or entirely in 
    the right half, or it crosses the middle and is in both halves. The first 
    two cases can be solved recursively. The last case can be obtained by 
    finding the largest sum in the first half that include the last element 
    in the first half and the largest sum in the second half that include the
    first element in the second half. These two sums can be added together.

* int **Kadane**(*int arr[], int N*)

    This function uses the Kadane's algorithm to solve the problem. This is 
    an `O(N)` (linear) solution and is simple to implement.

    [Kadane's Algorithm](https://en.wikipedia.org/wiki/Maximum_subarray_problem)
