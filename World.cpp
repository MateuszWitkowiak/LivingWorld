#include "World.h"
#include <fstream>
#include <algorithm>

string World::getOrganismFromPosition(int x, int y)
{
    for (const auto& org : organisms)
        if (org->getPosition().getX() == x && org->getPosition().getY() == y)
            return org->getSpecies();
    return "";
}

bool World::isPositionOnWorld(int x, int y)
{
    return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position)
{
    return this->getOrganismFromPosition(position.getX(), position.getY()).empty();
}

vector<Position> World::getVectorOfFreePositionsAround(Position position)
{
    int pos_x = position.getX(), pos_y = position.getY();
    vector<Position> result;
    for (int x = -1; x < 2; ++x)
        for (int y = -1; y < 2; ++y)
            if ((x != 0 || y != 0) &&
                isPositionOnWorld(pos_x + x, pos_y + y)) {
                result.push_back(Position(pos_x + x, pos_y + y));
            }
    auto iter = remove_if(result.begin(), result.end(),
        [this](Position pos) { return !isPositionFree(pos); });
    result.erase(iter, result.end());

    return result;
}

World::World(int worldX, int worldY)
{
    setWorldX(worldX);
    setWorldY(worldY);
}

int World::getWorldX() { return this->worldX; }
void World::setWorldX(int worldX) { this->worldX = worldX; }

int World::getWorldY() { return this->worldY; }
void World::setWorldY(int worldY) { this->worldY = worldY; }

int World::getTurn() { return this->turn; }

void World::addOrganism(unique_ptr<Organism> organism)
{
    organisms.push_back(std::move(organism));
}

void World::makeTurn()
{
    vector<Position> newPositions;
    int numberOfNewPositions;
    int randomIndex;

    srand(time(0));
    for (auto& org : organisms) {
        newPositions = getVectorOfFreePositionsAround(org->getPosition());
        numberOfNewPositions = newPositions.size();
        if (numberOfNewPositions > 0) {
            randomIndex = rand() % numberOfNewPositions;
            org->setPosition(newPositions[randomIndex]);
        }
    }
    turn++;
}

void World::writeWorld(string fileName)
{
    fstream my_file;
    my_file.open(fileName, ios::out | ios::binary);
    if (my_file.is_open()) {
        my_file.write((char*)&this->worldX, sizeof(int));
        my_file.write((char*)&this->worldY, sizeof(int));
        my_file.write((char*)&this->turn, sizeof(int));
        int orgs_size = this->organisms.size();
        my_file.write((char*)&orgs_size, sizeof(int));
        for (int i = 0; i < orgs_size; i++) {
            int data;
            data = organisms[i]->getPower();
            my_file.write((char*)&data, sizeof(int));
            data = organisms[i]->getPosition().getX();
            my_file.write((char*)&data, sizeof(int));
            data = organisms[i]->getPosition().getY();
            my_file.write((char*)&data, sizeof(int));
            string s_data = organisms[i]->getSpecies();
            int s_size = s_data.size();
            my_file.write((char*)&s_size, sizeof(int));
            my_file.write(s_data.data(), s_data.size());
        }
        my_file.close();
    }
}

void World::readWorld(string fileName)
{
    fstream my_file;
    my_file.open(fileName, ios::in | ios::binary);
    if (my_file.is_open()) {
        int result;
        my_file.read((char*)&result, sizeof(int));
        this->worldX = result;
        my_file.read((char*)&result, sizeof(int));
        this->worldY = result;
        my_file.read((char*)&result, sizeof(int));
        this->turn = result;
        my_file.read((char*)&result, sizeof(int));
        int orgs_size = result;
        vector<unique_ptr<Organism>> new_organisms;
        for (int i = 0; i < orgs_size; i++) {
            int power;
            my_file.read((char*)&result, sizeof(int));
            power = result;

            int pos_x;
            my_file.read((char*)&result, sizeof(int));
            pos_x = result;
            int pos_y;
            my_file.read((char*)&result, sizeof(int));
            pos_y = result;
            Position pos{ pos_x, pos_y };

            int s_size;
            my_file.read((char*)&result, sizeof(int));
            s_size = result;

            string species;
            species.resize(s_size);
            my_file.read(&species[0], s_size);

            auto org = make_unique<Organism>(power, pos);
            org->setSpecies(species);
            new_organisms.push_back(std::move(org));
        }
        this->organisms = std::move(new_organisms);
        my_file.close();
    }
}

string World::toString()
{
    string result = "\nturn: " + to_string(getTurn()) + "\n";
    string spec;

    for (int wY = 0; wY < getWorldY(); ++wY) {
        for (int wX = 0; wX < getWorldX(); ++wX) {
            spec = getOrganismFromPosition(wX, wY);
            result += spec.empty() ? std::string(1, separator) : spec;
        }
        result += "\n";
    }
    return result;
}

void World::removeOrganism(Organism& organismToRemove)
{
	auto it = std::find(organisms.begin(), organisms.end(), organismToRemove);
	auto it = std::find_if(organisms.begin(), organisms.end(),
        [&organismToRemove](const std::unique_ptr<Organism>& org) {
            return org.get() == &organismToRemove;
        });
    if (it != organisms.end()) {
        organisms.erase(it);
    }
}