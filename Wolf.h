#include "Animal.h"
#include "World.h"

class Wolf : public Animal {
    public:
        Wolf(Position position);
        void consequences(Organism& organism, World& world) override;
};