#include "Location.h"
#include <string>
#include <iostream>

Location::Location(std::string locName, char locSymbol, int sizeX, int sizeY)
{
    name = locName;
    symbol = locSymbol;

    INTERIOR_WIDTH = sizeX;
    INTERIOR_HEIGHT = sizeY;

    /* Set the spawn to the space above the entrance of the building */
    spawnX = sizeX / 2;
    spawnY = sizeY - 2;


    // Initialise the grid accordingly
    interiorGrid = new char* [INTERIOR_HEIGHT]; // Rows
    
    for (int i = 0; i < INTERIOR_HEIGHT; ++i) {
        interiorGrid[i] = new char[INTERIOR_WIDTH]; // Columns
    }

    // Fill the interior with the floor spaces and perimeter walls
    for (int r = 0; r < INTERIOR_HEIGHT; ++r) {
        for (int c = 0; c < INTERIOR_WIDTH; ++c) {
            if (r == 0 || r == INTERIOR_HEIGHT - 1 || c == 0 || c == INTERIOR_WIDTH - 1) {
                interiorGrid[r][c] = '#'; // Exterior interior wall
            }
            else {
                interiorGrid[r][c] = '.'; // Walkable floor
            }
        }
    }

    // Default exit door at bottom wall at the center of the building
    interiorGrid[INTERIOR_HEIGHT - 1][INTERIOR_WIDTH / 2] = 'E';
}

Location::~Location()
{
    for (int i = 0; i < INTERIOR_HEIGHT; ++i) {
        delete[] interiorGrid[i]; // Deallocate Columns
        interiorGrid[i] = nullptr;
    }

    delete[] interiorGrid; // Deallocate Rows
    interiorGrid = nullptr;
}

bool Location::isIndoorWalkable(int x, int y) const
{
    if (x < 0 || x >= INTERIOR_WIDTH || y < 0 || y >= INTERIOR_HEIGHT) return false;
    // Impassable interior walls/furniture marked with '#'
    return interiorGrid[y][x] != '#';
}

char Location::getTileAt(int x, int y) const
{
    if (x < 0 || x >= INTERIOR_WIDTH || y < 0 || y >= INTERIOR_HEIGHT) return '#';
    return interiorGrid[y][x];
}

void Location::setTileAt(int x, int y, char tile) {
    if (x >= 0 && x < INTERIOR_WIDTH && y >= 0 && y < INTERIOR_HEIGHT) {
        interiorGrid[y][x] = tile;
    }
}

void Location::displayInterior(int playerX, int playerY) const {
    std::cout << "=== " << name << " Interior ===" << std::endl;
    for (int r = 0; r < INTERIOR_HEIGHT; ++r) {
        for (int c = 0; c < INTERIOR_WIDTH; ++c) {
            if (r == playerY && c == playerX) {
                std::cout << "P "; // Player inside building
            }
            else {
                std::cout << interiorGrid[r][c] << " ";
            }
        }
        std::cout << std::endl;
    }
}

std::string Location::getName() const
{
    return name;
}

char Location::getSymbol() const
{
    return symbol;
}

int Location::getSpawnX() const
{
    return spawnX;
}

int Location::getSpawnY() const
{
    return spawnY;
}
