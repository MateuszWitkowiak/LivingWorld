#include "Wolf.h"

Wolf::Wolf(Position position) : Animal(8, position) {
    setInitiative(5);
    setLiveLength(20);
    setPowerToReproduce(16);
    setSign("W");
}