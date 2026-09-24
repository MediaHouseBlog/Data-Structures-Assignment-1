//25K-0610, Muhammad Siddique
#include <iostream>
#include <string>

using namespace std;

class PatientQueue {
private:
    int* queueArr;
    int frontIndex;
    int rearIndex;
    int capacity;
    int currentCount;

public:
    PatientQueue(int size = 100) {
        capacity = size;
        queueArr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        currentCount = 0;
    }

    ~PatientQueue() {
        delete[] queueArr;
    }

    PatientQueue(const PatientQueue& other) {
        capacity = other.capacity;
        frontIndex = other.frontIndex;
        rearIndex = other.rearIndex;
        currentCount = other.currentCount;
        queueArr = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            queueArr[i] = other.queueArr[i];
        }
    }

    PatientQueue& operator=(const PatientQueue& other) {
        if (this != &other) {
            delete[] queueArr;
            capacity = other.capacity;
            frontIndex = other.frontIndex;
            rearIndex = other.rearIndex;
            currentCount = other.currentCount;
            queueArr = new int[capacity];
            for (int i = 0; i < capacity; i++) queueArr[i] = other.queueArr[i];
        }
        return *this;
    }

    void enqueue(int id) {
        if (isFull()) {
            cout << "Queue Capacity Reached!\n";
            return;
        }
        rearIndex = (rearIndex + 1) % capacity;
        queueArr[rearIndex] = id;
        currentCount++;
    }

    int dequeue() {
        if (isEmpty()) return -1;
        int id = queueArr[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        currentCount--;
        return id;
    }

    bool isEmpty() const { return currentCount == 0; }
    bool isFull() const { return currentCount == capacity; }
    int getCount() const { return currentCount; }
};

void resizeOrderArray(int*& arr, int& capacity) {
    int newCapacity = capacity * 2;
    int* newArr = new int[newCapacity];
    for (int i = 0; i < capacity; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    capacity = newCapacity;
}

int main() {
    PatientQueue criticalQ(100), seriousQ(100), normalQ(100);
    string command;
    int totalTreated = 0;
    
    int orderCapacity = 5; 
    int* treatmentOrder = new int[orderCapacity]; 
    int tIndex = 0;

    cout << "=== EMERGENCY ROOM SIMULATOR ===\n";
    cout << "Input format: ARRIVE <ID> <1, 2, or 3> | TREAT | END\n";

    while (cin >> command && command != "END") {
        if (command == "ARRIVE") {
            int id, severity; cin >> id >> severity;
            if (severity == 1) criticalQ.enqueue(id);
            else if (severity == 2) seriousQ.enqueue(id);
            else if (severity == 3) normalQ.enqueue(id);
            else cout << "Invalid severity level.\n";
        } 
        else if (command == "TREAT") {
            int treatedId = -1;
            
            if (!criticalQ.isEmpty()) treatedId = criticalQ.dequeue();
            else if (!seriousQ.isEmpty()) treatedId = seriousQ.dequeue();
            else if (!normalQ.isEmpty()) treatedId = normalQ.dequeue();
            else cout << "No patients waiting to be treated.\n";

            if (treatedId != -1) {
                if (tIndex == orderCapacity) {
                    resizeOrderArray(treatmentOrder, orderCapacity);
                }
                treatmentOrder[tIndex++] = treatedId;
                totalTreated++;
            }
        }
    }

    cout << "\n=== END OF DAY REPORT ===\n";
    cout << "Treatment Order: ";
    if (tIndex == 0) cout << "None";
    for (int i = 0; i < tIndex; i++) cout << treatmentOrder[i] << " ";
    cout << "\n\nTotal Patients Treated: " << totalTreated << endl;
    
    int remainingTotal = criticalQ.getCount() + seriousQ.getCount() + normalQ.getCount();
    cout << "Total Patients Remaining: " << remainingTotal << endl;
    cout << " - Critical waiting: " << criticalQ.getCount() << endl;
    cout << " - Serious waiting: " << seriousQ.getCount() << endl;
    cout << " - Normal waiting: " << normalQ.getCount() << endl;

    delete[] treatmentOrder;
    return 0;
}