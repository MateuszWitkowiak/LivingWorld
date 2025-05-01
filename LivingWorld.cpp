#include <iostream>
#include "World.h"
#include "Sheep.h"
#include "Wolf.h"
#include "Dandelion.h"
#include "Toadstool.h"
#include "Grass.h"

#include <memory>  // konieczne do make_unique

int main() {
    World world;

    world.addOrganism(std::make_unique<Sheep>(Position(2, 2)));
    world.addOrganism(std::make_unique<Wolf>(Position(3, 3)));
    world.addOrganism(std::make_unique<Dandelion>(Position(1, 1)));
    world.addOrganism(std::make_unique<Toadstool>(Position(4, 4)));
    world.addOrganism(std::make_unique<Grass>(Position(3, 3)));

    for (int turn = 0; turn < 5; ++turn) {
        std::cout << "=== Turn " << turn << " ===" << std::endl;
        world.makeTurn();
        std::cout << world.toString() << std::endl;
    }

    return 0;
}

