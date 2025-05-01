#pragma once
#include "Organism.h"

using namespace std;

class Animal : public Organism
{
	public:
		Animal(int power, Position position);
		Animal();

	private:
		Position lastPosition;
		void move(int posX, int posY);
};