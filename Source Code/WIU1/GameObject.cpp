#include "GameObject.h"

GameObject::GameObject(const std::string& name, const std::string& description, int x, int y, char symbol)
    : name(name), description(description), positionX(x), positionY(y), symbol(symbol) {
        
    }

