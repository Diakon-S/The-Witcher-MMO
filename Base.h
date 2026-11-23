#pragma once
#include <iostream>
#include "Observer.h"

class Base : public IObserver {
private:
    int health;
    int maxUnits;
    int maxBuildings;
    int currentUnitsCount;
    int resourcesGold;
public:
    Base(int hp, int maxU, int maxB) : health(hp), maxUnits(maxU), maxBuildings(maxB), currentUnitsCount(0), resourcesGold(0) {}

    int getMaxUnits() const { return maxUnits; }
    int getMaxBuildings() const { return maxBuildings; }
    int getHealth() const { return health; }

    void takeDamage(int amount) {
        health -= amount;
        if (health < 0) health = 0;
        std::cout << "[БАЗА] Получен урон: " << amount << "! Осталось HP: " << health << "\n";
    }

    bool isDestroyed() const { return health <= 0; }

    void onUnitEvent(const UnitEvent& event) override {
        if (event.eventType == UnitEvent::Type::Created) {
            currentUnitsCount++;
            std::cout << "[БАЗА] Создан юнит: " << event.unitName << "\n";
        }
        else if (event.eventType == UnitEvent::Type::Destroyed) {
            currentUnitsCount--;
            std::cout << "[БАЗА] Юнит " << event.unitName << " уничтожен!\n";
        }
        else if (event.eventType == UnitEvent::Type::Damaged) {
            std::cout << "[БАЗА] Юнит " << event.unitName << " получил " << event.value << " урона.\n";
        }
        else if (event.eventType == UnitEvent::Type::ResourcesCollected) {
            resourcesGold += event.value;
            std::cout << "[БАЗА] Собрано " << event.value << " золота. (Всего: " << resourcesGold << ")\n";
        }
    }

    void printStatus() const {
        std::cout << "База HP: " << health << " | Юниты: " << currentUnitsCount << "/" << maxUnits << " | Золото: " << resourcesGold;
    }
};