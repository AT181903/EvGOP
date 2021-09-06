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
#include <iomanip>
#include "game.h"
#include "../tab/start.h"
#include "../tab/boss.h"
#include "../tab/vuota.h"
#include "../tab/changePosition.h"
#include "../tab/enemy.h"
#include "../tab/teleportation.h"

using namespace std;

// Costruttore
game::game() {

    this->isGameFinished = false;
    this->nowPlaying = 0;
    this->numPlayers = 0;
    this->numBoxes = 0;

    srand((unsigned int)time(0)); // Funzione per non far uscire sempre gli stessi numeri casuali

    titleAndRules(); // Titolo e regole

    pressButton(); // Premere invio per iniziare il gioco

    initializationPlayers(); // Inizializzazione giocatori

    initializationBoxes(); // Inizializzazione tabellone

    mazzo = new deck(); // Inizializzazione deck

    // "Svolgimento" del gioco
    while (!isGameFinished) {
        playGame();
    }

    endMessage(); // Messaggio finale
};

// Titolo e regole
void game::titleAndRules() {
    cout << "EVGOP (Evolutional Gioco dell'Oca Pazza)" << endl;
    cout << endl;
    cout << "Come giocare: " << endl;
    cout << "* Premi INVIO per eseguire le azioni richieste";
    cout << "\n";
}

//Inizializzazione giocatori
void game::initializationPlayers() {
    char name[LENGHT];


    cout << "Quanti giocatori ci sono? (2-3) ";
    while (numPlayers < 2 || numPlayers > 3) {
        cout << endl;
        cin >> numPlayers;
        if (cin.fail()) {
            cout << "Inserire il numero di giocatori! ";
            clearCin();
        } else if (numPlayers < 2){
            cout << "Inserire almeno 2 giocatori! " << endl;
            clearCin();
        } else if (numPlayers > 3){
            cout << "Inserire massimo 3 giocatori! " << endl;
            clearCin();
        }
    }

    int i = 0;
    while (i < numPlayers){
        cout << "Nome " << i+1 << " giocatore: ";
        cin >> name;
        players[i] = new player(name);
        i++;
    }

    cout << endl;
}

// Inizializzazione tabellone
void game::initializationBoxes() {

    this->numBoxes = rand() % 60 + 40; //Numero caselle casuale da 40 a 99

    tab[0] = new start(); // Prima casella
    tab[0]->setEnergy(0);

    tab[numBoxes - 1] = new boss(); // Ultima casella
    tab[numBoxes - 1]->setEnergy(numBoxes * 4);

    int numCas = 0;

    // Cicla dalla seconda alla penultima casella
    for (int i = 1; i < numBoxes - 1; ++i) {
        numCas = rand() % 99 + 1;

        if (numCas <= 70){
            tab[i] = new vuota();
            tab[i]->setEnergy(i * 4);
            } else if (numCas > 70 && numCas <= 80) {
            tab[i] = new teleportation();
            tab[i]->setEnergy(i * 4);
        } else if (numCas > 80 && numCas <= 90) {
            tab[i] = new enemy();
            tab[i]->setEnergy(i * 4);
        } else {
            tab[i] = new changePosition();
            tab[i]->setEnergy(i * 4);
        }
    }
}

// Gioco
void game::playGame() {

    // Pulizia terminale
    cleanTerminal();

    // Stampa tabellone
    printTab();

    cout << endl;

    //Il giocatore gioca
    play();

    // Cambio turno
    cout << "Premi INVIO per passare al giocatore successivo";
    pressButton();
    nextPlayer();
}

// Lancio del dado, gioca la carta pescata, muove il giocatore, esegue l'effetto della casella e mostra la nuova posizione e la nuova energia
void game::play() {

    // Stampa statistiche giocatore
    cout << "Giocatore: " << this->players[nowPlaying]->getName() << endl;
    cout << "Posizione: " << this->players[nowPlaying]->getPos() << endl;
    cout << "Energia: " << this->players[nowPlaying]->getEnergy() << endl;

    // Se il giocatore è dopo la prima casella
    if (this->players[nowPlaying]->getPos() > 0) {
        runCardEffect(); // Pesca una carta ed esegue l'effetto
    }

    lanciaDado(); // Lancia il dado e sposta il giocatore

    runBoxEffect(); // Esegui l'effetto della casella

    cout << "Nuova posizione: " << players[nowPlaying]->getPos() << endl;
    cout << "Nuova energia: " << players[nowPlaying]->getEnergy() << endl;
}



// Fine gioco
void game::end() {
    isGameFinished = true;
}

// Output fine gioco
void game::endMessage() {
    cleanTerminal();

    printTab();

    cout << endl;

    cout << "Il vincitore è " << this->players[nowPlaying]->getName() << endl;
}

