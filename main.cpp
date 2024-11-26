#include "sorting.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <filesystem>

using namespace std;

void testAlgorithm(const string& name, void (*sortFunc)(int[], int),
                   const vector<int>& sizes, const string& arrayType) {
    vector<sorting::SortStats> stats;
    cout << "  " << name << "... " << flush;

    for (int size : sizes) {
        int* arr = new int[size + 1];
        
        if (arrayType == "ascending")
            utils::generateAscendingArray(arr, size);
        else if (arrayType == "descending")
            utils::generateDescendingArray(arr, size);
        else
            utils::generateRandomArray(arr, size);
        
        sorting::resetStats();
        
        auto start = chrono::high_resolution_clock::now();
        if (name == "Quicksort") {
            sorting::quickSort(arr, 1, size);
        } else {
            sortFunc(arr, size);
        }
        auto end = chrono::high_resolution_clock::now();
        
        sorting::SortStats stat;
        stat.comparisons = sorting::getComparisons();
        stat.movements = sorting::getMovements();
        stat.timeInSeconds = chrono::duration<double>(end - start).count();
        
        stats.push_back(stat);
        delete[] arr;
    }
    
    utils::exportResults(name, sizes, stats, arrayType, "../data/" + arrayType + "_resultados.csv");
    cout << "OK\n" << flush;
}

int main() {
    int choice;
    cout << "=== Programa de Ordenacao ===\n";
    cout << "1 - Teste com entrada manual (itens a e b)\n";
    cout << "2 - Analise de desempenho (item c)\n";
    cout << "Escolha uma opcao: ";
    cin >> choice;

    if (choice == 1) {
        int n;
        cout << "Digite o tamanho do vetor: ";
        cin >> n;

        int* arr = new int[n + 1];
        cout << "Digite os " << n << " elementos do vetor:\n";
        
        cin.ignore();
        
        for (int i = 1; i <= n; i++) {
            cout << "Elemento " << i << ": ";
            cin >> arr[i];
        }

        cout << "\nVetor original: ";
        utils::printArray(arr, n);
        cout << "\nResultados das ordenacoes:\n\n";

        int* temp = new int[n + 1];

        cout << "Insercao Direta: ";
        utils::copyArray(arr, temp, n);
        sorting::insertionSort(temp, n);
        utils::printArray(temp, n);

        cout << "Insercao Binaria: ";
        utils::copyArray(arr, temp, n);
        sorting::binaryInsertionSort(temp, n);
        utils::printArray(temp, n);

        cout << "Selecao: ";
        utils::copyArray(arr, temp, n);
        sorting::selectionSort(temp, n);
        utils::printArray(temp, n);

        cout << "Bubblesort: ";
        utils::copyArray(arr, temp, n);
        sorting::bubbleSort(temp, n);
        utils::printArray(temp, n);

        cout << "Heapsort: ";
        utils::copyArray(arr, temp, n);
        sorting::heapSort(temp, n);
        utils::printArray(temp, n);

        cout << "Mergesort: ";
        utils::copyArray(arr, temp, n);
        sorting::mergeSort(temp, n);
        utils::printArray(temp, n);

        cout << "Quicksort: ";
        utils::copyArray(arr, temp, n);
        sorting::quickSort(temp, 1, n);
        utils::printArray(temp, n);

        delete[] arr;
        delete[] temp;
    }

    else if (choice == 2) {
        filesystem::create_directory("../data");
        vector<string> fileNames = {
            "../data/ascending_resultados.csv",
            "../data/descending_resultados.csv",
            "../data/random_resultados.csv"
        };
        
        for (const auto& fileName : fileNames) {
            ofstream clearFile(fileName, ios::trunc);
            clearFile.close();
        }

        vector<int> sizes = {1000, 5000, 10000, 50000, 100000};
        //vector<int> sizes = {10, 20, 30, 40, 50};
        vector<string> arrayTypes = {"ascending", "descending", "random"};

        for (const auto& type : arrayTypes) {
            cout << "\nTestando arrays " << type << ":\n";
            testAlgorithm("Insercao Direta", sorting::insertionSort, sizes, type);
            testAlgorithm("Insercao Binaria", sorting::binaryInsertionSort, sizes, type);
            testAlgorithm("Selecao", sorting::selectionSort, sizes, type);
            testAlgorithm("Bubblesort", sorting::bubbleSort, sizes, type);
            testAlgorithm("Heapsort", sorting::heapSort, sizes, type);
            testAlgorithm("Fusao", sorting::mergeSort, sizes, type);
            testAlgorithm("Quicksort", nullptr, sizes, type);
        }

        cout << "\nTodos os testes foram concluidos!\n";
        cout << "Os resultados foram exportados para os arquivos 'ascending_resultados.csv', 'descending_resultados.csv' e 'random_resultados.csv'.\n";
    }

    return 0;
}