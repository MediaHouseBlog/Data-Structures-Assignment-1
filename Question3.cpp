//25K-0610, Muhammad Siddique
#include <iostream>
using namespace std;

void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

void combSort(int arr[], int size) {
    int gap = size;
    bool swapped = true;
    int pass = 1;

    while (gap > 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;

        swapped = false;
        for (int i = 0; i < size - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                int temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = true;
            }
        }
        cout << "Pass " << pass++ << " (Gap: " << gap << "): ";
        displayArray(arr, size);
    }
}

int main() {
    int size;
    cout << "Enter the number of packages: ";
    cin >> size;

    int* arr = new int[size];
    cout << "Enter the weights: ";
    for (int i = 0; i < size; i++) cin >> arr[i];

    cout << "\nOriginal array: ";
    displayArray(arr, size);

    combSort(arr, size);

    cout << "Final sorted array: ";
    displayArray(arr, size);

    delete[] arr;
    return 0;
}