// Stampa il tabellone
void game::printTab() {
    int numColonne = 3;

    int c = 0;
    // Cicla finchè non finiscono le colonne da stampare
    while (c < numBoxes / numColonne) {
        int j = 0;

        int lenght = 0;
        for (int p = 0; p < numPlayers; p++) {
                lenght = lenght + strlen(players[p]->getName());
        }

        lenght = lenght + (numPlayers*2) + 3;

        // Cicla finchè non stampa le 3 colonne
        while (j < numColonne) {
            //Stampa prima colonna
            if (j == 0) {
                cout << "";
                cout << right << setfill(' ') << setw(3) << c << ") ";
                cout << left << setfill(' ') << setw(16) << tab[c]->getMessage();
                cout << left << setfill(' ') << setw(11) << " (Energia: ";
                cout << right << setfill(' ') << setw(5) << tab[c]->getEnergy() << ") ";

                // Controlla quante persone ci sono per ogni casella e stampa il nome dei giocatori
                int howMany = 0;
                char s = '4';
                for (int p = 0; p < numPlayers; p++){
                    if (players[p]->getPos() == c){
                        cout << "(" << players[p]->getName() << ")";
                        howMany = howMany + 1;
                        if (p==0){
                            s = 'p';
                        } else if (p==1){
                            s = 's';
                        } else if (p==2){
                            s = 't';
                        }
                    }
                }

                // Decide quanto spazio dare nel tabellone a ciascuna persona
                if (howMany == 3){
                    cout << right << setfill (' ') << setw(3);
                } else if (howMany == 2) {
                    if (numPlayers == 2){
                        cout << right << setfill (' ') << setw(3);
                    } else {
                        cout << right << setfill (' ') << setw(10);
                    }
                } else if (howMany == 1) {
                    if (s == 'p'){
                        cout << right << setfill (' ') << setw(7 + strlen(players[1]->getName()) + strlen(players[2]->getName()));
                    } else if (s == 's'){
                        cout << right << setfill (' ') << setw(7 + strlen(players[0]->getName()) + strlen(players[2]->getName()));
                    } else {
                        cout << right << setfill (' ') << setw(7 + strlen(players[0]->getName()) + strlen(players[1]->getName()));
                    }
                } else {
                    cout << right << setfill (' ') << setw(lenght);
                }

             // Stampa seconda colonna
            } else if (j == 1) {
                cout << "| ";
                cout << right << setfill(' ') << setw(3) << (numBoxes / 3) + c << ") ";
                cout << left << setfill(' ') << setw(16) << tab[numBoxes / 3 + c]->getMessage();
                cout << left << setfill(' ') << setw(11) << " (Energia: ";
                cout << right << setfill(' ') << setw(5) << tab[numBoxes / 3 + c]->getEnergy() << ") ";

                // Controlla quante persone ci sono per ogni casella e stampa il nome dei giocatori
                int howMany = 0;
                char s = '4';
                for (int p = 0; p < numPlayers; p++){
                    if (players[p]->getPos() == (numBoxes / 3 + c)){
                        cout << "(" << players[p]->getName() << ")";
                        howMany = howMany + 1;
                        if (p==0){
                            s = 'p';
                        } else if (p==1){
                            s = 's';
                        }
                    }
                }

                // Decide quanto spazio dare nel tabellone a ciascuna persona
                if (howMany == 3){
                    cout << right << setfill (' ') << setw(3);
                } else if (howMany == 2) {
                    if (numPlayers == 2){
                        cout << right << setfill (' ') << setw(3);
                    } else {
                        if (s == 'p'){
                            cout << right << setfill (' ') << setw(7 + strlen(players[1]->getName()));
                        } else {
                            cout << right << setfill (' ') << setw(7 + strlen(players[0]->getName()));
                        }
                    }
                } else if (howMany == 1) {
                    if (s == 'p'){
                        cout << right << setfill (' ') << setw(7 + strlen(players[1]->getName()) + strlen(players[2]->getName()));
                    } else if (s == 's'){
                        cout << right << setfill (' ') << setw(7 + strlen(players[0]->getName()) + strlen(players[2]->getName()));
                    } else {
                        cout << right << setfill (' ') << setw(7 + strlen(players[0]->getName()) + strlen(players[1]->getName()));
                    }
                } else {
                    cout << right << setfill (' ') << setw(lenght);
                }

             // Stampa terza colonna
            } else {
                cout << "| ";
                cout << right << setfill(' ') << setw(3) << (numBoxes / 3) * 2 + c << ") ";
                cout << left << setfill(' ') << setw(16) << tab[(numBoxes / 3) * 2 + c]->getMessage();
                cout << left << setfill(' ') << setw(11) << " (Energia: ";
                cout << right << setfill(' ') << setw(5) << tab[(numBoxes / 3) * 2 + c]->getEnergy() << ") ";

                // Stampa il nome dei giocatori
                for (int p = 0; p < numPlayers; p++){
                    if (players[p]->getPos() == (numBoxes / 3)*2 + c){
                        cout << "(" << players[p]->getName() << ")";
                    }
                }

                // Se il numero di caselle non è divisibile per 3 e con resto 1 allora stampa l'ultima casella mancante
                if (c + 1 == numBoxes / numColonne && numBoxes%numColonne == 1){
                    cout << endl;

                    cout << right << setfill(' ') << setw(78 + 2*lenght);
                    cout << "| ";
                    cout << right << setfill(' ') << setw(3) << (numBoxes / 3) * 2 + c + 1 << ") ";
                    cout << left << setfill(' ') << setw(16) << tab[(numBoxes / 3) * 2 + c + 1]->getMessage();
                    cout << left << setfill(' ') << setw(11) << " (Energia: ";
                    cout << right << setfill(' ') << setw(5) << tab[(numBoxes / 3) * 2 + c + 1]->getEnergy() << ") ";

                    // Stampa il nome dei giocatori
                    for (int p = 0; p < numPlayers; p++) {
                        if (players[p]->getPos() == (numBoxes / 3) * 2 + c + 1) {
                            cout << " (" << players[p]->getName() << ") ";
                        } else {

                        }
                    }

                    // Se il numero di caselle non è divisibile per 3 e con resto 2 allora stampa le ultime 2 caselle mancanti
                } else if (c + 1 == numBoxes / numColonne && numBoxes%numColonne == 2){
                    cout << endl;

                    // Stampa la penultima casella
                    cout << right << setfill(' ') << setw(78 + 2*lenght);
                    cout << "| ";
                    cout << right << setfill(' ') << setw(3) << (numBoxes / 3) * 2 + c + 1 << ") ";
                    cout << left << setfill(' ') << setw(16) << tab[(numBoxes / 3) * 2 + c + 1]->getMessage();
                    cout << left << setfill(' ') << setw(11) << " (Energia: ";
                    cout << right << setfill(' ') << setw(5) << tab[(numBoxes / 3) * 2 + c + 1]->getEnergy() << ") ";

                    // Stampa il nome dei giocatori nella penultima casella
                    for (int p = 0; p < numPlayers; p++) {
                        if (players[p]->getPos() == (numBoxes / 3) * 2 + c + 1) {
                            cout << " (" << players[p]->getName() << ") ";
                        } else {

                        }
                    }

                    // Stampa l'ultima casella
                    cout << endl;
                    cout << right << setfill(' ') << setw(78 + 2*lenght);
                    cout << "| ";
                    cout << right << setfill(' ') << setw(3) << (numBoxes / 3) * 2 + c + 2<< ") ";
                    cout << left << setfill(' ') << setw(16) << tab[(numBoxes / 3) * 2 + c + 2]->getMessage();
                    cout << left << setfill(' ') << setw(11) << " (Energia: ";
                    cout << right << setfill(' ') << setw(5) << tab[(numBoxes / 3) * 2 + c + 2]->getEnergy() << ") ";

                    // Stampa il nome dei giocatori nell'ultima casella
                    for (int p = 0; p < numPlayers; p++) {
                        if (players[p]->getPos() == (numBoxes / 3) * 2 + c + 1) {
                            cout << " (" << players[p]->getName() << ") ";
                        } else {

                        }
                    }

                }
            }

            j++;
        }

        c++;
        cout << endl;
    }
}

