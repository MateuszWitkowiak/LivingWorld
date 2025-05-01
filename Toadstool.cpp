#include "Toadstool.h"

Toadstool::Toadstool(Position position) : Plant(0, position) {
    setInitiative(0);
    setLiveLength(12);
    setPowerToReproduce(4);
    setSpecies("Toadstool");
    setSign("T");
}

void Toadstool::consequences(Organism& organism, World& world) {
    if (this->getPosition() == organism.getPosition()) {
        world.removeOrganism(organism);
    }
}