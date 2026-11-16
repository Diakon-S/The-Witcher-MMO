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
    void interact(Unit& unit) override {
        std::cout << "[Сундук] " << unit.getName() << " собирает ресурсы (+50 золота)!\n";
        unit.notify({ UnitEvent::Type::ResourcesCollected, unit.getId(), unit.getName(), 50 });
    }
    char getSymbol() const override { return 'c'; }
    int getColor() const override { return Color::Yellow; }
    std::unique_ptr<NeutralObject> clone() const override { return std::make_unique<TreasureChest>(*this); }
};

class Trap : public NeutralObject {
public:
    void interact(Unit& unit) override {
        std::cout << "[Ловушка] " << unit.getName() << " наступает на ловушку!\n";
        unit.takeDamage(40);
    }
    char getSymbol() const override { return 't'; }
    int getColor() const override { return Color::Red; }
    std::unique_ptr<NeutralObject> clone() const override { return std::make_unique<Trap>(*this); }
};

class Altar : public NeutralObject {
private:
    std::shared_ptr<InteractionStrategy> infantryStrategy;
    std::shared_ptr<InteractionStrategy> archerStrategy;
    std::shared_ptr<InteractionStrategy> mageStrategy;

public:
    Altar() {
        infantryStrategy = std::make_shared<ArmorBoostStrategy>();
        archerStrategy = std::make_shared<AttackBoostStrategy>();
        mageStrategy = std::make_shared<HealthRestoreStrategy>();
    }

    void interact(Unit& unit) override {
        std::cout << "[Алтарь] Выбор эффекта для " << unit.getName() << "...\n";
        switch (unit.getType()) {
        case UnitType::Infantry:
            infantryStrategy->apply(unit);
            break;
        case UnitType::Archer:
            archerStrategy->apply(unit);
            break;
        case UnitType::Mage:
            mageStrategy->apply(unit);
            break;
        case UnitType::Flying:
            archerStrategy->apply(unit);
            break;
        }
    }
    char getSymbol() const override { return 'a'; }
    int getColor() const override { return Color::Magenta; }

    std::unique_ptr<NeutralObject> clone() const override { return std::make_unique<Altar>(*this); }
};

class EnergySource : public NeutralObject {
public:
    void interact(Unit& unit) override {
        std::cout << "[Источник] " << unit.getName() << " восстанавливает здоровье.\n";
        unit.heal(100);
    }
    char getSymbol() const override { return 'e'; }
    int getColor() const override { return Color::Cyan; }
    std::unique_ptr<NeutralObject> clone() const override { return std::make_unique<EnergySource>(*this); }
};

inline void operator+(Unit& unit, TreasureChest& chest) { chest.interact(unit); }
inline void operator-(Unit& unit, Trap& trap) { trap.interact(unit); }
inline void operator*(Unit& unit, Altar& altar) { altar.interact(unit); }
inline void operator/(Unit& unit, EnergySource& source) { source.interact(unit); }