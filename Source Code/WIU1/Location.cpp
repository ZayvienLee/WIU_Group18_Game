#include <string>
#include <iostream>
#include <random>
#include <memory>
#include "Location.h"
#include "NPC.h"
#include "Item.h"
#include "Zombie.h"
#include "Food.h"
#include "Water.h"
#include "Medicine.h"
#include "Ammunition.h"
#include "Player.h"

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

    if (getSymbol() == 'V')
    {
        // The Final door to get through
        interiorGrid[0][INTERIOR_WIDTH / 2] = '^';
        interiorGridActive[0][INTERIOR_WIDTH / 2] = '^';
    }
}

Location::~Location()
{
    for (int r = 0; r < INTERIOR_HEIGHT; ++r)
    {
        delete[] interiorGrid[r]; // Deallocate Columns
        interiorGrid[r] = nullptr;

        delete[] interiorGridActive[r]; // Deallocate Columns
        interiorGridActive[r] = nullptr;
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

    npcs.clear();
    
    for (Zombie* zombie : zombies)
    {
        delete zombie;
    }
    zombies.clear();
}

void Location::spawnRandomZombies(int zombieCount)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrX(0, INTERIOR_WIDTH - 1), distrY(0, INTERIOR_HEIGHT - 1);

    int spawned = 0;
    int attempts = 0;
    while (spawned < zombieCount && attempts < zombieCount * 30)
    {
        int randomX = distrX(gen);
        int randomY = distrY(gen);

        if (interiorGrid[randomY][randomX] == '.' && getZombieAt(randomX, randomY) == nullptr && getNPCat(randomX, randomY) == nullptr)
        {
            zombies.push_back(new Zombie("Zombie", "A shambling infected corpse.", randomX, randomY, 'Z', 40, 40, 5));
            spawned++;
            attempts = 0;
        }
        else
        {
            attempts++;
        }
    }
}

void Location::updateZombies(int playerX, int playerY)
{
    for (Zombie* zombie : zombies)
    {
        if (zombie->getIsAlive())
        {
            zombie->moveRandomly(0, 0, INTERIOR_WIDTH - 1, INTERIOR_HEIGHT - 1, nullptr, this);
        }
    }
}

Zombie* Location::getZombieAt(int x, int y) const
{
    for (Zombie* zombie : zombies)
    {
        if (zombie->getIsAlive() && zombie->getX() == x && zombie->getY() == y)
        {
            return zombie;
        }
    }
    return nullptr;
}

void Location::removeZombie(Zombie* target)
{
    zombies.erase(std::remove(zombies.begin(), zombies.end(), target), zombies.end());
    delete target;
}

