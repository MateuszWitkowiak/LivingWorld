#include "Organism.h"
#include <iostream>
#include "World.h"

Organism::Organism(Position position, World* world) {
    setTurnOfBirth(0);
    setPosition(position);
    setWorld(world);
}

Organism::Organism(Position position, int turnOfBirth, World* world) {
    setPosition(position);
    setTurnOfBirth(turnOfBirth);
    setWorld(world);
}

Organism::Organism(World* world) {
    setPosition(Position(0, 0));
    setTurnOfBirth(0);
    setWorld(world);
}

Organism::Organism(const Organism& other) :
    power(other.power),
    position(other.position),
    species(other.species),
    ancestryHistory(other.ancestryHistory) {}

Organism::Organism(Organism&& other) noexcept :
    power(std::move(other.power)),
    position(std::move(other.position)),
    species(std::move(other.species)),
    ancestryHistory(std::move(other.ancestryHistory)) {}

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

int Organism::getPower() const { return this->power; }
void Organism::setPower(int power) { this->power = power; }

Position Organism::getPosition() const { return this->position; }
void Organism::setPosition(Position position) { this->position = position; }

string Organism::getSpecies() const { return this->species; }
void Organism::setSpecies(string spec) { this->species = spec; }

string Organism::getSign() { return this->sign; }
void Organism::setSign(string sign) { this->sign = sign; }

int Organism::getInitiative() const { return this->initiative; }
void Organism::setInitiative(int initiative) { this->initiative = initiative; }

int Organism::getLiveLength() const { return this->liveLength; }
void Organism::setLiveLength(int liveLength) { this->liveLength = liveLength; }

int Organism::getPowerToReproduce() const { return this->PowerToReproduce; }
void Organism::setPowerToReproduce(int powerToReproduce) { this->PowerToReproduce = powerToReproduce; }


vector<Organism*> Organism::getChildren() const { return children; }
void Organism::addChildren(Organism* child) { children.push_back(child); }


void Organism::addAncestor(int birth, int death) {
    ancestryHistory.push_back({birth, death});
}

void Organism::addAncestorToChildren(int birthTurn, int deathTurn) {
    for (auto child : getChildren()) {
        child->addAncestor(birthTurn, deathTurn);
    }
}

void Organism::addAncestor(int birthTurn, int deathTurn) {
    ancestryHistory.push_back(make_pair(birthTurn, deathTurn));
    addAncestorToChildren(birthTurn, deathTurn);
}


bool Organism::canReproduce() {
    return getPower() >= getPowerToReproduce();
}

void Organism::kill(int turn) {
    setAlive(false);
    auto children = getChildren();

    for (auto it = children.begin(); it != children.end();) {
        Organism* child = *it;

        if (child->isAlive()) {
            child->addAncestor(getTurnOfBirth(), turn);
            ++it;
        } else {
            child->addAncestor(getTurnOfBirth(), turn);
            delete child;
            it = children.erase(it);
        }
    }
}

string Organism::toString() const {
    return getSpecies() + ", " + to_string(getPower()) + ", " + getPosition().toString() + ", " + to_string(getTurnOfBirth()) + ", " + to_string(getLiveLength()) + ", " + to_string(getPowerToReproduce()) + ", " + to_string(getInitiative());
}

// Serializacja
void Organism::serialize(fstream& file) {

    int speciesSize = species.size();
    file.write((char*)&speciesSize, sizeof(int));
    file.write(species.data(), speciesSize);
    int x = position.getX();
    int y = position.getY();
    file.write((char*)&x, sizeof(int));
    file.write((char*)&y, sizeof(int));
    file.write((char*)&power, sizeof(int));
    file.write((char*)&alive, sizeof(bool));
    file.write((char*)&PowerToReproduce, sizeof(int));
    file.write((char*)&turnOfBirth, sizeof(int));
    file.write((char*)&liveLength, sizeof(int));
    file.write((char*)&initiative, sizeof(int));

    int childrenSize = children.size();
    file.write((char*)&childrenSize, sizeof(int));
    for (Organism* org : children) {
        org->serialize(file);
    }

    int ancestorsSize = ancestryHistory.size();
    file.write((char*)&ancestorsSize, sizeof(int));
    for (const auto& ancestor : ancestryHistory) {
        file.write((char*)&ancestor.first, sizeof(int));
        file.write((char*)&ancestor.second, sizeof(int));
    }
}

vector<Organism*> Organism::deserialize(fstream& file) {
    int resultInt, x, y;
    bool alive;
    vector<pair<int, int>> ancestors;
    vector<Organism*> allChildren;

    file.read((char*)&x, sizeof(int));
    file.read((char*)&y, sizeof(int));
    Position position(x, y);
    setPosition(position);
    file.read((char*)&resultInt, sizeof(int));
    setPower(resultInt);
    file.read((char*)&alive, sizeof(bool));
    setAlive(alive);
    file.read((char*)&resultInt, sizeof(int));
    setPowerToReproduce(resultInt);
    file.read((char*)&resultInt, sizeof(int));
    setTurnOfBirth(resultInt);
    file.read((char*)&resultInt, sizeof(int));
    setLiveLength(resultInt);
    file.read((char*)&resultInt, sizeof(int));
    setInitiative(resultInt);


    deserializeChildren(file, allChildren);

    file.read((char*)&resultInt, sizeof(int));
    int birthTurn, deathTurn;
    for (int i = 0; i < resultInt; i++) {
        file.read((char*)&birthTurn, sizeof(int));
        file.read((char*)&deathTurn, sizeof(int));
        ancestors.push_back(make_pair(birthTurn, deathTurn));
    }

    return allChildren;
}

vector<Position> Organism::getBirthPositionsVector() const {
    return getWorld()->getVectorOfFreePositionsAround(getPosition());
}