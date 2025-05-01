#include "Animal.h"
#include "Position.cpp"

Animal::Animal(int power, Position position) : Organism(power, position)
{
	setSpecies("A");
}

Animal::Animal() : Organism()
{
	setSpecies("A");
}

void Animal::move(int posX, int posY) {
	lastPosition = getPosition();
	Position p = getPosition();
	p.setX(posX);
	p.setY(posY);
}