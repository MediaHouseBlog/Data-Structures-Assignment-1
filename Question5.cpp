//25K-0610, Muhammad Siddique
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Product {
    int id;
    string name;
    string category;
    double price;
    Product* next;
};

class BranchList {
public:
    Product* head;
    string branchName;

    BranchList(string name) : head(nullptr), branchName(name) {}

    ~BranchList() {
        clearList();
    }

    void clearList() {
        Product* current = head;
        while (current != nullptr) {
            Product* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    bool isEmpty() { return head == nullptr; }

    void insertSorted(int id, string name, string category, double price) {
        Product* newNode = new Product{id, name, category, price, nullptr};
        
        if (isEmpty() || head->id > id) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Product* current = head;
        while (current->next != nullptr && current->next->id < id) {
            current = current->next;
        }
        
        if (current->id == id || (current->next && current->next->id == id)) {
            cout << "Product ID " << id << " already exists in " << branchName << ".\n";
            delete newNode;
            return;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void displayList() {
        cout << "\n--- " << branchName << " Inventory ---\n";
        if (isEmpty()) {
            cout << "No products available.\n";
            return;
        }
        
        Product* temp = head;
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Category" << "Price" << endl;
        cout << "---------------------------------------------------------\n";
        while (temp) {
            cout << left << setw(10) << temp->id << setw(20) << temp->name 
                 << setw(15) << temp->category << "$" << temp->price << endl;
            temp = temp->next;
        }
    }
};

BranchList* mergeBranchesInPlace(BranchList& b1, BranchList& b2) {
    BranchList* master = new BranchList("Master Consolidated List");
    
    Product dummy{0, "", "", 0.0, nullptr};
    Product* tail = &dummy;

    Product* p1 = b1.head;
    Product* p2 = b2.head;

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->id < p2->id) {
            tail->next = p1;
            p1 = p1->next;
        } else if (p2->id < p1->id) {
            tail->next = p2;
            p2 = p2->next;
        } else {
            if (p1->price <= p2->price) {
                tail->next = p1;
                Product* toDelete = p2;
                p2 = p2->next;
                delete toDelete; 
                p1 = p1->next;
            } else {
                tail->next = p2;
                Product* toDelete = p1;
                p1 = p1->next;
                delete toDelete;
                p2 = p2->next;
            }
        }
        tail = tail->next;
    }

    tail->next = (p1 != nullptr) ? p1 : p2;
    master->head = dummy.next;

    b1.head = nullptr;
    b2.head = nullptr;

    return master;
}

int main() {
    BranchList glowCare("GlowCare");
    BranchList beautyHub("BeautyHub");
    BranchList* masterList = nullptr;

    int choice;
    do {
        cout << "\n1. Add to GlowCare\n2. Add to BeautyHub\n3. Show GlowCare\n4. Show BeautyHub\n5. Merge Branches In-Place\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            int id; string name, cat; double price;
            cout << "Enter ID, Name, Category, Price: ";
            cin >> id >> name >> cat >> price;
            if (choice == 1) glowCare.insertSorted(id, name, cat, price);
            else beautyHub.insertSorted(id, name, cat, price);
        }
        else if (choice == 3) glowCare.displayList();
        else if (choice == 4) beautyHub.displayList();
        else if (choice == 5) {
            masterList = mergeBranchesInPlace(glowCare, beautyHub);
            masterList->displayList();
            cout << "Original branch lists have been safely rewired into the Master List.\n";
        }
    } while (choice != 0);

    if (masterList) delete masterList;
    return 0;
}