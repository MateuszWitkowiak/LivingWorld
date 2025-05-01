#include "Plant.h"
#include "World.h"

class Toadstool : public Plant {
    public:
        Toadstool(Position position);
        void consequences(Organism& organism, World& world);
};