#include "sorting.h"
#include <algorithm>

namespace sorting {
    long long comparisons = 0;
    long long movements = 0;

    long long getComparisons() { return comparisons; }
    long long getMovements() { return movements; }
    void resetStats() { comparisons = 0; movements = 0; }

    void insertionSort(int arr[], int size) {
        for (int i = 2; i <= size; i++) {
            comparisons++;
            if (arr[i] < arr[i-1]) {
                int key = arr[i];
                int j = i - 1;
                movements++;
                
                while (j >= 1 && arr[j] > key) {
                    comparisons++;
                    arr[j + 1] = arr[j];
                    movements++;
                    j--;
                }
                arr[j + 1] = key;
                movements++;
            }
        }
    }

    void binaryInsertionSort(int arr[], int size) {
        for (int i = 2; i <= size; i++) {
            int key = arr[i];
            int left = 1;
            int right = i - 1;
            movements++;

            while (left <= right) {
                int mid = (left + right) / 2;
                comparisons++;
                if (arr[mid] > key)
                    right = mid - 1;
                else
                    left = mid + 1;
            }

            for (int j = i - 1; j >= left; j--) {
                arr[j + 1] = arr[j];
                movements++;
            }
            arr[left] = key;
            movements++;
        }
    }

    void selectionSort(int arr[], int size) {
        for (int i = 1; i < size; i++) {
            int min_idx = i;
            
            for (int j = i + 1; j <= size; j++) {
                comparisons++;
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }
            
            if (min_idx != i) {
                int temp = arr[i];
                arr[i] = arr[min_idx];
                arr[min_idx] = temp;
                movements += 3;
            }
        }
    }

    void bubbleSort(int arr[], int size) {
        for (int i = 1; i <= size-1; i++) {
            bool swapped = false;
            for (int j = 1; j <= size-i; j++) {
                comparisons++;
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    movements += 3;
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

    void heapSort(int arr[], int size) {
        // Construir heap
        for (int i = size/2; i >= 1; i--) {
            int root = i;
            while (2*root <= size) {
                int child = 2*root;
                if (child + 1 <= size) {
                    comparisons++;
                    if (arr[child + 1] > arr[child])
                        child++;
                }
                comparisons++;
                if (arr[root] < arr[child]) {
                    std::swap(arr[root], arr[child]);
                    movements += 3;
                    root = child;
                } else break;
            }
        }

        // Extrair elementos
        for (int i = size; i > 1; i--) {
            std::swap(arr[1], arr[i]);
            movements += 3;
            int root = 1;
            while (2*root < i) {
                int child = 2*root;
                if (child + 1 < i) {
                    comparisons++;
                    if (arr[child + 1] > arr[child])
                        child++;
                }
                comparisons++;
                if (arr[root] < arr[child]) {
                    std::swap(arr[root], arr[child]);
                    movements += 3;
                    root = child;
                } else break;
            }
        }
    }

    void merge(int arr[], int left, int mid, int right) {
        int* temp = new int[right - left + 2];
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            comparisons++;
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
            movements++;
        }

        while (i <= mid) {
            temp[k++] = arr[i++];
            movements++;
        }
        while (j <= right) {
            temp[k++] = arr[j++];
            movements++;
        }

        for (i = 0; i < k; i++) {
            arr[left + i] = temp[i];
            movements++;
        }

        delete[] temp;
    }

    void mergeSortHelper(int arr[], int left, int right) {
        if (left < right) {
            int mid = (left + right) / 2;
            mergeSortHelper(arr, left, mid);
            mergeSortHelper(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    void mergeSort(int arr[], int size) {
        mergeSortHelper(arr, 1, size);
    }

    void quickSort(int arr[], int left, int right) {
        if (left >= right) return;

        // Choose pivot as median of first, middle, and last elements
        int mid = (left + right) / 2;
        int pivot = std::max(std::min(arr[left], arr[mid]), std::min(std::max(arr[left], arr[mid]), arr[right]));
        movements += 3; // Counts the pivot selection

        int i = left, j = right;
        while (i <= j) {
            while (arr[i] < pivot) {
                i++;
                comparisons++;
            }
            while (arr[j] > pivot) {
                j--;
                comparisons++;
            }
            if (i <= j) {
                std::swap(arr[i], arr[j]);
                movements += 3; // Counts each swap
                i++;
                j--;
            }
        }

        quickSort(arr, left, j);
        quickSort(arr, i, right);
    }
}