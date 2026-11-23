#pragma once
#include "Unit.h"
#include "Strategy.h"
#include "ConsoleColor.h"
#include <memory>

class NeutralObject {
public:
    virtual ~NeutralObject() = default;
    virtual void interact(Unit& unit) = 0;
    virtual char getSymbol() const = 0;
    virtual int getColor() const = 0;
    virtual std::unique_ptr<NeutralObject> clone() const = 0;
};
class TreasureChest : public NeutralObject {
public:
    void interact(Unit& unit) override { std::cout << "[Сундук] " << unit.getName() << " собирает +50 золота!\n"; unit.notify({ UnitEvent::Type::ResourcesCollected, unit.getId(), unit.getName(), 50 }); }
    char getSymbol() const override { return 'C'; }
    int getColor() const override { return Color::Yellow; }
    std::unique_ptr<NeutralObject> clone() const override { return std::make_unique<TreasureChest>(*this); }
};
class Trap : public NeutralObject {
public:
    void interact(Unit& unit) override { std::cout << "[Ловушка] " << unit.getName() << " наступает на ловушку!\n"; unit.takeDamage(40); }
    char getSymbol() const override { return 'T'; }
    int getColor() const override { return Color::Red; }
    std::unique_ptr<NeutralObject> clone() const override { return std::make_unique<Trap>(*this); }
};
class Altar : public NeutralObject {
private:
    std::shared_ptr<InteractionStrategy> infantryStrategy, tankStrategy, medicStrategy;
public:
    Altar() {
        infantryStrategy = std::make_shared<AttackBoostStrategy>();
        tankStrategy = std::make_shared<ArmorBoostStrategy>();
        medicStrategy = std::make_shared<HealthRestoreStrategy>();
    }
    void interact(Unit& unit) override {
        if (unit.getType() == UnitType::Tank) tankStrategy->apply(unit);
        else if (unit.getType() == UnitType::Medic) medicStrategy->apply(unit);
        else infantryStrategy->apply(unit);
    }
    char getSymbol() const override { return 'A'; }
    int getColor() const override { return Color::Magenta; }
    std::unique_ptr<NeutralObject> clone() const override { return std::make_unique<Altar>(*this); }
};