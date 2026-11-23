#pragma once
#include "Unit.h"

// ================= ГЕРОИ =================
class Geralt : public Unit { public: Geralt(int id, int x, int y) : Unit(id, "Геральт", Faction::Heroes, UnitType::Infantry, x, y, 200, 40, 50, 'W') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<Geralt>(*this); } };
class Ciri : public Unit { public: Ciri(int id, int x, int y) : Unit(id, "Цири", Faction::Heroes, UnitType::Scout, x, y, 120, 10, 45, 'C') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<Ciri>(*this); } };
class Yennefer : public Unit { public: Yennefer(int id, int x, int y) : Unit(id, "Йеннифэр", Faction::Heroes, UnitType::Medic, x, y, 100, 10, 15, 'Y') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<Yennefer>(*this); } };

// ================= СЕВЕР =================
class VernonRoche : public Unit { public: VernonRoche(int id, int x, int y) : Unit(id, "Вернон Роше", Faction::North, UnitType::Infantry, x, y, 150, 30, 35, 'V') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<VernonRoche>(*this); } };
class RedanianKnight : public Unit { public: RedanianKnight(int id, int x, int y) : Unit(id, "Реданский Рыцарь", Faction::North, UnitType::Tank, x, y, 250, 50, 20, 'K') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<RedanianKnight>(*this); } };
class DwarfMiner : public Unit { public: DwarfMiner(int id, int x, int y) : Unit(id, "Краснолюд-Шахтер", Faction::North, UnitType::Worker, x, y, 80, 5, 5, 'D') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<DwarfMiner>(*this); } };

// ================= НИЛЬФГААРД =================
class Morteisen : public Unit { public: Morteisen(int id, int x, int y) : Unit(id, "Мортейсен", Faction::Nilfgaard, UnitType::Infantry, x, y, 130, 35, 28, 'M') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<Morteisen>(*this); } };
class LethoOfGulet : public Unit { public: LethoOfGulet(int id, int x, int y) : Unit(id, "Лето из Гулеты", Faction::Nilfgaard, UnitType::Scout, x, y, 140, 20, 35, 'L') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<LethoOfGulet>(*this); } };
class Albrich : public Unit { public: Albrich(int id, int x, int y) : Unit(id, "Альбрых", Faction::Nilfgaard, UnitType::Medic, x, y, 90, 10, 40, 'A') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<Albrich>(*this); } };

// ================= ЧУДОВИЩА =================
class Ghoul : public Unit { public: Ghoul(int id, int x, int y) : Unit(id, "Упырь", Faction::Monsters, UnitType::Infantry, x, y, 70, 5, 15, 'G') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<Ghoul>(*this); } };
class Harpy : public Unit { public: Harpy(int id, int x, int y) : Unit(id, "Гарпия", Faction::Monsters, UnitType::Scout, x, y, 60, 0, 25, 'H') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<Harpy>(*this); } };
class Golem : public Unit { public: Golem(int id, int x, int y) : Unit(id, "Голем", Faction::Monsters, UnitType::Tank, x, y, 300, 45, 25, 'O') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<Golem>(*this); } };

// ================= СКОЯ'ТАЭЛИ =================
class Filavandrel : public Unit { public: Filavandrel(int id, int x, int y) : Unit(id, "Филавандрель", Faction::Scoiatael, UnitType::Infantry, x, y, 100, 20, 30, 'F') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<Filavandrel>(*this); } };
class Iorveth : public Unit { public: Iorveth(int id, int x, int y) : Unit(id, "Иорвет", Faction::Scoiatael, UnitType::Scout, x, y, 140, 25, 35, 'I') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<Iorveth>(*this); } };
class Eithne : public Unit { public: Eithne(int id, int x, int y) : Unit(id, "Эитнэ", Faction::Scoiatael, UnitType::Medic, x, y, 85, 15, 45, 'E') {} std::unique_ptr<Unit> clone() const override { return std::make_unique<Eithne>(*this); } };