#pragma once
#include "Organism.h"

class Plant : public Organism
{
	public:
		Plant(int power, Position position);
		Plant();
		virtual ~Plant() {};
		void move(int dx, int dy);
};