#pragma once
#include <memory>
#include "Units.h"

// Базовый интерфейс фабрики
class UnitFactory {
public:
    virtual ~UnitFactory() = default;
    virtual std::unique_ptr<Unit> createUnit(Role role, int x, int y) const = 0;
};

class NorthFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(Role role, int x, int y) const override {
        if (role == Role::Melee) return std::make_unique<RedanianKnight>(x, y);
        if (role == Role::Ranged) return std::make_unique<KaedweniCrossbowman>(x, y);
        if (role == Role::Universal) return std::make_unique<Zoltan>(x, y);
        return nullptr;
    }
};

class NilfgaardFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(Role role, int x, int y) const override {
        if (role == Role::Melee) return std::make_unique<ImperaBrigade>(x, y);
        if (role == Role::Ranged) return std::make_unique<NauzicaaBrigade>(x, y);
        if (role == Role::Universal) return std::make_unique<Cahir>(x, y);
        return nullptr;
    }
};

class MonsterFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(Role role, int x, int y) const override {
        if (role == Role::Melee) return std::make_unique<Ghoul>(x, y);
        if (role == Role::Ranged) return std::make_unique<Wraith>(x, y);
        if (role == Role::Universal) return std::make_unique<Griffin>(x, y);
        return nullptr;
    }
};

class ScoiataelFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(Role role, int x, int y) const override {
        if (role == Role::Melee) return std::make_unique<ElvenSwordmaster>(x, y);
        if (role == Role::Ranged) return std::make_unique<Isengrim>(x, y);
        if (role == Role::Universal) return std::make_unique<Iorveth>(x, y);
        return nullptr;
    }
};

class HeroFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(Role role, int x, int y) const override {
        if (role == Role::Melee) return std::make_unique<Geralt>(x, y);
        if (role == Role::Ranged) return std::make_unique<Yennefer>(x, y);
        if (role == Role::Universal) return std::make_unique<Ciri>(x, y);
        return nullptr;
    }
};