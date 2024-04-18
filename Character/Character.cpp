//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
#include<iostream>

using namespace std;
Character::Character(string _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    name = _name;
    health = _health;
    maxHealth = _health;
    attack = _attack;
    defense = _defense;
    maxDefense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
}

string Character::getName() {
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

string Character::toString() {
    return "Name: " + name + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}

bool Character::getIsPlayer() {
    return isPlayer;
}

void Character::defend() {
    cout<<getName()<<" aumento su defensa."<<endl;

    defense += (maxDefense*.2);

    cout<<"Defense: "<<defense<<endl;
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

bool Character::flee(Character*target) {
    if(this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}