// Ritorna il numero delle caselle
int game::getNumBoxes() {
    return this->numBoxes;
}

// Ritorna un puntatore al primo giocatore
player* game::getPlayers(){
    return this->players[0];
}

// Ritorna l'attuale giocatore
int game::getNowPlaying(){
    return this->nowPlaying;
}

// Ritorna un puntatore alla prima casella
box* game::getTab(){
    return this->tab[0];
}

// Esegue l'effetto della casella
void game::runBoxEffect(){
    // Se la posizione è maggiore di 0 (Cioè se è dopo lo start)
    if (players[nowPlaying]->getPos() > 0) {
        // Se la casella è vuota non fa niente, altrimenti esegue l'effetto
        if (strcmp(tab[players[nowPlaying]->getPos()]->getMessage(), "Casella vuota") == 0) {

        } else {
            tab[players[nowPlaying]->getPos()]->effect(this);
        }
    }
}

// Esegue l'effetto della carta
void game::runCardEffect(){
    // Il giocatore pesca una carta
    cout << "Premi INVIO per pescare una carta" << endl;
    pressButton();
    card *cartaAttuale;
    cartaAttuale = mazzo->pesca();

    // Output carta
    cout << "Hai pescato la carta \"" << cartaAttuale->getName() << "\""<< endl;
    cout << "Premi INVIO per giocarla" << endl;
    pressButton();

    // Esegue l'effetto della carta
    cartaAttuale->effect(this);
}

