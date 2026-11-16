#pragma once
#include <iostream>
#include "Unit.h"

class InteractionStrategy {
public:
    virtual ~InteractionStrategy() = default;
    virtual void apply(Unit& unit) = 0;
};

class AttackBoostStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) override {
        unit.increaseAttack(15);
        std::cout << unit.getName() << " получает +15 к атаке!\n";
    }
};

class ArmorBoostStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) override {
        unit.increaseArmor(15);
        std::cout << unit.getName() << " получает +15 к броне!\n";
    }
};

class HealthRestoreStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) override {
        unit.heal(50);
        std::cout << unit.getName() << " восстанавливает 50 HP!\n";
    }
};