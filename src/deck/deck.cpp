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
#include "deck.h"
#include "cards/assorbimento.h"
#include "cards/card.h"
#include "cards/cataclisma.h"
#include "cards/controAssorbimento.h"
#include "cards/dimezzaEnergiaCasella.h"
#include "cards/lanciaDado.h"
#include "cards/tornaIndietro.h"
#include "cards/swiftGain.h"


deck::deck() = default;

// Ritorna casualmente una carta in base alle probabilità scelte
card* deck::pesca() {
    int probabilita = (rand() % 40 + 1);

    if (probabilita == 1 || probabilita == 2) {
            return new swiftGain();
        }else if (probabilita == 3 || probabilita == 4 || probabilita == 5) {
            return new cataclisma();
        }else if (probabilita > 5 && probabilita < 13){
            return new controAssorbimento();
        }else if (probabilita > 12 && probabilita < 20){
            return new dimezzaEnergiaCasella();
        }else if (probabilita > 19 && probabilita < 27) {
            return new lanciaDado();
        }else if (probabilita > 26 && probabilita < 34) {
            return new tornaIndietro();
        }else {
            return new assorbimento();
    }
}
