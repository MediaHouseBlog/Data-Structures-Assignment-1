//25K-0610, Muhammad Siddique
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Combatant {
    string name;
    int hp;
    int ap;
    Combatant* prev;
    Combatant* next;
};

class Team {
private:
    Combatant* head;
    Combatant* tail;
    int size;

public:
    Team() : head(nullptr), tail(nullptr), size(0) {}

    ~Team() {
        while (head) {
            Combatant* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addMember(string name, int hp, int ap) {
        Combatant* newNode = new Combatant{name, hp, ap, nullptr, nullptr};
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    int getSize() { return size; }

    Combatant* getMemberByName(string name) {
        Combatant* temp = head;
        while (temp) {
            if (temp->name == name) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    Combatant* getMemberByPosition(int pos) {
        if (pos < 1 || pos > size) return nullptr;
        Combatant* temp = head;
        for (int i = 1; i < pos; i++) temp = temp->next;
        return temp;
    }

    Combatant* getRandomMember() {
        if (size == 0) return nullptr;
        int steps = rand() % size;
        Combatant* temp = head;
        while (steps--) temp = temp->next;
        return temp;
    }

    void removeDead(Combatant* c) {
        if (!c) return;
        
        if (c->prev) c->prev->next = c->next;
        else head = c->next;

        if (c->next) c->next->prev = c->prev;
        else tail = c->prev;

        delete c;
        size--;
    }

    bool isEliminated() { return size == 0; }

    int getTotalHP() {
        int total = 0;
        Combatant* temp = head;
        while (temp) {
            total += temp->hp;
            temp = temp->next;
        }
        return total;
    }

    void displayNames() {
        Combatant* temp = head;
        int i = 1;
        while (temp) {
            cout << i++ << ". " << temp->name << "  ";
            temp = temp->next;
        }
        cout << endl;
    }

    void displayFullStats() {
        Combatant* temp = head;
        while (temp) {
            cout << "[" << temp->name << " | HP: " << temp->hp << " | AP: " << temp->ap << "]\n";
            temp = temp->next;
        }
    }
};

Combatant* selectCombatant(Team& team, string prompt) {
    int choice;
    cout << prompt << " (1 for Position, 2 for Name): ";
    cin >> choice;
    if (choice == 1) {
        int pos; cout << "Enter position: "; cin >> pos;
        return team.getMemberByPosition(pos);
    } else {
        string name; cout << "Enter name: "; cin >> name;
        return team.getMemberByName(name);
    }
}

int main() {
    srand(time(0)); 
    Team heroes, enemies;
    
    heroes.addMember("Knight", 70, 5);
    heroes.addMember("Archer", 50, 4);
    heroes.addMember("Mage", 40, 5);
    heroes.addMember("Healer", 45, 2);
    heroes.addMember("Rogue", 55, 4);

    enemies.addMember("Goblin", 30, 2);
    enemies.addMember("Orc", 60, 4);
    enemies.addMember("Troll", 70, 3);
    enemies.addMember("Dragon", 70, 5);
    enemies.addMember("Witch", 40, 4);

    int round = 1;
    bool gameOver = false;

    cout << "=== TURN-BASED BATTLE SIMULATOR ===\n";

    while (!gameOver && round <= 20) { 
        cout << "\n--- Round " << round << " ---\n";
        
        cout << "Heroes Alive: "; heroes.displayNames();
        cout << "Enemies Alive: "; enemies.displayNames();
        
        cout << "\n[Player Turn]\n";
        Combatant* attacker = nullptr;
        while (!attacker) {
            attacker = selectCombatant(heroes, "Select Attacker");
            if (!attacker) cout << "Invalid selection. Try again.\n";
        }
        
        Combatant* target = nullptr;
        while (!target) {
            target = selectCombatant(enemies, "Select Target");
            if (!target) cout << "Invalid selection. Try again.\n";
        }

        int damage = attacker->ap * ((rand() % 3) + 1);
        cout << attacker->name << " attacks " << target->name << " for " << damage << " damage!\n";
        target->hp -= damage;
        
        if (target->hp <= 0) {
            cout << target->name << " has been eliminated!\n";
            enemies.removeDead(target);
            if (enemies.isEliminated()) { gameOver = true; break; }
        }

        cout << "\n[Enemy Turn]\n";
        Combatant* eAttacker = enemies.getRandomMember();
        Combatant* hTarget = heroes.getRandomMember();

        if (eAttacker && hTarget) {
            int eDamage = eAttacker->ap * ((rand() % 3) + 1);
            cout << eAttacker->name << " attacks " << hTarget->name << " for " << eDamage << " damage!\n";
            hTarget->hp -= eDamage;

            if (hTarget->hp <= 0) {
                cout << hTarget->name << " has been eliminated!\n";
                heroes.removeDead(hTarget);
                if (heroes.isEliminated()) { gameOver = true; break; }
            }
        }

        if (round >= 10) {
            char choice;
            cout << "\nMinimum rounds reached. End battle early and calculate winner by HP? (Y/N): ";
            cin >> choice;
            if (choice == 'Y' || choice == 'y') gameOver = true;
        }
        round++;
    }

    cout << "\n=== BATTLE CONCLUDED ===\n";
    if (heroes.isEliminated()) {
        cout << "ENEMIES WIN BY ELIMINATION!\nSurviving Enemies:\n";
        enemies.displayFullStats();
    } else if (enemies.isEliminated()) {
        cout << "HEROES WIN BY ELIMINATION!\nSurviving Heroes:\n";
        heroes.displayFullStats();
    } else {
        int hHP = heroes.getTotalHP();
        int eHP = enemies.getTotalHP();
        cout << "Time Limit Reached! Total Hero HP: " << hHP << " | Total Enemy HP: " << eHP << "\n";
        
        if (hHP > eHP) {
            cout << "HEROES WIN BY HP ADVANTAGE!\nRemaining Team:\n";
            heroes.displayFullStats();
        } else if (eHP > hHP) {
            cout << "ENEMIES WIN BY HP ADVANTAGE!\nRemaining Team:\n";
            enemies.displayFullStats();
        } else {
            cout << "MATCH ENDS IN A DRAW!\nHeroes:\n";
            heroes.displayFullStats();
            cout << "Enemies:\n";
            enemies.displayFullStats();
        }
    }
    return 0;
}