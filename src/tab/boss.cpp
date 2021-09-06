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


#include "boss.h"
#include <iostream>

using namespace std;

boss::boss() {
    char message[LENGHT];
    strcpy(message, "BOSS");
    setMessage(message);
};

void boss::effect(game* g) {
    cout << "Sei sull'ultima casella, per vincere il gicoo devi superare il BOSS " << endl;

    box* tab = g->getTab();

    int nowPlaying = g->getNowPlaying();

    player* players = g->getPlayers();

    cout << "Energia BOSS: " << tab[players[nowPlaying].getPos()].getEnergy() << endl;
    cout << "Tua energia: " << players[nowPlaying].getEnergy() << endl;

    // Se il giocatore ha energia maggiore del boss allora vince, altrimenti torna indietro di 6 caselle
    if (players[nowPlaying].getEnergy() > tab[players[nowPlaying].getPos()].getEnergy()){
        cout << "Hai sconfitto il BOSS! ";
        g->end();
    } else {
        cout << "Purtroppo non hai energia sufficiente per superare il BOSS, devi tornare indietro di 6 caselle" << endl;
        players[nowPlaying].decPos(6);
    }
}