//25K-0610, Muhammad Siddique
#include <iostream>
using namespace std;

void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n;
    cout << "Enter number of shelves: ";
    cin >> n;

    int* shelves = new int[n];
    cout << "Enter book capacity of each shelf:\n";
    for (int i = 0; i < n; i++) cin >> shelves[i];

    int pos, newCapacity;
    cout << "Enter position to add the new shelf (0 to " << n << "): ";
    cin >> pos;
    cout << "Enter capacity of the new shelf: ";
    cin >> newCapacity;

    cout << "\nOriginal shelf capacities: ";
    for (int i = 0; i < n; i++) cout << shelves[i] << " ";
    cout << endl;

    int* newShelves = new int[n + 1];
    for (int i = 0, j = 0; i <= n; i++) {
        if (i == pos) {
            newShelves[i] = newCapacity;
        } else {
            newShelves[i] = shelves[j++];
        }
    }

    delete[] shelves;
    shelves = newShelves;
    n++;

    cout << "Shelves after adding new shelf: ";
    for (int i = 0; i < n; i++) cout << shelves[i] << " ";
    cout << endl;

    insertionSort(shelves, n);

    cout << "Shelves after sorting: ";
    for (int i = 0; i < n; i++) cout << shelves[i] << " ";
    cout << endl;

    delete[] shelves;
    return 0;
}