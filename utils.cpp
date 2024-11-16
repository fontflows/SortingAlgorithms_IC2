#include "utils.h"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>

using namespace std;

namespace utils {
    void printArray(const int arr[], int size) {
        cout << "[ ";
        for (int i = 1; i <= size; i++) {
            cout << arr[i] << " ";
        }
        cout << "]" << endl;
    }

    void generateRandomArray(int arr[], int size, int max_value) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, max_value);

        for (int i = 1; i <= size; i++) {
            arr[i] = dis(gen);
        }
    }

    void generateAscendingArray(int arr[], int size) {
        for (int i = 1; i <= size; i++) {
            arr[i] = i;
        }
    }

    void generateDescendingArray(int arr[], int size) {
        for (int i = 1; i <= size; i++) {
            arr[i] = size - i + 1;
        }
    }

    void copyArray(const int source[], int dest[], int size) {
        for (int i = 1; i <= size; i++) {
            dest[i] = source[i];
        }
    }

    sorting::SortStats testSort(void (*sortFunc)(int[], int), int arr[], int size) {
        sorting::SortStats stats = {0, 0, 0.0};
        sorting::resetStats();
        
        int* arrCopy = new int[size + 1];
        copyArray(arr, arrCopy, size);
        
        try {
            auto start = chrono::high_resolution_clock::now();
            sortFunc(arrCopy, size);
            auto end = chrono::high_resolution_clock::now();
            
            stats.timeInSeconds = chrono::duration<double>(end - start).count();
            stats.comparisons = sorting::getComparisons();
            stats.movements = sorting::getMovements();
        }
        catch (...) {
            delete[] arrCopy;
            throw;
        }
        
        delete[] arrCopy;
        return stats;
    }

    sorting::SortStats testQuickSort(int arr[], int size) {
        sorting::SortStats stats = {0, 0, 0.0};
        
        sorting::resetStats(); // Reseta os contadores antes de começar
        
        auto start = chrono::high_resolution_clock::now();
        sorting::quickSort(arr, 1, size);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> diff = end - start;
        stats.timeInSeconds = diff.count();

        stats.comparisons = sorting::getComparisons();
        stats.movements = sorting::getMovements();

        return stats;
    }

    void exportResults(const std::string& algorithm_name,
                      const std::vector<int>& sizes,
                      const std::vector<sorting::SortStats>& stats,
                      const std::string& array_type,
                      const std::string& filename) {
        static bool headers_written = false;
        std::ofstream file(filename, std::ios::app);
        
        if (!headers_written) {
            file << "Algorithm,ArrayType,Size,Comparisons,Movements,Time\n";
            headers_written = true;
        }

        for (size_t i = 0; i < sizes.size(); i++) {
            file << algorithm_name << ","
                 << array_type << ","
                 << sizes[i] << ","
                 << std::fixed << stats[i].comparisons << ","
                 << std::fixed << stats[i].movements << ","
                 << std::fixed << std::setprecision(6) << stats[i].timeInSeconds
                 << "\n";
        }
        
        file.close();
    }
}