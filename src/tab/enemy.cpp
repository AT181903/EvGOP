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


#include "enemy.h"
#include <iostream>

using namespace std;

enemy::enemy() {
    char message[LENGHT];
    strcpy(message, "Nemico");
    setMessage(message);
};

void enemy::effect(game *g){
    cout << "Sei sulla casella Nemico, per andare avanti devi sconfiggerlo" << endl;

    box* tab = g->getTab();

    int nowPlaying = g->getNowPlaying();

    player* players = g->getPlayers();

    int posAttuale = players[nowPlaying].getPos();

    cout << "Energia nemico: " << tab[posAttuale].getEnergy() << endl;
    cout << "Tua energia: " << players[nowPlaying].getEnergy() << endl;

    // Se il giocatore ha energia maggiore del nemico allora può andare avanti al prossimo giro, altrimenti torna indietro di 6 caselle
    if (players[nowPlaying].getEnergy() > tab[posAttuale].getEnergy()){
        cout << "Hai sconfitto il nemico, puoi andare avanti" << endl;
    } else {
        cout << "Purtroppo non hai energia sufficiente per sconfiggere il nemico, devi tornare indietro di 6 caselle" << endl;
        players[nowPlaying].decPos(6);
    }
}
