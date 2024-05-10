#include "Combat.h"
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for (auto participant : participants) {
        if (participant->getIsPlayer()) {
            partyMembers.push_back((Player *) participant);
        } else {
            enemies.push_back((Enemy *) participant);
        }
    }
}

Combat::Combat(vector<Player*> _partyMembers, vector<Enemy*> _enemies) {
    partyMembers = std::move(_partyMembers);
    enemies = std::move(_enemies);
    participants = vector<Character*>();
    participants.insert(participants.end(), partyMembers.begin(), partyMembers.end());
    participants.insert(participants.end(), enemies.begin(), enemies.end());
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if (participant->getIsPlayer()) {
        partyMembers.push_back((Player*) participant);
    } else {
        enemies.push_back((Enemy*) participant);
    }
}

void Combat::combatPrep() {
    // Ordena los participantes por velocidad
    sort(participants.begin(), participants.end(), compareSpeed);
}

char* Combat::toString() {
    string result = "";
    vector<Character*>::iterator it;
    for (it = participants.begin(); it != participants.end(); it++) {
        result += (*it)->toString();  "\n";
    }
    cout << "====================" << endl;
    return strdup(result.c_str());
}

Character* Combat::getTarget(Character* attacker) {
    vector<Character*>::iterator it;
    for (it = participants.begin(); it != participants.end(); it++) {
        if ((*it)->getIsPlayer() != attacker->getIsPlayer()) {
            return *it;
        }
    }
    //TODO: Handle this exception
    return nullptr;
}

void Combat::doCombat() {
    cout << "Inicio del combate" << endl;
    combatPrep();
    int round = 1;
    // Este while representa las rondas del combate
    while (enemies.size() > 0 && partyMembers.size() > 0) {
        cout << "Round " << round << endl;
        vector<Character*>::iterator it = participants.begin();
        registerActions(it);
        executeActions(it);

        round++;
    }

    if (enemies.empty()) {
        cout << "You win!" << endl;
    } else {
        cout << "You lose!" << endl;
    }
}

void Combat::executeActions(vector<Character*>::iterator participant) {
    while (!actionQueue.empty()) {
        Action currentAction = actionQueue.top();
        currentAction.action();
        actionQueue.pop();
        if (currentAction.target != nullptr) {
            checkParticipantStatus(*participant);
            checkParticipantStatus(currentAction.target);
            if (currentAction.target->getHealth() <= 0 && !currentAction.target->getIsPlayer()) {
                for (Player* player : partyMembers) {
                    player->levelUp();

                }
            }
        }
    }
}

void Combat::checkParticipantStatus(Character *participant) {
    if (participant->getHealth() <= 0) {
        if (participant->getIsPlayer()) {
            partyMembers.erase(remove(partyMembers.begin(), partyMembers.end(), participant), partyMembers.end());
        } else {
            enemies.erase(remove(enemies.begin(), enemies.end(), participant), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), participant), participants.end());
    }
}

void Combat::registerActions(vector<Character*>::iterator participantIterator) {
    // Este while representa el turno de cada participante
    // La elección que cada personaje elige en su turno
    while (participantIterator != participants.end()) {
        if ((*participantIterator)->getIsPlayer()) {
            Action playerAction = ((Player*) *participantIterator)->takeAction(enemies);
            actionQueue.push(playerAction);
        } else {
            Action enemyAction = ((Enemy*) *participantIterator)->takeAction(partyMembers);
            actionQueue.push(enemyAction);
        }

        participantIterator++;
    }
}
