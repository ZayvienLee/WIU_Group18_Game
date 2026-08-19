#pragma once
#include <string>

class Location
{
protected:
    std::string name;
    char symbol; // 'A', 'S', 'H', 'P', 'G', 'C', 'F', 'M', 'V'

    static const int INTERIOR_HEIGHT = 10;
    static const int INTERIOR_WIDTH = 10;
    char interiorGrid[INTERIOR_HEIGHT][INTERIOR_WIDTH];

    int spawnX; // Interior entry X coordinate
    int spawnY; // Interior entry Y coordinate

public:
    Location(std::string locName = "Unknown Location", char locSymbol = '?');
    virtual ~Location() = default;

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
	
};