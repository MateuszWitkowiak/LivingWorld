#pragma once
#include <string>
#include <utility>
#include <vector>
#include "Position.h"

using namespace std;

class Organism
{
private:
	int power;
	Position position;
	string species;
	std::vector<std::pair<int, int>> ancestryHistory;
	
public:
	Organism(int power, Position position);
	Organism() : power(0), position(0, 0), species("O") {};
	Organism(const Organism& other);
	Organism(Organism&& other) noexcept;
	~Organism();
	Organism& operator=(const Organism& other);
	Organism& operator=(Organism&& other) noexcept;
	int getPower();
	void setPower(int power);
	Position getPosition();
	void setPosition(Position position);
	string getSpecies();
	void setSpecies(string spec);
	void addAncestor(int birth, int death);
	string toString();

	virtual void move(int dx, int dy);
	virtual void ancestralHistory();
};