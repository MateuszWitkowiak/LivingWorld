#pragma once
#include <string>
#include <utility>
#include <vector>
#include "Position.h"
#include "World.h"
#include <fstream>
#include <iostream>

using namespace std;
class World;

class Organism {
private:
    int power;
    Position position;
    string species;
    string sign;
    bool alive = true;
    int turnOfBirth;
    int initiative;
    int liveLength;
    int PowerToReproduce;
    World* world;
    std::vector<std::pair<int, int>> ancestryHistory;

protected:
    vector<Organism*> children;

public:
    // Constructors & operators
    Organism(Position position, int turnOfBirth, vector<pair<int, int>> ancestryHistory, World* world);
    Organism(Position position, int turnOfBirth, World* world);
    Organism(Position position, World* world);
    Organism(World* world);
    Organism(const Organism& other);
    Organism(Organism&& other) noexcept;
    Organism() = delete;
    virtual ~Organism() = default;
    Organism& operator=(const Organism& other);
    Organism& operator=(Organism&& other) noexcept;

    // Basic getters and setters
    int getPower() const;
    void setPower(int power);
    Position getPosition() const;
    void setPosition(Position position);
    string getSpecies() const;
    void setSpecies(string spec);
    string getSign();
    void setSign(string sign);
    bool isAlive() const { return alive; }
    void setAlive(bool alive) { this->alive = alive; }
    int getTurnOfBirth() const { return turnOfBirth; }
    void setTurnOfBirth(int turnOfBirth) { this->turnOfBirth = turnOfBirth; }
    int getInitiative() const;
    void setInitiative(int initiative);
    int getLiveLength() const { return liveLength; }
    void setLiveLength(int liveLength);
    int getPowerToReproduce() const;
    void setPowerToReproduce(int powerToReproduce);
    World* getWorld() const { return world; }
    void setWorld(World* world) { this->world = world; }

    // Children management
    vector<Organism*> getChildren() const { return children; }
    void addChildren(Organism* child) { children.push_back(child); }

    // Ancestry management
    void addAncestor(int birth, int death);
    void addAncestorToChildren(int birthTurn, int deathTurn);
    void setAncestors(const vector<pair<int, int>>& ancestors) { this->ancestryHistory = ancestors; }

    // State and behavior
    bool canReproduce();
    void kill(int turn);
    string toString() const;

    // Serialization
    void serialize(fstream& file);
    vector<Organism*> deserialize(fstream& file);
    virtual void deserializeChildren(fstream& file, vector<Organism*>& allChildren) = 0;

    // Pure virtual methods
    virtual Organism* copy() const = 0;
    virtual void move() = 0;
    virtual Organism* action() = 0;
    virtual bool isPredator() const = 0;
    virtual void initParams() = 0;
    virtual vector<Position> getNeighboringPositionsToMove() const = 0;
    vector<Position> getBirthPositionsVector() const;
};
