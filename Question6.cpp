//25K-0610, Muhammad Siddique
#include <iostream>
#include <string>

using namespace std;

struct Song {
    string title;
    string genre;
    int duration;
    bool isExplicit;
    Song* next;
};

class Playlist {
private:
    Song* head;
    int operationCount;

    int getSegmentDuration(Song* s1, Song* s2, Song* s3) {
        int total = 0;
        if (s1) total += s1->duration;
        if (s2) total += s2->duration;
        if (s3) total += s3->duration;
        return total;
    }

    bool isValidPlacement(Song* prev, Song* newNode, Song* nextNode) {
        if (prev && prev->genre == newNode->genre) return false;
        if (nextNode && nextNode->genre == newNode->genre) return false;

        Song* prevPrev = nullptr;
        if (head && prev && prev != head) {
            Song* temp = head;
            while (temp && temp->next != prev) temp = temp->next;
            prevPrev = temp;
        }

        if (prevPrev && prev && getSegmentDuration(prevPrev, prev, newNode) > 600) return false;
        if (prev && nextNode && getSegmentDuration(prev, newNode, nextNode) > 600) return false;
        if (nextNode && nextNode->next && getSegmentDuration(newNode, nextNode, nextNode->next) > 600) return false;

        return true;
    }

    void enforceConstraints() {
        if (!head || !head->next) return;
        
        Song* curr = head->next;
        Song* prev = head;
        Song* prevPrev = nullptr;
        
        while (curr) {
            bool conflict = false;
            if (prev->genre == curr->genre) conflict = true;
            if (prevPrev && getSegmentDuration(prevPrev, prev, curr) > 600) conflict = true;

            if (conflict) {
                cout << "\n[Constraint Check] Conflict detected at '" << curr->title << "'. Rebalancing...\n";
                prev->next = curr->next;
                Song* detached = curr;
                curr = curr->next;
                detached->next = nullptr;
                
                Song* temp = head;
                Song* searchPrev = nullptr;
                bool inserted = false;
                
                while (temp) {
                    if (isValidPlacement(searchPrev, detached, temp)) {
                        detached->next = temp;
                        if (searchPrev) searchPrev->next = detached;
                        else head = detached;
                        inserted = true;
                        break;
                    }
                    searchPrev = temp;
                    temp = temp->next;
                }
                
                if (!inserted && isValidPlacement(searchPrev, detached, nullptr)) {
                    searchPrev->next = detached;
                    inserted = true;
                }
                
                if (!inserted) {
                    cout << "Could not find a valid position for '" << detached->title << "'. Song removed to preserve limits.\n";
                    delete detached;
                }
                
                curr = head->next;
                prev = head;
                prevPrev = nullptr;
                continue;
            }
            
            prevPrev = prev;
            prev = curr;
            curr = curr->next;
        }
    }

    void recordOperation() {
        operationCount++;
        if (operationCount % 3 == 0) {
            cout << "\n--- 3 Operations Reached: Verifying Playlist Constraints ---\n";
            enforceConstraints();
        }
    }

public:
    Playlist() : head(nullptr), operationCount(0) {}
    
    ~Playlist() {
        Song* temp = head;
        while (temp) {
            Song* nxt = temp->next;
            delete temp;
            temp = nxt;
        }
    }

    void insertSafe(string title, string genre, int duration, bool isExplicit, int desiredPos) {
        Song* newNode = new Song{title, genre, duration, isExplicit, nullptr};
        if (!head) {
            head = newNode;
            recordOperation();
            return;
        }

        Song* temp = head;
        Song* prev = nullptr;
        int currentPos = 1;

        while (temp && currentPos < desiredPos) {
            prev = temp;
            temp = temp->next;
            currentPos++;
        }

        if (isValidPlacement(prev, newNode, temp)) {
            newNode->next = temp;
            if (prev) prev->next = newNode;
            else head = newNode;
            recordOperation();
            return;
        }

        temp = head; prev = nullptr;
        while (temp) {
            if (isValidPlacement(prev, newNode, temp)) {
                newNode->next = temp;
                if (prev) prev->next = newNode;
                else head = newNode;
                recordOperation();
                return;
            }
            prev = temp; temp = temp->next;
        }

        if (isValidPlacement(prev, newNode, nullptr)) {
            prev->next = newNode;
            recordOperation();
        } else {
            cout << "Violates core constraints everywhere. Rejected.\n";
            delete newNode;
        }
    }

    void searchSong(string title) {
        Song* temp = head;
        int pos = 1;
        while (temp) {
            if (temp->title == title) {
                cout << "Found: '" << title << "' at Position " << pos 
                     << " [" << temp->genre << ", " << temp->duration << "s]\n";
                recordOperation();
                return;
            }
            temp = temp->next;
            pos++;
        }
        cout << "Song '" << title << "' not found.\n";
        recordOperation();
    }

    void removeExplicitFlag(string title) {
        Song* temp = head;
        while (temp) {
            if (temp->title == title) {
                if (temp->isExplicit) {
                    temp->isExplicit = false;
                    cout << "Explicit flag removed for '" << title << "'. You may now delete it.\n";
                } else {
                    cout << "Song is already clean.\n";
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Song not found.\n";
    }

    void deleteSong(string title) {
        if (!head) return;

        Song* temp = head;
        Song* prev = nullptr;

        while (temp && temp->title != title) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) { cout << "Not found.\n"; return; }
        if (temp->isExplicit) { cout << "Cannot directly delete EXPLICIT song.\n"; return; }

        if (prev) prev->next = temp->next;
        else head = temp->next;
        
        delete temp;
        cout << "Deleted.\n";
        recordOperation();
    }

    void display() {
        cout << "\n--- Current Playlist ---\n";
        Song* temp = head;
        int i = 1;
        while (temp) {
            cout << i++ << ". " << temp->title << " [" << temp->genre << "] - " 
                 << temp->duration << "s " << (temp->isExplicit ? "(EXPLICIT)" : "(CLEAN)") << endl;
            temp = temp->next;
        }
        cout << "------------------------\n";
    }
};

int main() {
    Playlist p;
    int choice;
    do {
        cout << "\n1. Add Song\n2. Delete Song\n3. Remove Explicit Flag\n4. View Playlist\n5. Search Song\n0. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            string t, g; int d, pos; bool exp;
            cout << "Title, Genre, Duration(s), Explicit(1/0), Desired Pos: ";
            cin >> t >> g >> d >> exp >> pos;
            p.insertSafe(t, g, d, exp, pos);
        } else if (choice == 2) {
            string t; cout << "Title to delete: "; cin >> t;
            p.deleteSong(t);
        } else if (choice == 3) {
            string t; cout << "Title to clean: "; cin >> t;
            p.removeExplicitFlag(t);
        } else if (choice == 4) {
            p.display();
        } else if (choice == 5) {
            string t; cout << "Title to search: "; cin >> t;
            p.searchSong(t);
        }
    } while (choice != 0);
    return 0;
}