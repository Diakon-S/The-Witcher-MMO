#pragma once
#include <memory>
#include "Units.h"

class UnitFactory {
public:
    virtual ~UnitFactory() = default;
    virtual std::unique_ptr<Unit> createUnit(UnitType type, int id, int x, int y) const = 0;
};

class HeroFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(UnitType type, int id, int x, int y) const override {
        if (type == UnitType::Infantry) return std::make_unique<Geralt>(id, x, y);
        if (type == UnitType::Scout)    return std::make_unique<Ciri>(id, x, y);
        if (type == UnitType::Medic)    return std::make_unique<Yennefer>(id, x, y);
        return nullptr;
    }
};

class NorthFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(UnitType type, int id, int x, int y) const override {
        if (type == UnitType::Infantry) return std::make_unique<VernonRoche>(id, x, y);
        if (type == UnitType::Tank)     return std::make_unique<RedanianKnight>(id, x, y);
        if (type == UnitType::Worker)   return std::make_unique<DwarfMiner>(id, x, y);
        return nullptr;
    }
};

class NilfgaardFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(UnitType type, int id, int x, int y) const override {
        if (type == UnitType::Infantry) return std::make_unique<Morteisen>(id, x, y);
        if (type == UnitType::Scout)    return std::make_unique<LethoOfGulet>(id, x, y);
        if (type == UnitType::Medic)    return std::make_unique<Albrich>(id, x, y);
        return nullptr;
    }
};

class MonsterFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(UnitType type, int id, int x, int y) const override {
        if (type == UnitType::Infantry) return std::make_unique<Ghoul>(id, x, y);
        if (type == UnitType::Scout)    return std::make_unique<Harpy>(id, x, y);
        if (type == UnitType::Tank)     return std::make_unique<Golem>(id, x, y);
        return nullptr;
    }
};

class ScoiataelFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(UnitType type, int id, int x, int y) const override {
        if (type == UnitType::Infantry) return std::make_unique<Filavandrel>(id, x, y);
        if (type == UnitType::Scout)    return std::make_unique<Iorveth>(id, x, y);
        if (type == UnitType::Medic)    return std::make_unique<Eithne>(id, x, y);
        return nullptr;
    }
};