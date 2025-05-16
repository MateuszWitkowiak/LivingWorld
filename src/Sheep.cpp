#include "Sheep.h"
#include <iostream>

Sheep::Sheep(Position position) : Animal(3, position) {
    setPower(3);
    setInitiative(3);
    setLiveLength(3);
    setPowerToReproduce(6);
    setSign("S");
    setSpecies("Sheep");
}

void Sheep::consequences(Organism& attackingOrganism, World& world) {
    std::cout << "Sheep at position: " << this->getPosition().toString() << std::endl;
    std::cout << "Attacking organism (Grass) at position: " << attackingOrganism.getPosition().toString() << std::endl;

    if (this->getPosition() == attackingOrganism.getPosition()) {
        std::cout << "Positions are the same!" << std::endl;
        if (attackingOrganism.getSpecies() == "Grass") {
            std::cout << "Sheep eats Grass!" << std::endl;
            world.removeOrganism(attackingOrganism);
        }
    }
}
