#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"

void Player::displayStats() const {
    using namespace std;

    cout << "<--------------------------------------->" << endl;
    cout << "Estadisticas del Jugador:" << endl;
    cout << "Name: " << name << endl;
    cout << "Health: " << health << endl;
    cout << "Attack: " << attack << endl;
    cout << "Defense: " << defense << endl;
    cout << "Speed: " << speed << endl;
    cout << "<-------------------------------------->" << endl;
}

int main() {
    Player *player = new Player("Solid", 40, 15, 8, 3);
    Enemy *enemy = new Enemy("Mogh", 15, 10, 5, 5, 10);
    Enemy *enemy2 = new Enemy("Malenia", 15, 10, 5, 5, 10);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    player->displayStats();

    combat->doCombat();

    delete player;
    delete enemy;
    delete combat;
    return 0;
}
