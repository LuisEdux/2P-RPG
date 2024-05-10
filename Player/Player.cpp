#include <iostream>
#include "Player.h"

using namespace std;

Player::Player(char* _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;

    health -= trueDamage;

    if (trueDamage > 0) {
        cout << name << " Recibio " << trueDamage << " de damage!" << endl;

        if (health <= 0) {
            cout << name << " Haz Sido Derrotado" << endl;
        }
    } else {
        gainExperience(10);
        cout << getName() << " Se Defendio Del Ataque" << endl;
    }
}

void Player::levelUp() {
    level++;
    health += 0;
    attack += 0;
    defense += 0;
    selectAttributeToUpgrade();
}

void Player::selectAttributeToUpgrade() {
    int choice;
    cout << "Selecciona el atributo para aumentar:" << endl;
    cout << "1. Salud" << endl;
    cout << "2. Ataque" << endl;
    cout << "3. Defensa" << endl;

    cin >> choice;
    switch (choice) {
        case 1:
            health += 10; 
            cout << "Salud aumentada a " << health << endl;
            break;
        case 2:
            attack += 10; 
            cout << "Ataque aumentado a " << attack << endl;
            break;
        case 3:
            defense += 10; 
            cout << "Defensa aumentada a " << defense << endl;
            break;
        default:
            cout << "Opción inválida. No se ha realizado ningún cambio en los atributos." << endl;
            break;
    }
    cout << "Nuevas estadisticas:" << endl;
    cout << "Salud: " << health << endl;
    cout << "Ataque: " << attack << endl;
    cout << "Defensa: " << defense << endl;
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = experience - 100;
    }
}

Character* Player::selectTarget(std::vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Selecciona A quien Atacar: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(std::vector<Enemy*> enemies) {
    int action = 0;
    cout << "Elige una Accion: " << endl
         << "1. Atacar" << endl
         << "2. Defenderte" << endl;

    //TODO: Validate input
    cin >> action;
    Action currentAction;
    Character* target = nullptr;

    unDefend();

    switch(action) {
        case 1:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target](){
                doAttack(target);
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            currentAction.action = [this](){
                defend();
            };

            currentAction.speed = 9999999;
            break;
        default:
            cout << "Invalid action" << endl;
            break;
    }

    return currentAction;
}
