#pragma once
#include <iostream>
#include "Observer.h"

class Base : public IObserver {
private:
    int health;
    int maxUnits;
    int defenseLevel;
    int resources;
    int currentUnitsCount;
public:
    Base(int hp, int maxU) : health(hp), maxUnits(maxU), defenseLevel(10), resources(0), currentUnitsCount(0) {}

    void onUnitEvent(const UnitEvent& event) override {
        if (event.eventType == UnitEvent::Type::Created) {
            currentUnitsCount++;
        }
        else if (event.eventType == UnitEvent::Type::Damaged) {
            std::cout << "[БАЗА] Зафиксирован урон по юниту " << event.unitName << ": -" << event.value << " HP.\n";
        }
        else if (event.eventType == UnitEvent::Type::Destroyed) {
            currentUnitsCount--;
            std::cout << "[БАЗА] Юнит " << event.unitName << " уничтожен. Освобожден слот!\n";
        }
        else if (event.eventType == UnitEvent::Type::ResourcesCollected) {
            resources += event.value;
            std::cout << "[БАЗА] Получено ресурсов: " << event.value << ". Всего: " << resources << "\n";
        }
    }

    void printStatus() const {
        std::cout << "=== СТАТУС БАЗЫ ===\n"
            << "HP: " << health << " | Юнитов: " << currentUnitsCount << "/" << maxUnits
            << " | Ресурсы: " << resources << "\n";
    }
};