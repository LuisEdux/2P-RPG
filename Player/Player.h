//
// Created by Victor Navarro on 15/02/24.
//
#pragma once
#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include <vector>

class Enemy;

class Player: public Character {
    //TODO: Implementar Clases (Mago, Guerrero, Pícaro, etc.)
    //TODO: Implementar Inventario
private:
    int level;
    int experience;

    void levelUp();
public:
    Player(char* _name, int _health, int _attack, int _defense, int _speed); // Cambio de string a char
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* selectTarget(vector<Enemy*> possibleTargets);
    Action takeAction(vector<Enemy*> enemies);

    void gainExperience(int exp);

    //TODO: Implementar uso de objeto
    void displayStats() const;
};


#endif //RPG_PLAYER_H
