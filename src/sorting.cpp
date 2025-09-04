#include "sorting.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;
namespace SortingAlgorithms {

//Funcion swap
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int arr[], int size) {
    bool swapped;

    for(int i=0;i<size-1;i++){ 
        swapped=false;
        for(int j=0;j<size-i-1;j++){ 
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
      
        if (!swapped){
            break;
        }
    }     
}

void selectionSort(int arr[], int size) {
    for(int i=0;i<size;++i){
        int min=i; //El valor minimo del array

        for(int j=i+1;j<size;++j){
            if(arr[j]<arr[min]){ //Si el valor del valor en j es menor al valor minimo
                min=j; //El valor de j se convierte en el minimo
            }
        }
        swap(arr[i],arr[min]);
    }         
}

void insertionSort(int arr[], int size) {
    for(int i=1;i<size;++i){
        int current=arr[i]; //Valor en el que estoy segun posicion i
        int j=i-1; //Posicion anterior a current

        while(j>=0&&arr[j]>current){
            arr[j+1]=arr[j]; //Agregando el valor anterior en current manteniendo la misma posición.
            j--;
        }
        arr[j+1]=current;//Agrega el valor de current en la posicion ordenada. 
    }    
}

void merge(int arr[], int l, int m, int r){
    int pl = m - l + 1; // Left part
    int pr = r - m;     // Right part

    // Arreglos temporales (vectores)
    vector<int> L(pl), R(pr);

    // Copiar los datos en los arreglos nuevos
    for (int i = 0; i < pl; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < pr; j++)
        R[j] = arr[m + 1 + j];

    // Contadores
    int i = 0, j = 0, k = l;

    // Mezclar L y R en arr
    while (i < pl && j < pr) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar elementos restantes de L
    while (i < pl) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar elementos restantes de R
    while (j < pr) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2; // evita overflow
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Pivote
    int i = low - 1;       // índice del elemento más pequeño

    // Mover a la izquierda los valores pequeños
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]); // usa std::swap
        }
    }

    // Colocar el pivote en su posición correcta
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Ordenar los elementos antes y después de la partición
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// void heapify(int arr[], int n, int i) {
    
// }

// void heapSort(int arr[], int n) {

void printArray(int arr[], int n) {
    if (n == 0) {
        std::cout << "[]" << std::endl;
        return;
    }
    
    std::cout << "[";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i];
        if (i < n - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

bool isSorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

void SortingTimer::start() {
    start_time = std::chrono::high_resolution_clock::now();
}

void SortingTimer::stop() {
    end_time = std::chrono::high_resolution_clock::now();
}

double SortingTimer::getElapsedMilliseconds() const {
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    return duration.count() / 1000.0;
}

std::string SortingTimer::getElapsedTime() const {
    double ms = getElapsedMilliseconds();
    std::stringstream ss;
    
    if (ms < 1.0) {
        ss << std::fixed << std::setprecision(3) << (ms * 1000) << " microseconds";
    } else if (ms < 1000.0) {
        ss << std::fixed << std::setprecision(3) << ms << " ms";
    } else {
        ss << std::fixed << std::setprecision(3) << (ms / 1000.0) << " seconds";
    }
    
    return ss.str();
}

std::vector<int> generateRandomArray(int size, int minVal, int maxVal) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minVal, maxVal);
    
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    
    return arr;
}

std::vector<int> generateSortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

std::vector<int> generateReverseSortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = size - i - 1;
    }
    return arr;
}

std::vector<int> generateNearlySortedArray(int size, int swaps) {
    std::vector<int> arr = generateSortedArray(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    
    for (int i = 0; i < swaps && i < size/2; i++) {
        int idx1 = dis(gen);
        int idx2 = dis(gen);
        std::swap(arr[idx1], arr[idx2]);
    }
    
    return arr;
}

}