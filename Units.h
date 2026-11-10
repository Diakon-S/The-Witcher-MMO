#pragma once
#include "Unit.h"

class NorthUnit : public Unit {
public:
    using Unit::Unit;
    Faction getFaction() const override { return Faction::North; }
};

class NilfgaardUnit : public Unit {
public:
    using Unit::Unit;
    Faction getFaction() const override { return Faction::Nilfgaard; }
};

class MonsterUnit : public Unit {
public:
    using Unit::Unit;
    Faction getFaction() const override { return Faction::Monsters; }
};

class ScoiataelUnit : public Unit {
public:
    using Unit::Unit;
    Faction getFaction() const override { return Faction::Scoiatael; }
};

class HeroUnit : public Unit {
public:
    using Unit::Unit;
    Faction getFaction() const override { return Faction::Heroes; }
};

// Королевства Севера

class PrinceStennis : public NorthUnit {
public:
    PrinceStennis(int x, int y) : NorthUnit("Принц Стеннис", x, y, 120, 30, 25, 'S') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<PrinceStennis>(*this); }
    Role getRole() const override { return Role::Melee; }
};

class Dethmold : public NorthUnit {
public:
    Dethmold(int x, int y) : NorthUnit("Детмольд", x, y, 80, 15, 35, 'D') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Dethmold>(*this); }
    Role getRole() const override { return Role::Ranged; }
};

class VernonRoche : public NorthUnit {
public:
    VernonRoche(int x, int y) : NorthUnit("Вернон Роше", x, y, 150, 25, 30, 'V') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<VernonRoche>(*this); }
    Role getRole() const override { return Role::Universal; }
};

// Нильфгаард

class Morteisen : public NilfgaardUnit {
public:
    Morteisen(int x, int y) : NilfgaardUnit("Мортейсен", x, y, 130, 35, 28, 'M') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Morteisen>(*this); }
    Role getRole() const override { return Role::Melee; }
};

class Albrich : public NilfgaardUnit {
public:
    Albrich(int x, int y) : NilfgaardUnit("Альбрых", x, y, 90, 10, 40, 'A') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Albrich>(*this); }
    Role getRole() const override { return Role::Ranged; }
};

class LethoOfGulet : public NilfgaardUnit {
public:
    LethoOfGulet(int x, int y) : NilfgaardUnit("Лето из Гулеты", x, y, 140, 20, 35, 'L') {} 
    std::unique_ptr<Unit> clone() const override { return std::make_unique<LethoOfGulet>(*this); }
    Role getRole() const override { return Role::Universal; }
};

// Чудовища

class Ghoul : public MonsterUnit {
public:
    Ghoul(int x, int y) : MonsterUnit("Упырь", x, y, 70, 5, 15, 'G') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Ghoul>(*this); }
    Role getRole() const override { return Role::Melee; }
};

class Harpy : public MonsterUnit {
public:
    Harpy(int x, int y) : MonsterUnit("Гарпия", x, y, 60, 0, 25, 'H') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Harpy>(*this); }
    Role getRole() const override { return Role::Ranged; }
};

class Kayran : public MonsterUnit {
public:
    Kayran(int x, int y) : MonsterUnit("Кейран", x, y, 180, 15, 40, 'K') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Kayran>(*this); }
    Role getRole() const override { return Role::Universal; }
};

// Скоя'таэли

class Filavandrel : public ScoiataelUnit {
public:
    Filavandrel(int x, int y) : ScoiataelUnit("Филавандрель", x, y, 100, 20, 30, 'F') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Filavandrel>(*this); }
    Role getRole() const override { return Role::Melee; }
};

class Eithne : public ScoiataelUnit {
public:
    Eithne(int x, int y) : ScoiataelUnit("Эитнэ", x, y, 85, 15, 45, 'E') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Eithne>(*this); }
    Role getRole() const override { return Role::Ranged; }
};

class Iorveth : public ScoiataelUnit {
public:
    Iorveth(int x, int y) : ScoiataelUnit("Иорвет", x, y, 140, 25, 35, 'I') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Iorveth>(*this); }
    Role getRole() const override { return Role::Universal; }
};

// Герои

class Geralt : public HeroUnit {
public:
    Geralt(int x, int y) : HeroUnit("Геральт из Ривии", x, y, 200, 40, 50, 'W') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Geralt>(*this); }
    Role getRole() const override { return Role::Melee; }
};

class Yennefer : public HeroUnit {
public:
    Yennefer(int x, int y) : HeroUnit("Йеннифэр", x, y, 120, 10, 60, 'Y') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Yennefer>(*this); }
    Role getRole() const override { return Role::Ranged; }
};

class Ciri : public HeroUnit {
public:
    Ciri(int x, int y) : HeroUnit("Цири", x, y, 160, 30, 45, 'C') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Ciri>(*this); }
    Role getRole() const override { return Role::Universal; }
};