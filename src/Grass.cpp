#include "Grass.h"
#include <iostream>

Grass::Grass(Position position) : Plant(0, position) {
    setInitiative(0);
    setLiveLength(6);
    setPowerToReproduce(3);
    setSpecies("Grass");
    setSign("G");
    std::cout << "Tworzę grass" << position.toString() << std::endl;
} 