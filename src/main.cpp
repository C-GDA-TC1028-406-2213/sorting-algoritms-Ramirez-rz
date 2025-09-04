#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>
#include "sorting.h"

using namespace SortingAlgorithms;
using namespace std;

void displayMenu() {
    cout << "\n========================================" << endl;
    cout << "    SORTING ALGORITHMS DEMONSTRATION    " << endl;
    cout << "========================================" << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. Selection Sort" << endl;
    cout << "3. Insertion Sort" << endl;
    cout << "4. Merge Sort" << endl;
    cout << "5. Quick Sort" << endl;
    cout << "6. Heap Sort" << endl;
    cout << "7. Compare All Algorithms" << endl;
    cout << "8. Load Data from File" << endl;
    cout << "9. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

void displayDataMenu() {
    cout << "\n--- Data Generation Options ---" << endl;
    cout << "1. Random Array" << endl;
    cout << "2. Already Sorted Array" << endl;
    cout << "3. Reverse Sorted Array" << endl;
    cout << "4. Nearly Sorted Array" << endl;
    cout << "5. Enter Custom Array" << endl;
    cout << "Enter your choice: ";
}

vector<int> getArrayFromUser() {
    int size;
    cout << "Enter array size: ";
    cin >> size;
    
    if (size <= 0) {
        cout << "Invalid size! Using default size of 10." << endl;
        size = 10;
    }
    
    int dataChoice;
    displayDataMenu();
    cin >> dataChoice;
    
    vector<int> arr;
    
    switch(dataChoice) {
        case 1:
            arr = generateRandomArray(size);
            break;
        case 2:
            arr = generateSortedArray(size);
            break;
        case 3:
            arr = generateReverseSortedArray(size);
            break;
        case 4:
            arr = generateNearlySortedArray(size);
            break;
        case 5: {
            arr.resize(size);
            cout << "Enter " << size << " integers:" << endl;
            for (int i = 0; i < size; i++) {
                cin >> arr[i];
            }
            break;
        }
        default:
            cout << "Invalid choice! Generating random array." << endl;
            arr = generateRandomArray(size);
    }
    
    return arr;
}

void performSort(int choice, int arr[], int n) {
    SortingTimer timer;
    string algorithmName;
    
    cout << "\nOriginal array (first 20 elements): ";
    int displaySize = min(n, 20);
    printArray(arr, displaySize);
    if (n > 20) cout << "... and " << (n - 20) << " more elements" << endl;
    
    timer.start();
    
    switch(choice) {
        case 1:
            bubbleSort(arr, n);
            algorithmName = "Bubble Sort";
            break;
        case 2:
            selectionSort(arr, n);
            algorithmName = "Selection Sort";
            break;
        case 3:
            insertionSort(arr, n);
            algorithmName = "Insertion Sort";
            break;
        case 4:
            mergeSort(arr, 0, n - 1);
            algorithmName = "Merge Sort";
            break;
        case 5:
            quickSort(arr, 0, n - 1);
            algorithmName = "Quick Sort";
            break;
        // case 6:
        //     heapSort(arr, n);
        //     algorithmName = "Heap Sort";
        //     break;
        default:
            cout << "Invalid choice!" << endl;
            return;
    }
    
    timer.stop();
    
    cout << "\nSorted array (first 20 elements): ";
    printArray(arr, displaySize);
    if (n > 20) cout << "... and " << (n - 20) << " more elements" << endl;
    
    cout << "\n" << algorithmName << " completed in: " << timer.getElapsedTime() << endl;
    
    if (isSorted(arr, n)) {
        cout << "Array is correctly sorted!" << endl;
    } else {
        cout << "WARNING: Array is NOT correctly sorted!" << endl;
    }
}

void compareAllAlgorithms() {
    int size;
    cout << "\nEnter array size for comparison: ";
    cin >> size;
    
    if (size <= 0) {
        cout << "Invalid size! Using default size of 100." << endl;
        size = 100;
    }
    
    vector<int> original = generateRandomArray(size);
    
    cout << "\n========================================" << endl;
    cout << "     ALGORITHM PERFORMANCE COMPARISON   " << endl;
    cout << "     Array Size: " << size << " elements" << endl;
    cout << "========================================" << endl;
    
    struct AlgorithmResult {
        string name;
        double time;
        bool correct;
    };
    
    vector<AlgorithmResult> results;
    
    vector<int> temp(size);
    SortingTimer timer;
    
    copy(original.begin(), original.end(), temp.begin());
    timer.start();
    bubbleSort(temp.data(), size);
    timer.stop();
    results.push_back({"Bubble Sort", timer.getElapsedMilliseconds(), isSorted(temp.data(), size)});
    
    copy(original.begin(), original.end(), temp.begin());
    timer.start();
    selectionSort(temp.data(), size);
    timer.stop();
    results.push_back({"Selection Sort", timer.getElapsedMilliseconds(), isSorted(temp.data(), size)});
    
    copy(original.begin(), original.end(), temp.begin());
    timer.start();
    insertionSort(temp.data(), size);
    timer.stop();
    results.push_back({"Insertion Sort", timer.getElapsedMilliseconds(), isSorted(temp.data(), size)});
    
    copy(original.begin(), original.end(), temp.begin());
    timer.start();
    mergeSort(temp.data(), 0, size - 1);
    timer.stop();
    results.push_back({"Merge Sort", timer.getElapsedMilliseconds(), isSorted(temp.data(), size)});
    
    copy(original.begin(), original.end(), temp.begin());
    timer.start();
    quickSort(temp.data(), 0, size - 1);
    timer.stop();
    results.push_back({"Quick Sort", timer.getElapsedMilliseconds(), isSorted(temp.data(), size)});
    
    // copy(original.begin(), original.end(), temp.begin());
    // timer.start();
    // heapSort(temp.data(), size);
    // timer.stop();
    // results.push_back({"Heap Sort", timer.getElapsedMilliseconds(), isSorted(temp.data(), size)});
    
    cout << "\n" << left << setw(20) << "Algorithm" 
         << setw(15) << "Time (ms)" 
         << setw(10) << "Status" << endl;
    cout << string(45, '-') << endl;
    
    for (const auto& result : results) {
        cout << left << setw(20) << result.name 
             << setw(15) << fixed << setprecision(3) << result.time
             << setw(10) << (result.correct ? "PASSED" : "FAILED") << endl;
    }
    
    cout << "\nNote: Results may vary based on system performance and current load." << endl;
}

vector<int> loadFromFile() {
    string filename;
    cout << "Enter filename (or 'default' for data/sample_data.txt): ";
    cin >> filename;
    
    if (filename == "default") {
        filename = "data/sample_data.txt";
    }
    
    ifstream file(filename);
    vector<int> arr;
    
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'" << endl;
        return arr;
    }
    
    int value;
    while (file >> value) {
        arr.push_back(value);
    }
    
    file.close();
    
    if (arr.empty()) {
        cout << "Warning: File was empty or contained no valid integers." << endl;
    } else {
        cout << "Successfully loaded " << arr.size() << " integers from file." << endl;
    }
    
    return arr;
}

int main() {
    cout << "Welcome to the Sorting Algorithms Demonstration!" << endl;
    cout << "This program allows you to test and compare different sorting algorithms." << endl;
    
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }
        
        if (choice >= 1 && choice <= 6) {
            vector<int> arr = getArrayFromUser();
            if (!arr.empty()) {
                performSort(choice, arr.data(), arr.size());
            }
        } else if (choice == 7) {
            compareAllAlgorithms();
        } else if (choice == 8) {
            vector<int> arr = loadFromFile();
            if (!arr.empty()) {
                cout << "\nWhich algorithm would you like to use?" << endl;
                cout << "1. Bubble Sort" << endl;
                cout << "2. Selection Sort" << endl;
                cout << "3. Insertion Sort" << endl;
                cout << "4. Merge Sort" << endl;
                cout << "5. Quick Sort" << endl;
                // cout << "6. Heap Sort" << endl;
                cout << "Enter choice: ";
                int sortChoice;
                cin >> sortChoice;
                performSort(sortChoice, arr.data(), arr.size());
            }
        } else if (choice == 9) {
            cout << "\nThank you for using the Sorting Algorithms Demonstration!" << endl;
            cout << "Goodbye!" << endl;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
        
    } while (choice != 9);
    
    return 0;
}