//25K-0610, Muhammad Siddique
#include <iostream>

using namespace std;

struct Player {
    int id;
    int energy;
    char history[100]; 
    int historyTop;
    bool active;
};

class GameQueue {
private:
    Player* players;
    int front, rear, currentCount, capacity;
    int* eliminationOrder;
    int elimCount;

public:
    GameQueue(int maxPlayers) {
        capacity = maxPlayers;
        players = new Player[capacity];
        eliminationOrder = new int[capacity];
        front = 0; rear = -1; currentCount = 0; elimCount = 0;
    }

    ~GameQueue() {
        delete[] players;
        delete[] eliminationOrder;
    }

    void enqueue(int id) {
        if (currentCount == capacity) return;
        rear = (rear + 1) % capacity;
        players[rear].id = id;
        players[rear].energy = 100;
        players[rear].historyTop = -1; 
        players[rear].active = true;
        currentCount++;
    }

    void processCommands(int turns) {
        int processedTurns = 0;
        
        while (processedTurns < turns && currentCount > 0) {
            Player& p = players[front];
            
            if (!p.active) { 
                front = (front + 1) % capacity;
                continue; 
            }

            char cmd;
            cout << "Turn " << (processedTurns + 1) << " (Player " << p.id << "): ";
            cin >> cmd;

            if (cmd == 'F') { p.energy -= 10; p.history[++p.historyTop] = 'F'; } 
            else if (cmd == 'T') { p.energy += 20; p.history[++p.historyTop] = 'T'; } 
            else if (cmd == 'B') { p.history[++p.historyTop] = 'B'; } 
            else if (cmd == 'U' && p.historyTop >= 0) { 
                char lastAction = p.history[p.historyTop--];
                if (lastAction == 'F') p.energy += 10;
                else if (lastAction == 'T') p.energy -= 20;
            }

            if (p.energy <= 0) {
                p.active = false;
                eliminationOrder[elimCount++] = p.id;
                currentCount--;
            }

            front = (front + 1) % capacity;
            processedTurns++; 
        }
    }

    void displayResults() {
        cout << "\n=== GAME OVER REPORT ===\n";
        cout << "Elimination Order: ";
        if (elimCount == 0) cout << "None";
        for (int i = 0; i < elimCount; i++) cout << eliminationOrder[i] << " ";
        cout << "\n\nActive Players Remaining in Line:\n";
        
        for (int i = 0; i < capacity; i++) {
            int idx = (front + i) % capacity;
            if (players[idx].active) {
                cout << "Player ID: " << players[idx].id 
                     << " | Energy: " << players[idx].energy 
                     << " | Undos Available: " << (players[idx].historyTop + 1) << endl;
            }
        }
    }
};

int main() {
    int numPlayers, commandsToProcess;
    cout << "Enter number of players: ";
    cin >> numPlayers;

    GameQueue game(numPlayers);

    for (int i = 1; i <= numPlayers; i++) {
        game.enqueue(i); 
    }

    cout << "Enter total turns to play: ";
    cin >> commandsToProcess;

    game.processCommands(commandsToProcess);
    game.displayResults();

    return 0;
}