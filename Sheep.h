#include "Animal.h"
#include "World.h"

class Sheep : public Animal 
{
    public:
        Sheep(Position position);
        
        void consequences(Organism& attackingOrganism, World& world) override;
    
};