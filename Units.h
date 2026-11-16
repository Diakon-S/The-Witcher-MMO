#pragma once
#include "Unit.h"

class Infantry : public Unit { public: using Unit::Unit; };
class Archer : public Unit { public: using Unit::Unit; };
class Mage : public Unit { public: using Unit::Unit; };
class FlyingUnit : public Unit { public: using Unit::Unit; };

// Королевства Севера
class VernonRoche : public Infantry {
public:
    VernonRoche(int id, int x, int y) : Infantry(id, "Вернон Роше", Faction::North, UnitType::Infantry, x, y, 150, 25, 30, 'V') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<VernonRoche>(*this); }
};
class PrinceStennis : public Archer {
public:
    PrinceStennis(int id, int x, int y) : Archer(id, "Принц Стеннис", Faction::North, UnitType::Archer, x, y, 120, 30, 25, 'S') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<PrinceStennis>(*this); }
};
class Dethmold : public Mage {
public:
    Dethmold(int id, int x, int y) : Mage(id, "Детмольд", Faction::North, UnitType::Mage, x, y, 80, 15, 35, 'D') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Dethmold>(*this); }
};

// Нильфгаард
class Morteisen : public Infantry {
public:
    Morteisen(int id, int x, int y) : Infantry(id, "Мортейсен", Faction::Nilfgaard, UnitType::Infantry, x, y, 130, 35, 28, 'M') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Morteisen>(*this); }
};
class LethoOfGulet : public Archer {
public:
    LethoOfGulet(int id, int x, int y) : Archer(id, "Лето из Гулеты", Faction::Nilfgaard, UnitType::Archer, x, y, 140, 20, 35, 'L') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<LethoOfGulet>(*this); }
};
class Albrich : public Mage {
public:
    Albrich(int id, int x, int y) : Mage(id, "Альбрых", Faction::Nilfgaard, UnitType::Mage, x, y, 90, 10, 40, 'A') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Albrich>(*this); }
};

// Чудовища
class Ghoul : public Infantry {
public:
    Ghoul(int id, int x, int y) : Infantry(id, "Упырь", Faction::Monsters, UnitType::Infantry, x, y, 70, 5, 15, 'G') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Ghoul>(*this); }
};
class Kayran : public Archer {
public:
    Kayran(int id, int x, int y) : Archer(id, "Кейран", Faction::Monsters, UnitType::Archer, x, y, 180, 15, 40, 'K') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Kayran>(*this); }
};
class Harpy : public FlyingUnit {
public:
    Harpy(int id, int x, int y) : FlyingUnit(id, "Гарпия", Faction::Monsters, UnitType::Flying, x, y, 60, 0, 25, 'H') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Harpy>(*this); }
};

// Скоя'таэли
class Filavandrel : public Infantry {
public:
    Filavandrel(int id, int x, int y) : Infantry(id, "Филавандрель", Faction::Scoiatael, UnitType::Infantry, x, y, 100, 20, 30, 'F') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Filavandrel>(*this); }
};
class Iorveth : public Archer {
public:
    Iorveth(int id, int x, int y) : Archer(id, "Иорвет", Faction::Scoiatael, UnitType::Archer, x, y, 140, 25, 35, 'I') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Iorveth>(*this); }
};
class Eithne : public Mage {
public:
    Eithne(int id, int x, int y) : Mage(id, "Эитнэ", Faction::Scoiatael, UnitType::Mage, x, y, 85, 15, 45, 'E') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Eithne>(*this); }
};

// Герои
class Geralt : public Infantry {
public:
    Geralt(int id, int x, int y) : Infantry(id, "Геральт из Ривии", Faction::Heroes, UnitType::Infantry, x, y, 200, 40, 50, 'W') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Geralt>(*this); }
};
class Ciri : public Archer {
public:
    Ciri(int id, int x, int y) : Archer(id, "Цири", Faction::Heroes, UnitType::Archer, x, y, 160, 30, 45, 'C') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Ciri>(*this); }
};
class Yennefer : public Mage {
public:
    Yennefer(int id, int x, int y) : Mage(id, "Йеннифэр", Faction::Heroes, UnitType::Mage, x, y, 120, 10, 60, 'Y') {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Yennefer>(*this); }
};