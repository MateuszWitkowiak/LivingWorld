#include "World.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <Grass.h>
#include <Wolf.h>
#include <Toadstool.h>
#include <Dandelion.h>
#include <Sheep.h>

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
    std::cout << "Adding organism: " << organism->getSpecies() 
              << " at position: " << organism->getPosition().toString() << std::endl;
    organisms.push_back(std::move(organism));
}


void World::makeTurn() {
    vector<Position> newPositions;
    int numberOfNewPositions;
    int randomIndex;

    srand(time(0));
    for (auto& org : organisms) {
        newPositions = getVectorOfFreePositionsAround(org->getPosition());
        numberOfNewPositions = newPositions.size();
        if (numberOfNewPositions > 0) {
            randomIndex = rand() % numberOfNewPositions;
            std::cout << "Organism " << org->getSpecies() << " moves from " 
                      << org->getPosition().toString() << " to " 
                      << newPositions[randomIndex].toString() << std::endl;
            org->setPosition(newPositions[randomIndex]);
        }
    }

    // Sprawdzanie konsekwencji
    for (size_t i = 0; i < organisms.size(); ++i) {
        for (size_t j = i + 1; j < organisms.size(); ++j) {
            std::cout << "Checking consequences between " 
                      << organisms[i]->getSpecies() << " and " 
                      << organisms[j]->getSpecies() << std::endl;
            organisms[i]->consequences(*organisms[j], *this);
            organisms[j]->consequences(*organisms[i], *this);
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

#include "Grass.h"
#include "Sheep.h"
// Dodaj też pozostałe klasy: Dandelion, Toadstool itd.

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
            int pos_y;
            my_file.read((char*)&result, sizeof(int));
            Position pos{ pos_x, pos_y };

            int s_size;
            my_file.read((char*)&result, sizeof(int));
            string species;
            species.resize(s_size);
            my_file.read(&species[0], s_size);

            // 🔧 Stwórz odpowiedni organizm na podstawie species:
            if (species == "Grass") {
                auto org = make_unique<Grass>(pos);
                new_organisms.push_back(std::move(org));
            }
            else if (species == "Sheep") {
                auto org = make_unique<Sheep>(pos);
                new_organisms.push_back(std::move(org));
            }

            else if (species == "Wolf") {
                auto org = make_unique<Wolf>(pos);
                new_organisms.push_back(std::move(org));
            }

            else if (species == "Toadstool") {
                auto org = make_unique<Toadstool>(pos);
                new_organisms.push_back(std::move(org));
            }
            else if (species == "Dandelion") {
                auto org = make_unique<Dandelion>(pos);
                new_organisms.push_back(std::move(org));
            }
            
            else {
                std::cout << "Nieznany gatunek: " << species << ", tworzenie domyślnego organizmu NIE jest wspierane.\n" << std::endl;
            }
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
            if (!spec.empty()) {
                std::cout << "At position (" << wX << "," << wY << "), species: " << spec << std::endl;
            }
            result += spec.empty() ? std::string(1, separator) : spec;
        }
        result += "\n";
    }
    return result;
}


void World::removeOrganism(Organism& organismToRemove)
{
	auto it = std::find_if(organisms.begin(), organisms.end(),
        [&organismToRemove](const std::unique_ptr<Organism>& org) {
            return org.get() == &organismToRemove;
        });
    if (it != organisms.end()) {
        organisms.erase(it);
    }
}