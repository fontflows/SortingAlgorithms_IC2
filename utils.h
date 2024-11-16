#ifndef UTILS_H
#define UTILS_H

#include "sorting.h"
#include <vector>
#include <string>

namespace utils {
    void generateRandomArray(int arr[], int size, int max_value = 1000000);
    void generateAscendingArray(int arr[], int size);
    void generateDescendingArray(int arr[], int size);
    void copyArray(const int source[], int dest[], int size);
    void printArray(const int arr[], int size);
    
    sorting::SortStats testSort(void (*sortFunc)(int[], int), int arr[], int size);
    sorting::SortStats testQuickSort(int arr[], int size);
    
    void exportResults(const std::string& algorithm_name,
                      const std::vector<int>& sizes,
                      const std::vector<sorting::SortStats>& stats,
                      const std::string& array_type,
                      const std::string& filename);
}

#endif