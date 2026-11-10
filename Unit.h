#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "Attributes.h"

enum class Role { Melee, Ranged, Universal };

enum class Faction { North, Nilfgaard, Monsters, Scoiatael, Heroes };

class Unit {
protected:
    std::string name;
    int posX;
    int posY;
    Health health;
    Armor armor;
    Attack attack;
    char symbol;

public:
    Unit(const std::string& n, int x, int y, int hp, int arm, int atk, char sym)
        : name(n), posX(x), posY(y), health(hp), armor(arm), attack(atk), symbol(sym) {
    }

    virtual ~Unit() = default;

    virtual std::unique_ptr<Unit> clone() const = 0;
    virtual Role getRole() const = 0;
    virtual Faction getFaction() const = 0;

    int getX() const { return posX; }
    int getY() const { return posY; }
    char getSymbol() const { return symbol; }
    const std::string& getName() const { return name; }
    const Armor& getArmor() const { return armor; }
    const Attack& getAttack() const { return attack; }

    int getHp() const { return health.getValue(); }
    bool isDead() const { return health.isDead(); }

    void move(int newX, int newY) { posX = newX; posY = newY; }

    void takeDamage(int damage) {
        int actualDamage = armor.reduceDamage(damage);
        health.decrease(actualDamage);

        std::cout << "[" << symbol << "] " << name << " получает " << actualDamage
            << " урона (броня поглотила " << (damage - actualDamage) << "). ";

        if (isDead()) {
            std::cout << "Юнит погибает!\n";
        }
        else {
            std::cout << "Осталось HP: " << getHp() << "/" << health.getMaxValue() << "\n";
        }
    }

    void printStats() const {
        std::cout << "[" << symbol << "] " << name
            << " | HP: " << getHp() << "/" << health.getMaxValue()
            << " | Броня: " << armor.getValue()
            << " | Атака: " << attack.getValue() << "\n";
    }
};