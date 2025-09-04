
#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <chrono>
#include <string>

namespace SortingAlgorithms {
    
    void bubbleSort(int arr[], int n);
    
    void selectionSort(int arr[], int n);
    
    void insertionSort(int arr[], int n);
    
    void mergeSort(int arr[], int left, int right);
    
    void quickSort(int arr[], int low, int high);
    
    //void heapSort(int arr[], int n);
    
    void printArray(int arr[], int n);
    
    void copyArray(int source[], int dest[], int n);
    
    bool isSorted(int arr[], int n);
    
    class SortingTimer {
    private:
        std::chrono::high_resolution_clock::time_point start_time;
        std::chrono::high_resolution_clock::time_point end_time;
        
    public:
        void start();
        void stop();
        double getElapsedMilliseconds() const;
        std::string getElapsedTime() const;
    };
    
    std::vector<int> generateRandomArray(int size, int minVal = 0, int maxVal = 1000);
    
    std::vector<int> generateSortedArray(int size);
    
    std::vector<int> generateReverseSortedArray(int size);
    
    std::vector<int> generateNearlySortedArray(int size, int swaps = 5);
}

#endif