bool Location::isIndoorWalkable(int x, int y) const
{
    if (x < 0 || x >= INTERIOR_WIDTH || y < 0 || y >= INTERIOR_HEIGHT) return false;
    // Impassable interior walls/furniture marked with '#', etc.
    // Check if the space is '.' OR 'E'
    return (interiorGrid[y][x] == '.' || interiorGrid[y][x] == 'E' || interiorGrid[y][x] == '^');
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

void Location::displayInterior(int playerX, int playerY, Player& player) const {
    std::cout << "=== " << name << " Interior ===" << std::endl;
    for (int r = 0; r < INTERIOR_HEIGHT; ++r) {
        for (int c = 0; c < INTERIOR_WIDTH; ++c) {

            NPC* npc = getNPCat(c, r);
            Item* floorItem = getFloorItemAt(c, r);
            Zombie* zombie = getZombieAt(c, r);

            if (r == playerY && c == playerX) { // To render the Player
                std::cout << player.getColouredSymbol() << " "; // Player inside building
            }
            else if (zombie != nullptr) {
                std::cout << zombie->getColouredSymbol() << " "; // Render the Zombie
            }
            else if (npc != nullptr) { // NPC
                std::cout << npc->getColouredSymbol() << " ";
            }
            else if (floorItem != nullptr) {
                std::cout << floorItem->getColouredSymbol() << " "; // Item to render
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

int Location::getWidth() const
{
    return INTERIOR_WIDTH;
}

int Location::getHeight() const
{
    return INTERIOR_HEIGHT;
}

int Location::getInteriorFloorArea() const
{
    // Excluding the Bounding Walls
    return (INTERIOR_WIDTH - 2) * (INTERIOR_HEIGHT - 2);
}

void Location::generateRandomLayout(int furnitureCount, int itemCount)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrX(1, INTERIOR_WIDTH - 2);
    std::uniform_int_distribution<int> distrY(1, INTERIOR_HEIGHT - 2);
    std::uniform_int_distribution<int> itemTypes(0, 3);

    int placed = 0, attempts = 0;
    while (placed < furnitureCount && attempts < furnitureCount * 30)
    {
        int randomX = distrX(gen);
        int randomY = distrY(gen);
        bool isSpawn = (randomX == spawnX && randomY == spawnY);
        bool isOccupied = (getNPCat(randomX, randomY) != nullptr) || (getFloorItemAt(randomX, randomY) != nullptr);

        if (!isSpawn && !isOccupied && interiorGrid[randomY][randomX] == '.')
        {
            bool nearDoor = false;

            for (int dy = -2; dy <= 2; ++dy)
            {
                for (int dx = -2; dx <= 2; ++dx)
                {
                    int checkY = randomY + dx;
                    int checkX = randomX + dy;

                    if (checkY >= 0 && checkY < INTERIOR_HEIGHT && checkX >= 0 && checkX < INTERIOR_WIDTH)
                    {
                        if (interiorGridActive[checkY][checkX] == 'E' || interiorGridActive[checkY][checkX] == '^')
                        {
                            nearDoor = true;
                        }
                    }
                }
            }

            if (!nearDoor)
            {
                interiorGrid[randomY][randomX] = '#';
                interiorGridActive[randomY][randomX] = '#';
                placed++;
                attempts = 0;
            }
            else
            {
                attempts++;
            }
        }
        else
        {
            attempts++;
        }
    }

    int spawned = 0; attempts = 0;
    while (spawned < itemCount && attempts < itemCount * 30)
    {
        int randomX = distrX(gen);
        int randomY = distrY(gen);

        bool isOccupied = (getNPCat(randomX, randomY) != nullptr) || (getFloorItemAt(randomX, randomY) != nullptr);

        if (isIndoorWalkable(randomX, randomY) && getFloorItemAt(randomX, randomY) == nullptr && getNPCat(randomX, randomY) == nullptr)
        {
            // Next check to ensure that it is not adjacent to an entrance to the building '.'
            // Nor near any obstacles.
            // Also ensuring that no obstacles encase an item and make it in accessable
            bool nearDoorOrObstacle = false;
            for (int dy = -1; dy <= 1; ++dy)
            {
                for (int dx = -1; dx <= 1; ++dx)
                {
                    int checkY = randomY + dy;
                    int checkX = randomX + dx;

                    if (checkY >= 0 && checkY < INTERIOR_HEIGHT && checkX >= 0 && checkX < INTERIOR_WIDTH)
                    {
                        if (interiorGridActive[checkY][checkX] == '#')
                        {
                            nearDoorOrObstacle = true;
                        }
                    }
                }
            }

            // If it is safe, add the item into the map
            if (!nearDoorOrObstacle)
            {

                int type = itemTypes(gen);
                Item* newItem = nullptr;

                if (type == 0) newItem = new Food();
                else if (type == 1) newItem = new Water();
                else if (type == 2) newItem = new Medicine();
                else if (type == 3) newItem = new Ammunition();

                newItem->setPosition(randomX, randomY);
                addFloorItem(newItem);

                spawned++;
                attempts = 0;
            }
            else
            {
                attempts++;
            }
        }
        else
        {
            attempts++;
        }
    }
}

void Location::addNPC(NPC* npc)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrX(0, INTERIOR_WIDTH - 1);
    std::uniform_int_distribution<int> distrY(0, INTERIOR_HEIGHT - 1);

    int randX = 0;
    int randY = 0;

    do
    {
        randX = distrX(gen);
        randY = distrY(gen);

    } while (
        !isIndoorWalkable(randX, randY) ||
        getZombieAt(randX, randY) != nullptr ||
        getNPCat(randX, randY) != nullptr
        );

    npc->setPosition(randX, randY);

    npcs.push_back(npc);
}

NPC* Location::getNPCat(int x, int y) const
{
    for (NPC* npc : npcs)
    {
        if (npc != nullptr)
        {
            if (npc->getX() == x && npc->getY() == y)
            {
                return npc;
            }
        }
    }

    return nullptr;
}