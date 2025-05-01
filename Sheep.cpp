#include "Sheep.h"

Sheep::Sheep(Position position) : Animal(3, position) {
    setPower(3);
    setInitiative(3);
    setLiveLength(3);
    setPowerToReproduce(6);
    setSign("S");
    setSpecies("Sheep");
}

void Sheep::consequences(Organism& attackingOrganism, World& world) {
    if (this->getPosition() == attackingOrganism.getPosition()){
        if (attackingOrganism.getSpecies() == "Grass") {
            world.removeOrganism(attackingOrganism);
        }
    }   
}