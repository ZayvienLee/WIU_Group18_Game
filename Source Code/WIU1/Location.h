#pragma once
#include <string>
#include <vector>
#include "NPC.h"
#include "Item.h"

class Location
{
protected:
    std::string name;
    char symbol; // 'A', 'S', 'H', 'P', 'G', 'C', 'F', 'M', 'V'

    int INTERIOR_HEIGHT;
    int INTERIOR_WIDTH;

    char** interiorGrid;
    char** interiorGridActive;

    int spawnX; // Interior entry X coordinate
    int spawnY; // Interior entry Y coordinate

    std::vector<Item*> floorItems; // Items on the floor of the location

    std::vector<NPC*> npcs;


public:
    Location(std::string locName = "Unknown Location", char locSymbol = '?', int sizeX = 10, int sizeY = 10);
    virtual ~Location();

    // Variable Accessors
    std::string getName() const;
    char getSymbol() const;
    int getSpawnX() const;
    int getSpawnY() const;

    // Logic & Query Methods
	bool isIndoorWalkable(int x, int y) const;
	char getTileAt(int x, int y) const;
    void setTileAt(int x, int y, char tile);
    void displayInterior(int playerX, int playerY) const;

    void addFloorItem(Item* item); // Search and remove item from ground when picked up
    Item* pickupItemAt(int playerX, int playerY); // Helper for map rendering
    Item* getFloorItemAt(int x, int y) const;
	
    void addNPC(NPC* npc);
    NPC* getNPCat(int x, int y) const;
};