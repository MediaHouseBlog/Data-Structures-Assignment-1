//25K-0610, Muhammad Siddique
#include <iostream>

using namespace std;

struct MoveNode {
    char moveType;
    int value; 
    MoveNode* next;
};

class MoveStack {
private:
    MoveNode* top;
    int successMoves;
    int undoMoves;

public:
    MoveStack() : top(nullptr), successMoves(0), undoMoves(0) {}

    ~MoveStack() {
        while (top) {
            MoveNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(char type, int val) {
        MoveNode* newNode = new MoveNode{type, val, top};
        top = newNode;
        successMoves++;
    }

    int pop() {
        if (!top) return 0; 
        int val = top->value;
        MoveNode* temp = top;
        top = top->next;
        delete temp;
        
        undoMoves++;
        successMoves--; 
        return val;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void displayRemainingStack() {
        cout << "Remaining valid moves in stack (Top to Bottom): ";
        if (isEmpty()) {
            cout << "Empty\n";
            return;
        }
        MoveNode* temp = top;
        while (temp) {
            cout << temp->moveType << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    int getSuccessCount() { return successMoves; }
    int getUndoCount() { return undoMoves; }
};

int main() {
    MoveStack undoStack;
    int pos = 0;
    int n;

    cout << "--- UNDO BATTLE GAME ---\n";
    cout << "Rules: Start at 0. R(+1), L(-1), J(+2), B(Undo). Cannot go < 0.\n";
    cout << "Enter number of commands to execute: ";
    cin >> n;

    cout << "Enter the sequence of commands (space-separated or consecutive): ";
    for (int i = 0; i < n; i++) {
        char cmd;
        cin >> cmd;

        if (cmd == 'R') {
            pos += 1;
            undoStack.push('R', 1);
        } 
        else if (cmd == 'J') {
            pos += 2;
            undoStack.push('J', 2);
        } 
        else if (cmd == 'L') {
            if (pos - 1 >= 0) {
                pos -= 1;
                undoStack.push('L', -1);
            } else {
                cout << "Warning: Command L ignored to prevent negative position.\n";
            }
        } 
        else if (cmd == 'B') {
            if (!undoStack.isEmpty()) {
                int reversedValue = undoStack.pop();
                pos -= reversedValue; 
            } else {
                cout << "Warning: Stack is empty, nothing to undo.\n";
            }
        } else {
            cout << "Invalid command encountered: " << cmd << "\n";
        }
    }

    cout << "\n=== GAME RESULTS ===\n";
    cout << "Final Position: " << pos << endl;
    cout << "Total Successful Movements (currently active): " << undoStack.getSuccessCount() << endl;
    cout << "Total Undo Operations Performed: " << undoStack.getUndoCount() << endl;
    undoStack.displayRemainingStack();

    return 0;
}