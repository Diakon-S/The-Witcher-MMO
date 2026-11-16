#pragma once
#include <algorithm>

class Health {
private:
    int currentValue;
    int maxValue;
public:
    Health(int maxVal = 100) : maxValue(std::max(1, maxVal)), currentValue(std::max(1, maxVal)) {}
    void decrease(int amount) { currentValue = std::max(0, currentValue - amount); }
    void increase(int amount) { currentValue = std::min(maxValue, currentValue + amount); }
    bool isDead() const { return currentValue <= 0; }
    int getValue() const { return currentValue; }
    int getMaxValue() const { return maxValue; }
};

class Armor {
private:
    int value;
public:
    Armor(int val = 0) : value(std::max(0, val)) {}
    int reduceDamage(int incomingDamage) const { return std::max(1, incomingDamage - value); }
    int getValue() const { return value; }
    void increase(int amount) { value += amount; }
};

class Attack {
private:
    int value;
public:
    Attack(int val = 10) : value(std::max(0, val)) {}
    int calculateDamage(const Armor& targetArmor) const { return targetArmor.reduceDamage(value); }
    int getValue() const { return value; }
    void increase(int amount) { value += amount; }
};