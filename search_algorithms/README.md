Search Algorithms README

Overview

This repository contains implementations and explanations of two fundamental search algorithms: Linear Search and Binary Search. Understanding these algorithms is crucial for anyone involved in computer science, programming, or algorithm design. Below, we provide an overview of search algorithms and delve into the specifics of Linear Search and Binary Search.

What is a Search Algorithm?

A search algorithm is a step-by-step procedure or method for locating specific information within a collection of data. It involves systematically examining each element in the dataset until a match is found or the entire dataset has been searched.

What is a Linear Search?

A Linear Search, also known as a sequential search, is the simplest form of searching. In this algorithm, elements are sequentially checked in a linear order until the desired element is found or the end of the list is reached. The time complexity of a linear search is O(n), where 'n' is the size of the dataset.

Implementation

int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;  // Element found, return its index
        }
    }
    return -1;  // Element not found
}


What is a Binary Search?


Search Algorithms README
Overview
This repository contains implementations and explanations of two fundamental search algorithms: Linear Search and Binary Search. Understanding these algorithms is crucial for anyone involved in computer science, programming, or algorithm design. Below, we provide an overview of search algorithms and delve into the specifics of Linear Search and Binary Search.

What is a Search Algorithm?
A search algorithm is a step-by-step procedure or method for locating specific information within a collection of data. It involves systematically examining each element in the dataset until a match is found or the entire dataset has been searched.

What is a Linear Search?
A Linear Search, also known as a sequential search, is the simplest form of searching. In this algorithm, elements are sequentially checked in a linear order until the desired element is found or the end of the list is reached. The time complexity of a linear search is O(n), where 'n' is the size of the dataset.

Implementation
c
Copy code
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;  // Element found, return its index
        }
    }
    return -1;  // Element not found
}
What is a Binary Search?
Binary Search is a more efficient algorithm that works on sorted datasets. It repeatedly divides the search space in half until the target element is found. This algorithm has a time complexity of O(log(n)), making it significantly faster than Linear Search for large datasets.

Implementation

#include <stdio.h>

int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid; /* Element found, return its index */
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; /* Element not found */
}

int main() {
    /* Example usage */
    int sortedArray[] = {2, 4, 6, 8, 10, 12, 14, 16};
    int arraySize = sizeof(sortedArray) / sizeof(sortedArray[0]);
    int targetElement = 10;

    int result = binarySearch(sortedArray, 0, arraySize - 1, targetElement);

    if (result != -1) {
        printf("Element %d found at index %d\n", targetElement, result);
    } else {
        printf("Element %d not found in the array\n", targetElement);
    }

    return 0;
}

This C implementation of Binary Search assumes that the input array is sorted in ascending order. The binarySearch function takes the array, the lower and upper bounds, and the target element as parameters, performing the binary search until it finds the element or determines it's not present in the array. The main function provides an example of how to use the binarySearch function.

Conclusion

Both Linear Search and Binary Search serve different purposes based on the nature of the data. While Linear Search is straightforward and applicable to unsorted datasets, Binary Search excels in efficiently locating elements in sorted datasets. Understanding these algorithms provides a solid foundation for tackling various search-related challenges in computer science.
