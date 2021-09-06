//
// Copyright © 2018 Silvano Carradori
//
// This file is part of EvGOP.
//
// EvGOP is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// EvGOP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with EvGOP.  If not, see <http://www.gnu.org/licenses/>.
//


#include <iostream>
#include "../player/player.h"

using namespace std;

// Costruttore
player::player(char name[LENGHT]) {
    strcpy(this->name, name);
    this->energy = 0;
    this->pos = 0;
};

// Ritorna il nome del giocatore
char* player::getName(){
    return this->name;
}

// Ritorna l'energia del giocatore
int player::getEnergy() {
    return this->energy;
}

// Ritorna la posizione del giocatore
int player::getPos() {
    return this->pos;
}

// Imposta la posizione del giocatore
void player::setPos(int pos) {
    this->pos = pos;
}

// Incrementa la posizione e accumula energia dopo il lancio del dado
void player::incPos(int dice, box *tab[], int numBoxes) {
    // Se la posizione dopo il lancio del dado è prima dell'ultima casella allora si incrementa, altrimenti si va all'ultima casella
    if (this->pos + dice < numBoxes - 1){
        this->pos = this->pos + dice;
        this->energy = this->energy + tab[this->pos]->getEnergy();
    } else {
        this->pos = numBoxes - 1;
    }

}

// Decrementa la posizione dopo il lancio del dado
void player::decPos(int dice) {
    if (this->pos - dice < 0){
        this->pos = 0;
    } else {
        this->pos -= dice;
    }
}

// Setta l'energia
void player::setEnergy(int energy){
    this->energy = energy;
}
