#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>
#include "Attributes.h"
#include "Observer.h"

enum class UnitType { Infantry, Archer, Mage, Flying };
enum class Faction { North, Nilfgaard, Monsters, Scoiatael, Heroes };

struct UnitTypeInfo {
    int maxHealth;
    int baseAttack;
    double baseSpeed;
    int cost;
};

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

public:
    Unit(int id, const std::string& n, Faction f, UnitType t, int x, int y, int hp, int arm, int atk, char sym)
        : id(id), name(n), faction(f), type(t), posX(x), posY(y), health(hp), armor(arm), attack(atk), symbol(sym) {
    }

    virtual ~Unit() = default;

    virtual std::unique_ptr<Unit> clone() const = 0;

    int getId() const { return id; }
    UnitType getType() const { return type; }
    Faction getFaction() const { return faction; }
    char getSymbol() const { return symbol; }
    const std::string& getName() const { return name; }
    int getX() const { return posX; }
    int getY() const { return posY; }
    int getHp() const { return health.getValue(); }
    bool isDead() const { return health.isDead(); }
    const Armor& getArmor() const { return armor; }
    const Attack& getAttack() const { return attack; }

    void move(int newX, int newY) { posX = newX; posY = newY; }
    void increaseArmor(int amount) { armor.increase(amount); }
    void increaseAttack(int amount) { attack.increase(amount); }

    void attackUnit(Unit& target) {
        if (this->isDead()) return;
        std::cout << "[" << symbol << "] " << name << " атакует [" << target.getSymbol() << "] " << target.getName() << "!\n";
        target.takeDamage(this->attack.getValue());
    }

    void takeDamage(int damage) {
        int actualDamage = armor.reduceDamage(damage);
        health.decrease(actualDamage);

        std::cout << "  -> [" << symbol << "] " << name << " получает " << actualDamage << " урона. Осталось HP: " << getHp() << "/" << health.getMaxValue() << "\n";

        notify({ UnitEvent::Type::Damaged, id, name, actualDamage });

        if (isDead()) {
            notify({ UnitEvent::Type::Destroyed, id, name, 0 });
            std::cout << "  -> [" << symbol << "] " << name << " погибает!\n";
        }
    }

    void heal(int amount) {
        health.increase(amount);
        std::cout << "  -> [" << symbol << "] " << name << " вылечен на " << amount << " HP. (Текущее HP: " << getHp() << ")\n";
    }

    static const UnitTypeInfo& getInfo(UnitType type) {
        static const std::unordered_map<UnitType, UnitTypeInfo> infoMap = {
            { UnitType::Infantry, { 150, 20, 1.0, 100 } },
            { UnitType::Archer,   { 100, 30, 1.0, 120 } },
            { UnitType::Mage,     { 80,  50, 0.8, 200 } },
            { UnitType::Flying,   { 120, 40, 2.0, 250 } }
        };
        return infoMap.at(type);
    }

    void printStats() const {
        std::cout << "[" << symbol << "] " << name << " (ID: " << id << ") | HP: " << getHp()
            << " | Броня: " << armor.getValue() << " | Атака: " << attack.getValue() << "\n";
    }
};

inline void IObservable::notify(const UnitEvent& event) {
    for (auto obs : observers) obs->onUnitEvent(event);
}