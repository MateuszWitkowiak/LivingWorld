#include "Animal.h"
#include "Position.h"

Animal::Animal(int power, Position position) : Organism(power, position)
{
}

Animal::Animal() : Organism()
{
}

void Animal::move(int posX, int posY) {
	lastPosition = getPosition();
	setPosition(Position(posX, posY));
}

void Animal::consequences(Organism& attackingOrganism, World& world) {
	if (this->getPosition() == attackingOrganism.getPosition()) {
		if (this->getPower() >= attackingOrganism.getPower()) {
			world.removeOrganism(attackingOrganism);
		}
	}   
}
