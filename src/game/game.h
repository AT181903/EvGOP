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


#ifndef EVGOP_GAME_H
#define EVGOP_GAME_H

#include "../player/player.h"
#include "../deck/deck.h"

#define LENGHT 100

class player;
class box;
class deck;

class game {
private:
    player *players[LENGHT];
    deck *mazzo;
    box *tab[LENGHT];
    bool isGameFinished;
    int nowPlaying;
    int numPlayers;
    int numBoxes;

public:

    game(); // Costruttore

    void playGame(); // Gioco

    void titleAndRules(); // Titolo e regole

    void initializationPlayers(); // Inizializzazione giocatori

    void initializationBoxes(); // Inizializzazione tabellone

    void play(); // Lancio del dado, muove il giocatore, esegue l'effetto della casella e mostra la nuova posizione e la nuova energia

    void nextPlayer(); // Cambia giocatore

    void endMessage(); // Output fine gioco

    void end(); // Fine gioco

    void printTab(); // Stampa il tabellone

    int getNumBoxes(); // Ritorna il numero delle caselle

    player* getPlayers(); // Ritorna un puntatore al primo giocatore

    int getNowPlaying(); // Ritorna l'attuale giocatore

    int getNumPlayers(); // Ritorna il numero di giocatori

    box* getTab(); // Ritorna un puntatore alla prima casella

    void runBoxEffect(); // Esegue l'effetto della casella

    void runCardEffect(); // Esegue l'effetto della carta

    void lanciaDado(); // Lancia il dado e sposta il giocatore

    void assorbimento(); // Effetto carta assorbimento

    void cataclisma(); // Effetto carta cataclisma

    void controAssorbimento(); // Effetto carta Contro Assorbimento

    void dimezzaEnergiaCasella(); // Effetto carta Dimezza Energia Casella

    void swiftGain(); // Effetto carta swift Gain

    void tornaIndietro(); // Effetto carta torna indietro

    void cleanTerminal(); // Cancella tutto quello che c'è a video sul terminale

    void clearCin(); // Ignora qualunque cosa non sia il tasto INVIO

    void pressButton(); // Finchè non si preme il tasto INVIO non va avanti
};

#endif //EVGOP_GAME_H
