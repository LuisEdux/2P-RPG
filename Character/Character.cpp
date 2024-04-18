//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
#include <iostream>
#include <cstring> 

using namespace std;

Character::Character(char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {

    strcpy(name, _name);
    health = _health;
    maxHealth = _health;
    attack = _attack;
    defense = _defense;
    maxDefense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
}

char* Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    return defense;
}

int Character::getSpeed() {
    return speed;
}

char* Character::toString() {
    
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Name: %s\nHealth: %d\nAttack: %d\nDefense: %d\nSpeed: %d", name, health, attack, defense, speed);
    
    return strdup(buffer);
}

bool Character::getIsPlayer() {
    return isPlayer;
}

void Character::defend() {
    cout << name << " aumento su defensa." << endl;
    defense += (maxDefense * 0.2);
    cout << "Defense: " << defense << endl;
}

void Character::unDefend() {
    defense = maxDefense;
}

int Character::getMaxDefense() {
    return maxDefense;
}

int Character::getMaxHealth() {
    return maxHealth;
}

bool Character::flee(Character* target) {
    if (this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}
