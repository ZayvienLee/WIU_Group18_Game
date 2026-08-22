#include "Location.h"
#include <string>
#include <iostream>
#include "NPC.h"
#include "Item.h"

Location::Location(std::string locName, char locSymbol, int sizeX, int sizeY)
{
    name = locName;
    symbol = locSymbol;

    INTERIOR_WIDTH = sizeX;
    INTERIOR_HEIGHT = sizeY;

    /* Set the spawn to the space above the entrance of the building */
    spawnX = sizeX / 2;
    spawnY = sizeY - 2;


    // Initialise the grids accordingly
    interiorGrid = new char* [INTERIOR_HEIGHT]; // Rows
    interiorGridActive = new char* [INTERIOR_HEIGHT]; // Rows
    
    for (int i = 0; i < INTERIOR_HEIGHT; ++i) {
        interiorGrid[i] = new char[INTERIOR_WIDTH]; // Columns
        interiorGridActive[i] = new char[INTERIOR_WIDTH]; // Columns
    }

    // Fill the interior with the floor spaces and perimeter walls
    for (int r = 0; r < INTERIOR_HEIGHT; ++r) {
        for (int c = 0; c < INTERIOR_WIDTH; ++c) {
            if (r == 0 || r == INTERIOR_HEIGHT - 1 || c == 0 || c == INTERIOR_WIDTH - 1) {
                interiorGrid[r][c] = '#'; // Exterior interior wall
                interiorGridActive[r][c] = interiorGrid[r][c];
            }
            else {
                interiorGrid[r][c] = '.'; // Walkable floor
                interiorGridActive[r][c] = interiorGrid[r][c];
            }
        }
    }

    // Default exit door at bottom wall at the center of the building
    interiorGrid[INTERIOR_HEIGHT - 1][INTERIOR_WIDTH / 2] = 'E';
    interiorGridActive[INTERIOR_HEIGHT - 1][INTERIOR_WIDTH / 2] = 'E';
}

Location::~Location()
{
    for (int i = 0; i < INTERIOR_HEIGHT; ++i)
    {
        delete[] interiorGrid[i]; // Deallocate Columns
        interiorGrid[i] = nullptr;

        delete[] interiorGridActive[i]; // Deallocate Columns
        interiorGridActive[i] = nullptr;
    }

    delete[] interiorGrid; // Deallocate Rows
    interiorGrid = nullptr;

    delete[] interiorGridActive; // Deallocate Rows
    interiorGridActive = nullptr;


    for (Item* item : floorItems)
    {
        delete item;
    }
    floorItems.clear();
}

bool Location::isIndoorWalkable(int x, int y) const
{
    if (x < 0 || x >= INTERIOR_WIDTH || y < 0 || y >= INTERIOR_HEIGHT) return false;
    // Impassable interior walls/furniture marked with '#', etc.
    // Check if the space is '.' OR 'E'
    return (interiorGrid[y][x] == '.' || interiorGrid[y][x] == 'E');
}

char Location::getTileAt(int x, int y) const
{
    if (x < 0 || x >= INTERIOR_WIDTH || y < 0 || y >= INTERIOR_HEIGHT) return '#';
    return interiorGridActive[y][x];
}

void Location::setTileAt(int x, int y, char tile) {
    if (x >= 0 && x < INTERIOR_WIDTH && y >= 0 && y < INTERIOR_HEIGHT) {
        interiorGridActive[y][x] = tile;
    }
}

void Location::displayInterior(int playerX, int playerY) const {
    std::cout << "=== " << name << " Interior ===" << std::endl;
    for (int r = 0; r < INTERIOR_HEIGHT; ++r) {
        for (int c = 0; c < INTERIOR_WIDTH; ++c) {

            NPC* npc = getNPCat(c, r);
            Item* floorItem = getFloorItemAt(c, r);

            if (r == playerY && c == playerX) { // To render the Player
                std::cout << "P "; // Player inside building
            }
            else if (npc != nullptr) { // NPC
                std::cout << npc->getSymbol() << " ";
            }
            else if (floorItem != nullptr) {
                std::cout << floorItem->getSymbol() << " "; // Item to render
            }
            else {
                std::cout << interiorGridActive[r][c] << " "; // Tile + space
            }
        }
        std::cout << std::endl;
    }
}

void Location::addFloorItem(Item* item)
{
    if (item == nullptr) return;
    item->setInInventory(false);

    // Prevent overlapping: if target space already has an item, drop in adjacent walkable spot
    if (getFloorItemAt(item->getX(), item->getY()) != nullptr)
    {
        int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
        int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };

        for (int i = 0; i < 8; ++i)
        {
            int newX = item->getX() + dx[i];
            int newY = item->getY() + dy[i];

            if (isIndoorWalkable(newX, newY) && getFloorItemAt(newX, newY) == nullptr)
            {
                item->setPosition(newX, newY);
                break;
            }
        }
    }

    floorItems.push_back(item);
}

Item* Location::pickupItemAt(int playerX, int playerY)
{
    for (auto it = floorItems.begin(); it != floorItems.end(); ++it)
    {
        if ((*it)->getX() == playerX && (*it)->getY() == playerY) {
            Item* picked = *it;
            floorItems.erase(it); // Remove from floor item list so it no longer renders
            picked->setInInventory(true);
            return picked;
        }
    }
    return nullptr;
}

Item* Location::getFloorItemAt(int x, int y) const
{
    for (Item* item : floorItems)
    {
        if (item->getX() == x && item->getY() == y) {
            return item;
        }
    }
    return nullptr;
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

void Location::addNPC(NPC* npc)
{
    npcs.push_back(npc);
}

NPC* Location::getNPCat(int x, int y) const
{
    for (NPC* npc : npcs)
    {
        if (npc->getX() == x && npc->getY() == y)
        {
            return npc;
        }
    }

    return nullptr;
}