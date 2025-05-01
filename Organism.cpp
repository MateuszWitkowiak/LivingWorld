#include "Organism.h"
#include <iostream>
#include "World.h"

Organism::Organism(int power, Position position)
{
	setPower(power);
	setPosition(position);
	setSpecies("O");
}

Organism::Organism(const Organism& other):
	power(other.power),
	position(other.position),
	species(other.species),
	ancestryHistory(other.ancestryHistory)
{}

Organism::Organism(Organism&& other):
	power(std::move(other.power)),
	position(std::move(other.position)),
	species(std::move(other.species)),
	ancestryHistory(std::move(other.ancestryHistory))
{}

Organism::~Organism()
{
	std::cout << "Organism killed" << std::endl;
}

Organism& Organism::operator=(const Organism& other) {
	if (this != &other) {
		power = other.power;
		position = other.position;
		species = other.species;
		ancestryHistory = other.ancestryHistory;
	}
	return *this;
}

Organism& Organism::operator=(Organism&& other) noexcept {
	if (this != &other) {
		power = std::move(other.power);
		position = std::move(other.position);
		species = std::move(other.species);
		ancestryHistory = std::move(other.ancestryHistory);
	}
	return *this;
}

int Organism::getPower()
{
	return this->power;
}

void Organism::setPower(int power)
{
	this->power = power;
}

Position Organism::getPosition()
{
	return this->position;
}

void Organism::setPosition(Position position)
{
	this->position = position;
}

string Organism::toString()
{
	return "{ species: " + this->getSpecies() + 
		", power: " + to_string(getPower()) + 
		", position: " + getPosition().toString() + "}";
}

void Organism::move(int dx, int dy)
{
	position.move(dx, dy);
}

string Organism::getSpecies()
{
	return this->species;
}

void Organism::setSpecies(string spec)
{
	this->species = spec;
}

void Organism::addAncestor(int birth, int death)
{
	ancestryHistory.push_back({birth, death});
}

void Organism::consequences(Organism& attackingOrganism, World& world)
{
	if (this->getPosition() == attackingOrganism.getPosition()) {
		if (this->getPower() >= attackingOrganism.getPower()) {
			world.removeOrganism(attackingOrganism);
		} else {
			world.removeOrganism(*this);
		}
	}
}

int Organism::getInitiative()
{
	return this->initiative;
}

int Organism::getLiveLength()
{
	return this->liveLength;
}

int Organism::getpowerToReproduce()
{
	return this->powerToReproduce;
}

string Organism::getSign()
{
	return this->sign;
}

void Organism::setInitiative(int init)
{
	this->initiative = init;
}

void Organism::setLiveLength(int length)
{
	this->liveLength = length;
}

void Organism::setPowerToReproduce(int power)
{
	this->powerToReproduce = power;
}

void Organism::setSign(string sign)
{
	this->sign = sign;
}
