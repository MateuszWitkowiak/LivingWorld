#pragma once
#include "Organism.h"

using namespace std;

class Animal : public Organism
{
	public:
		Animal(int power, Position position);
		Animal();
		virtual ~Animal() {};
		virtual void consequences(Organism& attackingOrganism, World& world);

	private:
		Position lastPosition;
		void move(int posX, int posY);
};