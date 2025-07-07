#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

string get_save_path() {
    const char* home = getenv("HOME");
    return string(home ? home : ".") + "/.save.txt";
}

void save_game(int health, int gold, int health_potion, int level) {
    ofstream file(get_save_path());
    if (file.is_open()) {
        file << health << " " << gold << " " << health_potion << " " << level << "\n";
        file.close();
        cout << "Game saved.\n";
    } else {
        cout << "Could not save game.\n";
    }
}

void load_game(int &health, int &gold, int &health_potion, int &level) {
    ifstream file(get_save_path());
    if (file.is_open()) {
        file >> health >> gold >> health_potion >> level;
        file.close();
        cout << "Game loaded.\n";
    } else {
        cout << "No save file found.\n";
    }
}

int main() {
	
    ////////////////////	
    ////Player stats////
    ////////////////////
    int health = 100;
    int gold = 25;
    int health_potion = 1;
    int level = 0;
    int max_health = 100;
    int level_cost = 1000;

    ///////////////////
    ////Enemy stats////
    ///////////////////
    int damage_take = 25;
    int gold_drop = 20;

    int x;

    while (true) {
	/////////////////////
        ////Level scaling////
	/////////////////////
        max_health = 100 + level * 50;
        damage_take = 25 + level * 10;
        gold_drop = 10 + level * 10;
        level_cost = 1000 + level * 1000;

        cout << "\n[1] Attack\n[2] Stats\n[3] Shop\n[4] Heal\n[5] Save\n[6] Load\n[0] Exit\n>> ";
        cin >> x;

        if (x == 1) {
            cout << "You attacked an enemy. Took " << damage_take << " damage, gained " << gold_drop << " gold.\n";
            health -= damage_take;
            gold += gold_drop;

            if (health <= 0) {
                cout << "You died! Resetting to level 0.\n";
                level = 0;
                health = 100;
                gold = 25;
                health_potion = 1;
            }
        } else if (x == 2) {
            cout << "\nHealth: " << health << "/" << max_health
            << "\nGold: " << gold
            << "\nPotions: " << health_potion
            << "\nLevel: " << level << "\n";
        } else if (x == 3) {
            int y;
            cout << "Shop:\n[1] Heal (15 gold)\n[2] Level Up (" << level_cost << " gold)\n>> ";
            cin >> y;
            if (y == 1) {
                if (gold < 15) {
                    cout << "Not enough gold.\n";
                } else {
                    cout << "Bought a health potion.\n";
                    health_potion += 1;
                    gold -= 15;
                }
            } else if (y == 2) {
                if (gold < level_cost) {
                    cout << "Not enough gold to level up.\n";
                } else {
                    cout << "You leveled up!\n";
                    level += 1;
                    gold -= level_cost;
                }
            }
        } else if (x == 4) {
            if (health >= max_health) {
                cout << "You are already at full health.\n";
            } else if (health_potion <= 0) {
                cout << "No health potions.\n";
            } else {
                cout << "Healed 15 health.\n";
                health += 15;
                if (health > max_health) health = max_health;
                health_potion -= 1;
            }
        } else if (x == 5) {
            save_game(health, gold, health_potion, level);
        } else if (x == 6) {
            load_game(health, gold, health_potion, level);
        } else if (x == 0) {
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
