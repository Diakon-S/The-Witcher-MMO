#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include "Attributes.h"
#include "Observer.h"

enum class UnitType { Infantry, Scout, Tank, Worker, Medic };
enum class Faction { North, Nilfgaard, Monsters, Scoiatael, Heroes };

class Unit : public IObservable {
protected:
    int id;
    std::string name;
    int posX, posY;
    Health health;
    Armor armor;
    Attack attack;
    char symbol;
    UnitType type;
    Faction faction;
    std::string currentOrder;

public:
    int maxAP = 2;
    int currentAP = 2;

    Unit(int id, const std::string& n, Faction f, UnitType t, int x, int y, int hp, int arm, int atk, char sym)
        : id(id), name(n), faction(f), type(t), posX(x), posY(y), health(hp), armor(arm), attack(atk), symbol(sym), currentOrder("Ожидает") {
    }

    virtual ~Unit() = default;
    virtual std::unique_ptr<Unit> clone() const = 0;

    int getId() const { return id; }
    UnitType getType() const { return type; }
    char getSymbol() const { return symbol; }
    const std::string& getName() const { return name; }
    int getX() const { return posX; }
    int getY() const { return posY; }
    int getHp() const { return health.getValue(); }
    int getMaxHp() const { return health.getMaxValue(); }
    int getArmor() const { return armor.getValue(); }
    int getAttack() const { return attack.getValue(); }
    bool isDead() const { return health.isDead(); }
    std::string getOrder() const { return currentOrder; }

    void move(int newX, int newY) { posX = newX; posY = newY; currentOrder = "Движется"; }
    void increaseArmor(int amount) { armor.increase(amount); }
    void increaseAttack(int amount) { attack.increase(amount); }

    void takeDamage(int damage) {
        if (isDead()) return;
        int actualDamage = armor.reduceDamage(damage);
        health.decrease(actualDamage);
        notify({ UnitEvent::Type::Damaged, id, name, actualDamage });
        if (isDead()) notify({ UnitEvent::Type::Destroyed, id, name, 0 });
    }

    void heal(int amount) {
        if (isDead()) return;
        health.increase(amount);
    }

    void resetAP() { currentAP = maxAP; currentOrder = "Ожидает"; }
    void spendAP(int amount) { currentAP = std::max(0, currentAP - amount); }
};

inline void IObservable::notify(const UnitEvent& event) {
    for (auto obs : observers) obs->onUnitEvent(event);
}