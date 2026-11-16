#pragma once
#include "Base.h"
#include "GameField.h"
#include "UnitFactory.h"
#include <memory>

class GameController {
private:
    Base base;
    GameField field;
    int nextUnitId;
public:
    GameController() : base(1000, 25), field(15, 15, 25), nextUnitId(1) {}

    Base& getBase() { return base; }
    GameField& getField() { return field; }

    std::unique_ptr<Unit> spawnUnit(const UnitFactory& factory, UnitType type, int x, int y) {
        auto unit = factory.createUnit(type, nextUnitId++, x, y);
        if (unit) {
            unit->subscribe(&base);
            unit->notify({ UnitEvent::Type::Created, unit->getId(), unit->getName(), 0 });
        }
        return unit;
    }
};