// Ritorna il giocatore successivo
void game::nextPlayer() {
    if (nowPlaying + 1 >= numPlayers) {
        nowPlaying = 0;
    }else{
        nowPlaying = nowPlaying + 1;
    }
}

// Lancia il dado e sposta il giocatore
void game::lanciaDado(){
    cout << endl << "Premi INVIO per tirare il dado" << endl;

    pressButton();

    int dice = (rand() % 6) + 1;

    cout << "Hai fatto: " << dice << endl;

    players[nowPlaying]->incPos(dice, tab, numBoxes); // Esegue il metodo incPos della classe player
}

// Ritorna il numero dei giocatori
int game::getNumPlayers() {
    return this->numPlayers;
}

// Effetto carta assorbimento
void game::assorbimento(){
    cout << "Hai assorbito il doppio  dell'energia della casella attuale" << endl;

    int energy = players[nowPlaying]->getEnergy() + ((tab[players[nowPlaying]->getPos()]->getEnergy()) * 2);

    players[nowPlaying]->setEnergy(energy);

    cout << "Nuova energia: " <<  players[nowPlaying]->getEnergy();
}

// Effetto carta cataclisma
void game::cataclisma(){
    cout << endl << "Premi INVIO per tirare il dado" << endl;

    pressButton();

    int dice = (rand() % 6) + 1;

    cout << "Hai fatto: " << dice << endl;

    cout << "Tutte le caselle perdono " << dice << " punti energia" << endl;

    // Ciclo dalla seconda casella alla penultima
    for (int i = 1; i < numBoxes - 2 ; ++i) {
        int energy = tab[players[nowPlaying]->getPos()]->getEnergy() - dice;

        if (energy < 0){
            tab[players[nowPlaying]->getPos()]->setEnergy(0);
        } else {
            tab[players[nowPlaying]->getPos()]->setEnergy(energy);
        }
    }
}

// Effetto carta Contro Assorbimento
void game::controAssorbimento(){
    cout << "La casella ha raddoppiato la sua energia (togliendola a te)" << endl;

    int energy = players[nowPlaying]->getEnergy() - tab[players[nowPlaying]->getPos()]->getEnergy();

    // Se la differnza fra la tua energia e quella della casella è minore di 0 allora l'energia del giocatore va a 0
    if (energy < 0){
        players[nowPlaying]->setEnergy(0);
    } else {
        players[nowPlaying]->setEnergy(energy);
    }

    // Raddoppio energia casella
    tab[players[nowPlaying]->getPos()]->setEnergy((tab[players[nowPlaying]->getPos()]->getEnergy())*2);

    cout << "Nuova energia: " << players[nowPlaying]->getEnergy();
}

// Effetto carta Dimezza Energia Casella
void game::dimezzaEnergiaCasella(){
    cout << "La casella attuale perde la metà della sua energia";

    int energy = tab[players[nowPlaying]->getPos()]->getEnergy() / 2;

    tab[players[nowPlaying]->getPos()]->setEnergy(energy);
}

// Effetto carta swift Gain
void game::swiftGain(){
    int dice = rand() % 6 + 1;

    pressButton();

    cout << "Numero uscito dal dado: " << dice << endl;

    cout << "Tutte le caselle guadagnano " << dice << " punti energia" << endl;

    int energyTmp = 0;
    int posTmp = 0;

    // Ciclo dalla seconda casella alla penultima
    for (int i = 1; i < numBoxes - 1 ; i++) {
        energyTmp = tab[i]->getEnergy() + dice;
        posTmp = players[nowPlaying]->getPos();
        tab[posTmp]->setEnergy(energyTmp);
    }
}

// Effetto carta torna indietro
void game::tornaIndietro(){
    int dice = rand() % 6 + 1;

    pressButton();

    cout << "Numero uscito dal dado: " << dice << endl;
    players[nowPlaying]->decPos(dice);

    if (players[nowPlaying]->getPos()-dice > 0){
        cout << endl << "Sei tornato indietro di " << dice << " caselle";
    } else {
        cout << endl << "Sei tornato alla casella di partenza";
    }

}

// Cancella tutto quello che c'è a video sul terminale
void game::cleanTerminal() {
    cout << "\x1B[2J\x1B[H";
}

// Finchè non si preme il tasto INVIO non va avanti
void game::pressButton(){
    clearCin();
    cin.putback('\n');
    cin.get();
}

// Ignora qualunque cosa non sia il tasto INVIO
void game::clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

