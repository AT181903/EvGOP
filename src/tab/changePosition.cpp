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


#include "changePosition.h"
#include <iostream>

using namespace std;

changePosition::changePosition(){
    char message[LENGHT];
    strcpy(message, "Cambio posizione");
    setMessage(message);
};

void changePosition::effect(game* g) {
    int nowPlaying = g->getNowPlaying();

    player* players = g->getPlayers();

    int numPlayers = g->getNumPlayers();

    int numCas = rand() % (numPlayers - 1) + 0;

    cout << "La tua posizione sarà scambiata con quella di " << players[numCas].getName() << endl;

    // Salva in un intero la posizione dell'altro giocatore
    int posAltroGiocatore = players[nowPlaying].getPos();

    players[nowPlaying].setPos(players[numCas].getPos());

    players[numCas].setPos(posAltroGiocatore);
}