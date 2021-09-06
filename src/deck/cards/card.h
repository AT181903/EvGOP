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


#ifndef EVGOP_CARD_H
#define EVGOP_CARD_H

#include "../../game/game.h"

class game;

#define LENGHT 100

class card {
private:
    char name[LENGHT];

public:
    card(); // Costruttore

    void setName(char nome[]); // Imposta il nome della carta

    char* getName(); // Ritorna il nome della carta

    virtual void effect(game* g);
};

#endif //EVGOP_CARD_H
