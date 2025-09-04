#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "../src/sorting.h"
#include "test_cases.h"

using namespace std;
using namespace SortingAlgorithms;

typedef void (*SortFunction)(int[], int);
typedef void (*SortFunctionRange)(int[], int, int);

struct SortingAlgorithm {
    string name;
    function<void(int[], int)> sort;
};

void runBubbleSort(int arr[], int n) {
    bubbleSort(arr, n);
}

void runSelectionSort(int arr[], int n) {
    selectionSort(arr, n);
}

void runInsertionSort(int arr[], int n) {
    insertionSort(arr, n);
}

void runMergeSort(int arr[], int n) {
    mergeSort(arr, 0, n - 1);
}

void runQuickSort(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

// void runHeapSort(int arr[], int n) {
//     heapSort(arr, n);
// }

bool testSortingAlgorithm(const SortingAlgorithm& algo, const TestCase& test) {
    int n = test.input.size();
    vector<int> arr = test.input;
    
    algo.sort(arr.data(), n);
    
    return equal(arr.begin(), arr.end(), test.expected.begin());
}

void runTestsForAlgorithm(const SortingAlgorithm& algo) {
    cout << "\n========================================" << endl;
    cout << "Testing: " << algo.name << endl;
    cout << "========================================" << endl;
    
    auto basicTests = TestSuite::getBasicTestCases();
    int passed = 0;
    int total = basicTests.size();
    
    for (const auto& test : basicTests) {
        bool result = testSortingAlgorithm(algo, test);
        TestSuite::printTestResult(test.name, result);
        if (result) passed++;
    }
    
    TestSuite::printTestSummary(passed, total);
}

void runAllTests() {
    vector<SortingAlgorithm> algorithms = {
        {"Bubble Sort", runBubbleSort},
        {"Selection Sort", runSelectionSort},
        {"Insertion Sort", runInsertionSort},
        {"Merge Sort", runMergeSort},
        {"Quick Sort", runQuickSort},
        // {"Heap Sort", runHeapSort}
    };
    
    cout << "\n****************************************" << endl;
    cout << "*    SORTING ALGORITHMS TEST SUITE    *" << endl;
    cout << "****************************************" << endl;
    
    int totalAlgoPassed = 0;
    
    for (const auto& algo : algorithms) {
        runTestsForAlgorithm(algo);
        
        auto basicTests = TestSuite::getBasicTestCases();
        bool algoPassedAll = true;
        for (const auto& test : basicTests) {
            if (!testSortingAlgorithm(algo, test)) {
                algoPassedAll = false;
                break;
            }
        }
        if (algoPassedAll) totalAlgoPassed++;
    }
    
    cout << "\n========================================" << endl;
    cout << "FINAL SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << "Algorithms with all tests passing: " << totalAlgoPassed << "/" << algorithms.size() << endl;
    
    if (totalAlgoPassed == algorithms.size()) {
        cout << "\033[32m" << "CONGRATULATIONS! All algorithms implemented correctly!" << "\033[0m" << endl;
    } else if (totalAlgoPassed > 0) {
        cout << "\033[33m" << "Some algorithms are working. Keep going!" << "\033[0m" << endl;
    } else {
        cout << "\033[31m" << "No algorithms are fully implemented yet." << "\033[0m" << endl;
        cout << "Start with Bubble Sort - it's the simplest!" << endl;
    }
}

void runSpecificTest(int algoChoice, int testChoice) {
    vector<SortingAlgorithm> algorithms = {
        {"Bubble Sort", runBubbleSort},
        {"Selection Sort", runSelectionSort},
        {"Insertion Sort", runInsertionSort},
        {"Merge Sort", runMergeSort},
        {"Quick Sort", runQuickSort},
        // {"Heap Sort", runHeapSort}
    };
    
    if (algoChoice < 1 || algoChoice > algorithms.size()) {
        cout << "Invalid algorithm choice!" << endl;
        return;
    }
    
    auto tests = TestSuite::getBasicTestCases();
    if (testChoice < 1 || testChoice > tests.size()) {
        cout << "Invalid test choice!" << endl;
        return;
    }
    
    const auto& algo = algorithms[algoChoice - 1];
    const auto& test = tests[testChoice - 1];
    
    cout << "\nTesting " << algo.name << " with test case: " << test.name << endl;
    cout << "Input array: ";
    for (int val : test.input) {
        cout << val << " ";
    }
    cout << endl;
    
    bool result = testSortingAlgorithm(algo, test);
    
    vector<int> arr = test.input;
    algo.sort(arr.data(), arr.size());
    
    cout << "Output array: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "Expected array: ";
    for (int val : test.expected) {
        cout << val << " ";
    }
    cout << endl;
    
    TestSuite::printTestResult(test.name, result);
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--verbose") == 0) {
            cout << "Running in verbose mode..." << endl;
        } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            cout << "Usage: " << argv[0] << " [options]" << endl;
            cout << "Options:" << endl;
            cout << "  -h, --help     Show this help message" << endl;
            cout << "  -v, --verbose  Run in verbose mode" << endl;
            cout << "  -i, --interactive  Run interactive test mode" << endl;
            return 0;
        } else if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--interactive") == 0) {
            cout << "Interactive Test Mode" << endl;
            cout << "Select Algorithm:" << endl;
            cout << "1. Bubble Sort" << endl;
            cout << "2. Selection Sort" << endl;
            cout << "3. Insertion Sort" << endl;
            cout << "4. Merge Sort" << endl;
            cout << "5. Quick Sort" << endl;
            cout << "6. Heap Sort" << endl;
            cout << "Enter choice: ";
            
            int algoChoice;
            cin >> algoChoice;
            
            cout << "\nSelect Test Case:" << endl;
            auto tests = TestSuite::getBasicTestCases();
            for (size_t i = 0; i < tests.size(); i++) {
                cout << (i + 1) << ". " << tests[i].name << endl;
            }
            cout << "Enter choice: ";
            
            int testChoice;
            cin >> testChoice;
            
            runSpecificTest(algoChoice, testChoice);
            return 0;
        }
    }
    
    runAllTests();
    
    return 0;
}