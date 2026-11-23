#pragma once
#include <string>

enum class BuildingType { Barracks, PowerPlant, Laboratory, Warehouse, Hospital };
enum class ResourceType { Wood, Metal, Energy };

class Building {
public:
    int id;
    BuildingType type;
    int x, y;
    int health, maxHealth;
    int buildProgress;
    char symbol;

    Building(int id, BuildingType type, int x, int y)
        : id(id), type(type), x(x), y(y), health(500), maxHealth(500), buildProgress(100), symbol(' ') {
        switch (type) {
        case BuildingType::Barracks: symbol = 'B'; break;
        case BuildingType::PowerPlant: symbol = 'P'; break;
        case BuildingType::Laboratory: symbol = 'L'; break;
        case BuildingType::Warehouse: symbol = 'W'; break;
        case BuildingType::Hospital: symbol = 'H'; break;
        }
    }
};

class ResourcePoint {
public:
    int id;
    ResourceType type;
    int x, y;
    int amount;

    ResourcePoint(int id, ResourceType type, int x, int y, int amount)
        : id(id), type(type), x(x), y(y), amount(amount) {
    }
};