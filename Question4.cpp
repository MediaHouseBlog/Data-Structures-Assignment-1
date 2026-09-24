//25K-0610, Muhammad Siddique
#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Rider {
    int id;
    string name;
    int orders;
    Rider* next; 
};

class RiderList {
private:
    Rider* head;
    int totalRiders;

    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    RiderList() {
        head = nullptr;
        totalRiders = 0;
    }

    ~RiderList() {
        if (!head) return;
        Rider* temp = head;
        do {
            Rider* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);
        head = nullptr;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void insertAtBeginning(int id, string name, int orders) {
        Rider* newNode = new Rider{id, name, orders, nullptr};
        if (isEmpty()) {
            head = newNode;
            newNode->next = head;
        } else {
            Rider* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            newNode->next = head;
            temp->next = newNode;
            head = newNode;
        }
        totalRiders++;
        cout << "Rider inserted at beginning successfully.\n";
    }

    void insertAtEnd(int id, string name, int orders) {
        Rider* newNode = new Rider{id, name, orders, nullptr};
        if (isEmpty()) {
            head = newNode;
            newNode->next = head;
        } else {
            Rider* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
        totalRiders++;
        cout << "Rider inserted at end successfully.\n";
    }

    void insertAtPosition(int id, string name, int orders, int pos) {
        if (pos <= 1) {
            insertAtBeginning(id, name, orders);
            return;
        }
        if (pos > totalRiders) {
            insertAtEnd(id, name, orders);
            return;
        }

        Rider* newNode = new Rider{id, name, orders, nullptr};
        Rider* temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        totalRiders++;
        cout << "Rider inserted at position " << pos << ".\n";
    }

    void deleteFromBeginning() {
        if (isEmpty()) {
            cout << "List is empty.\n";
            return;
        }
        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Rider* temp = head;
            Rider* last = head;
            while (last->next != head) {
                last = last->next;
            }
            head = head->next;
            last->next = head;
            delete temp;
        }
        totalRiders--;
        cout << "Deleted from beginning.\n";
    }

    void deleteFromEnd() {
        if (isEmpty()) {
            cout << "List is empty.\n";
            return;
        }
        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Rider* temp = head;
            Rider* prev = nullptr;
            while (temp->next != head) {
                prev = temp;
                temp = temp->next;
            }
            prev->next = head;
            delete temp;
        }
        totalRiders--;
        cout << "Deleted from end.\n";
    }

    void deleteFromPosition(int pos) {
        if (isEmpty() || pos < 1 || pos > totalRiders) {
            cout << "Invalid position or empty list.\n";
            return;
        }
        if (pos == 1) {
            deleteFromBeginning();
            return;
        }
        if (pos == totalRiders) {
            deleteFromEnd();
            return;
        }

        Rider* temp = head;
        Rider* prev = nullptr;
        for (int i = 1; i < pos; i++) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        delete temp;
        totalRiders--;
        cout << "Deleted rider at position " << pos << ".\n";
    }

    void searchRider(int id) {
        if (isEmpty()) {
            cout << "List is empty.\n";
            return;
        }
        Rider* temp = head;
        int pos = 1;
        do {
            if (temp->id == id) {
                cout << "Found at position " << pos << " - [ID: " << temp->id << " | Name: " << temp->name << " | Orders: " << temp->orders << "]\n";
                return;
            }
            temp = temp->next;
            pos++;
        } while (temp != head);
        cout << "Rider ID " << id << " not found.\n";
    }

    void updateRider(int id, string newName, int newOrders) {
        if (isEmpty()) return;
        Rider* temp = head;
        do {
            if (temp->id == id) {
                temp->name = newName;
                temp->orders = newOrders;
                cout << "Rider updated successfully.\n";
                return;
            }
            temp = temp->next;
        } while (temp != head);
        cout << "Rider not found to update.\n";
    }

    void countRiders() {
        cout << "Total Active Riders: " << totalRiders << endl;
    }

    void displayAll() {
        if (isEmpty()) {
            cout << "No riders to display.\n";
            return;
        }
        Rider* temp = head;
        cout << "--- KFC Rider Roster ---\n";
        do {
            cout << "[ID: " << temp->id << " | Name: " << temp->name << " | Orders: " << temp->orders << "] -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(Points back to ID: " << head->id << ")\n";
    }

    void traverseFrom(int id) {
        if (isEmpty()) return;
        Rider* temp = head;
        Rider* startNode = nullptr;
        
        do {
            if (temp->id == id) {
                startNode = temp;
                break;
            }
            temp = temp->next;
        } while (temp != head);

        if (!startNode) {
            cout << "Starting Rider ID not found.\n";
            return;
        }

        cout << "Traversing starting from Rider ID " << id << ":\n";
        temp = startNode;
        do {
            cout << temp->name << " -> ";
            temp = temp->next;
        } while (temp != startNode);
        cout << "(Loop Complete)\n";
    }
};

int main() {
    RiderList kfcRiders;
    int choice, id, orders, pos;
    string name;

    do {
        cout << "\n--- KFC Rider Management System ---\n";
        cout << "1. Insert at Beginning\n2. Insert at End\n3. Insert at Position\n";
        cout << "4. Delete from Beginning\n5. Delete from End\n6. Delete from Position\n";
        cout << "7. Search Rider\n8. Update Rider\n9. Display All Riders\n";
        cout << "10. Count Total Riders\n11. Traverse from Specific Rider\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ID, Name, Orders: ";
                cin >> id >> name >> orders;
                kfcRiders.insertAtBeginning(id, name, orders);
                break;
            case 2:
                cout << "Enter ID, Name, Orders: ";
                cin >> id >> name >> orders;
                kfcRiders.insertAtEnd(id, name, orders);
                break;
            case 3:
                cout << "Enter ID, Name, Orders, Position: ";
                cin >> id >> name >> orders >> pos;
                kfcRiders.insertAtPosition(id, name, orders, pos);
                break;
            case 4: kfcRiders.deleteFromBeginning(); break;
            case 5: kfcRiders.deleteFromEnd(); break;
            case 6:
                cout << "Enter position to delete: ";
                cin >> pos;
                kfcRiders.deleteFromPosition(pos);
                break;
            case 7:
                cout << "Enter ID to search: ";
                cin >> id;
                kfcRiders.searchRider(id);
                break;
            case 8:
                cout << "Enter ID to update, New Name, New Orders: ";
                cin >> id >> name >> orders;
                kfcRiders.updateRider(id, name, orders);
                break;
            case 9: kfcRiders.displayAll(); break;
            case 10: kfcRiders.countRiders(); break;
            case 11:
                cout << "Enter starting Rider ID: ";
                cin >> id;
                kfcRiders.traverseFrom(id);
                break;
        }
    } while (choice != 0);
    return 0;
}