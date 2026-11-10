#pragma once
#include <memory>
#include "Units.h"

class UnitFactory {
public:
    virtual ~UnitFactory() = default;
    virtual std::unique_ptr<Unit> createUnit(Role role, int x, int y) const = 0;
};

class NorthFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(Role role, int x, int y) const override {
        if (role == Role::Melee) return std::make_unique<PrinceStennis>(x, y);
        if (role == Role::Ranged) return std::make_unique<Dethmold>(x, y);
        if (role == Role::Universal) return std::make_unique<VernonRoche>(x, y);
        return nullptr;
    }
};

class NilfgaardFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(Role role, int x, int y) const override {
        if (role == Role::Melee) return std::make_unique<Morteisen>(x, y);
        if (role == Role::Ranged) return std::make_unique<Albrich>(x, y);
        if (role == Role::Universal) return std::make_unique<LethoOfGulet>(x, y);
        return nullptr;
    }
};

class MonsterFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(Role role, int x, int y) const override {
        if (role == Role::Melee) return std::make_unique<Ghoul>(x, y);
        if (role == Role::Ranged) return std::make_unique<Harpy>(x, y);
        if (role == Role::Universal) return std::make_unique<Kayran>(x, y);
        return nullptr;
    }
};

class ScoiataelFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(Role role, int x, int y) const override {
        if (role == Role::Melee) return std::make_unique<Filavandrel>(x, y);
        if (role == Role::Ranged) return std::make_unique<Eithne>(x, y);
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