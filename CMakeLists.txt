cmake_minimum_required(VERSION 3.10)
project(EvGOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(EvGOP main.cpp src/deck/cards/assorbimento.cpp src/deck/cards/assorbimento.h src/deck/cards/card.cpp src/deck/cards/card.h src/deck/cards/cataclisma.cpp src/deck/cards/cataclisma.h src/deck/cards/controAssorbimento.cpp src/deck/cards/controAssorbimento.h src/deck/cards/dimezzaEnergiaCasella.cpp src/deck/cards/dimezzaEnergiaCasella.h src/deck/cards/lanciaDado.cpp src/deck/cards/lanciaDado.h src/deck/cards/tornaIndietro.cpp src/deck/cards/tornaIndietro.h src/deck/cards/swiftGain.cpp src/deck/cards/swiftGain.h src/deck/deck.cpp src/deck/deck.h src/game/game.cpp src/game/game.h src/tab/box.cpp src/tab/box.h src/player/player.cpp src/player/player.h src/tab/start.cpp src/tab/start.h src/tab/boss.cpp src/tab/boss.h src/tab/teleportation.cpp src/tab/teleportation.h src/tab/enemy.cpp src/tab/enemy.h src/tab/vuota.cpp src/tab/vuota.h main.cpp src/tab/changePosition.cpp src/tab/changePosition.h)