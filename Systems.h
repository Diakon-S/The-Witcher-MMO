#pragma once
#include "Domain.h"
#include "Unit.h"
#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class ResourceSystem {
private:
    std::map<ResourceType, int> resources;
public:
    ResourceSystem() {
        resources[ResourceType::Wood] = 500;
        resources[ResourceType::Metal] = 500;
        resources[ResourceType::Energy] = 500;
    }
    void addResources(ResourceType type, int amount) { resources[type] += amount; }
    bool spendResources(ResourceType type, int amount) {
        if (resources[type] >= amount) { resources[type] -= amount; return true; }
        return false;
    }
    void printStats() const {
        std::cout << "–есурсы: ƒерево=" << resources.at(ResourceType::Wood)
            << ", ћеталл=" << resources.at(ResourceType::Metal)
            << ", Ёнерги€=" << resources.at(ResourceType::Energy) << "\n";
    }
};

class CombatSystem {
public:
    void resolveCombat(Unit& attacker, Unit& target) {
        int dmg = attacker.getAttack();
        target.takeDamage(dmg);
        std::cout << attacker.getName() << " атакует " << target.getName() << " на " << dmg << " урона.\n";
    }
};

class UnitManager {
public:
    std::vector<std::shared_ptr<Unit>> allUnits;
    std::vector<std::shared_ptr<ResourcePoint>> resourcePoints;
    int nextUnitId = 1;
    int nextResourceId = 1;

    UnitManager() {
        resourcePoints.push_back(std::make_shared<ResourcePoint>(nextResourceId++, ResourceType::Wood, 5, 5, 100));
        resourcePoints.push_back(std::make_shared<ResourcePoint>(nextResourceId++, ResourceType::Metal, 6, 6, 100));
    }

    std::shared_ptr<Unit> getUnitById(int id) {
        for (auto& u : allUnits) if (u->getId() == id) return u;
        return nullptr;
    }
    std::shared_ptr<ResourcePoint> getResourceById(int id) {
        for (auto& r : resourcePoints) if (r->id == id) return r;
        return nullptr;
    }
};

class BuildingManager {
public:
    std::vector<std::shared_ptr<Building>> buildings;
    int nextBuildingId = 1;

    std::shared_ptr<Building> getBuildingById(int id) {
        for (auto& b : buildings) if (b->id == id) return b;
        return nullptr;
    }
};