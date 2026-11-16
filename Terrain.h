#pragma once
#include <string>
#include <iostream>
#include "Unit.h"
#include "ConsoleColor.h"

class Terrain {
public:
    virtual ~Terrain() = default;
    virtual bool isPassable(UnitType type) const = 0;
    virtual double getSpeedModifier(UnitType type) const = 0;
    virtual double getDefenseBonus(UnitType type) const = 0;
    virtual char getSymbol() const = 0;
    virtual int getColor() const = 0;
    virtual Terrain* clone() const = 0;
};

class Plains : public Terrain {
public:
    bool isPassable(UnitType) const override { return true; }
    double getSpeedModifier(UnitType) const override { return 1.0; }
    double getDefenseBonus(UnitType) const override { return 0.0; }
    char getSymbol() const override { return '"'; }
    int getColor() const override { return Color::Green; }
    Terrain* clone() const override { return new Plains(*this); }
};

class Swamp : public Terrain {
public:
    bool isPassable(UnitType) const override { return true; }
    double getSpeedModifier(UnitType) const override { return 0.25; }
    double getDefenseBonus(UnitType) const override { return 0.0; }
    char getSymbol() const override { return '~'; }
    int getColor() const override { return Color::Blue; }
    Terrain* clone() const override { return new Swamp(*this); }
};

class Mountains : public Terrain {
public:
    bool isPassable(UnitType type) const override { return type == UnitType::Flying; }
    double getSpeedModifier(UnitType) const override { return 1.0; }
    double getDefenseBonus(UnitType) const override { return 10.0; }
    char getSymbol() const override { return '^'; }
    int getColor() const override { return Color::Gray; }
    Terrain* clone() const override { return new Mountains(*this); }
};

class TerrainProxy : public Terrain {
private:
    Terrain* realTerrain;
public:
    TerrainProxy(Terrain* terrain) : realTerrain(terrain) {}
    TerrainProxy(const TerrainProxy& other) : realTerrain(other.realTerrain->clone()) {}
    TerrainProxy& operator=(const TerrainProxy& other) {
        if (this != &other) { delete realTerrain; realTerrain = other.realTerrain->clone(); }
        return *this;
    }
    ~TerrainProxy() override { delete realTerrain; }

    bool isPassable(UnitType type) const override {
        return type == UnitType::Flying ? true : realTerrain->isPassable(type);
    }
    double getSpeedModifier(UnitType type) const override { return realTerrain->getSpeedModifier(type); }
    double getDefenseBonus(UnitType type) const override { return realTerrain->getDefenseBonus(type); }
    char getSymbol() const override { return realTerrain->getSymbol(); }
    int getColor() const override { return realTerrain->getColor(); }
    Terrain* clone() const override { return new TerrainProxy(*this); }
};