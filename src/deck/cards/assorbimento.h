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


#ifndef EVGOP_ASSORBIMENTO_H
#define EVGOP_ASSORBIMENTO_H

#include "card.h"

class assorbimento : public card {
public:
    assorbimento();
    void effect(game* g) override; //Assorbe il doppio dell'energia della casella attuale
};


#endif //EVGOP_ASSORBIMENTO_H
