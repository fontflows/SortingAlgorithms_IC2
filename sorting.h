#ifndef SORTING_H
#define SORTING_H

namespace sorting {
    struct SortStats {
        long long comparisons;
        long long movements;
        double timeInSeconds;
    };

    // Declaração das variáveis globais de comparações e movimentações
    extern long long comparisons;
    extern long long movements;

    // Funções para acessar as estatísticas
    long long getComparisons();
    long long getMovements();
    void resetStats();

    // Funções de ordenação
    void insertionSort(int arr[], int size);
    void binaryInsertionSort(int arr[], int size);
    void selectionSort(int arr[], int size);
    void bubbleSort(int arr[], int size);
    void heapSort(int arr[], int size);
    void mergeSort(int arr[], int size);
    void quickSort(int arr[], int left, int right);
}

#endif
