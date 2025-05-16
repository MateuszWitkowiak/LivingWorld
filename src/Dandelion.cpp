#include "Dandelion.h"

Dandelion::Dandelion(Position position) : Plant(0, position) {
    setInitiative(0);
    setLiveLength(6);
    setPowerToReproduce(2);
    setSign("D");
    setSpecies("Dandelion");
};