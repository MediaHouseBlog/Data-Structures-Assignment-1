//25K-0610, Muhammad Siddique
#include <iostream>
using namespace std;

void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        
        cout << "After iteration " << i << ": ";
        displayArray(arr, size);
    }
}

int main() {
    int size;
    cout << "Enter the number of cables: ";
    cin >> size;
    
    int* arr = new int[size];
    cout << "Enter the cable lengths: ";
    for(int i = 0; i < size; i++) cin >> arr[i];

    cout << "\nOriginal array: ";
    displayArray(arr, size);

    insertionSort(arr, size);

    cout << "Final sorted array: ";
    displayArray(arr, size);
    
    delete[] arr;
    return 0;
}