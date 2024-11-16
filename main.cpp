#include "sorting.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <filesystem>

using namespace std;

// Função auxiliar para testar um algoritmo específico
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

    if (choice == 2) {
        // Criar diretório 'data' se não existir
        filesystem::create_directory("../data");
        
        // Atualizar caminhos dos arquivos
        vector<string> fileNames = {
            "../data/ascending_resultados.csv",
            "../data/descending_resultados.csv",
            "../data/random_resultados.csv"
        };
        
        for (const auto& fileName : fileNames) {
            ofstream clearFile(fileName, ios::trunc);
            clearFile.close();
        }

        // Tamanhos menores para todos os algoritmos
        vector<int> sizes = {1000, 5000, 10000, 50000, 100000};
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