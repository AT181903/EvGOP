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


#ifndef EVGOP_PLAYER_H
#define EVGOP_PLAYER_H

#define LENGHT 100

#include "../tab/box.h"

class box;

class player {
private:
    char name[LENGHT];
    int energy;
    int pos;

public:

    player(char name[LENGHT]); // Costruttore

    char* getName(); // Ritorna il nome del giocatore

    int getEnergy(); // Ritorna l'energia del giocatore

    void incPos(int dice, box *tab[], int numBoxes); // Incrementa la posizione dopo il lancio del dado

    void decPos(int dice); // Decrementa la posizione dopo il lancio del dado

    int getPos(); // Ritorna la posizione del giocatore

    void setPos(int pos); // Imposta la posizione del giocatore

    void setEnergy(int energy); // Setta l'energia

};


#endif //EVGOP_PLAYER_H
