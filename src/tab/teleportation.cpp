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


#include "teleportation.h"
#include <iostream>

using namespace std;

teleportation::teleportation() {
    char message[LENGHT];
    strcpy(message, "Teletrasporto");
    setMessage(message);
};

void teleportation::effect(game* g){
    cout << "Sei sulla casella Teletrasporto, sarai teletrasportato da qualche parte nel tabellone" << endl;

    int nowPlaying = g->getNowPlaying();

    player* players = g->getPlayers();

    int numCas;
    numCas = rand() % (g->getNumBoxes() - 1) + 1;
    players[nowPlaying].setPos(numCas);
}