#pragma once
#include <iostream> 
#include <algorithm> 
#include <sstream>
#include <memory>
#include <vector>
#include <cmath>
#include "Base.h"
#include "GameField.h"
#include "UnitFactory.h"
#include "Systems.h"

class GameMediator {
private:
    std::shared_ptr<Base> base;
    std::shared_ptr<GameField> field;
    std::shared_ptr<UnitManager> unitMgr;
    std::shared_ptr<BuildingManager> buildingMgr;
    std::shared_ptr<ResourceSystem> resSys;
    std::shared_ptr<CombatSystem> combSys;

    HeroFactory heroFab;
    NorthFactory northFab;
    NilfgaardFactory nilfFab;
    MonsterFactory monsterFab;
    ScoiataelFactory scoiFab;

public:
    int turnCount = 1;
    bool isGameOver = false;

    GameMediator() {
        base = std::make_shared<Base>(1000, 20, 5);
        field = std::make_shared<GameField>(40, 30);
        unitMgr = std::make_shared<UnitManager>();
        buildingMgr = std::make_shared<BuildingManager>();
        resSys = std::make_shared<ResourceSystem>();
        combSys = std::make_shared<CombatSystem>();

        generateMap();
    }

    void generateMap() {
        for (int y = 0; y < 30; ++y) {
            for (int x = 0; x < 40; ++x) {
                if (x >= 10 && x <= 20 && y >= 5 && y <= 15) field->setTerrain(x, y, new Mountains());
                else if (x >= 25 && x <= 38 && y >= 18 && y <= 28) field->setTerrain(x, y, new Swamp());
                else if (x >= 3 && x <= 12 && y >= 20 && y <= 27) field->setTerrain(x, y, new Forest());
            }
        }
        field->setNeutralObject(15, 15, std::make_unique<TreasureChest>());
        field->setNeutralObject(35, 5, std::make_unique<Altar>());
        field->setNeutralObject(20, 25, std::make_unique<Trap>());
    }

    void createUnit(Faction f, UnitType type, int x, int y) {
        if (unitMgr->allUnits.size() >= base->getMaxUnits()) { std::cout << "Достигнут лимит юнитов.\n"; return; }

        std::unique_ptr<Unit> u = nullptr;
        if (f == Faction::Heroes) u = heroFab.createUnit(type, unitMgr->nextUnitId, x, y);
        else if (f == Faction::North) u = northFab.createUnit(type, unitMgr->nextUnitId, x, y);
        else if (f == Faction::Nilfgaard) u = nilfFab.createUnit(type, unitMgr->nextUnitId, x, y);
        else if (f == Faction::Monsters) u = monsterFab.createUnit(type, unitMgr->nextUnitId, x, y);
        else if (f == Faction::Scoiatael) u = scoiFab.createUnit(type, unitMgr->nextUnitId, x, y);

        if (!u) { std::cout << "Эта фракция не умеет создавать такой тип юнита!\n"; return; }

        std::shared_ptr<Unit> sharedUnit = std::move(u);
        try {
            field->addUnit(sharedUnit, x, y);
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка размещения: " << e.what() << "\n";
            return;
        }

        unitMgr->nextUnitId++;
        sharedUnit->subscribe(base.get());
        sharedUnit->notify({ UnitEvent::Type::Created, sharedUnit->getId(), sharedUnit->getName(), 0 });
        unitMgr->allUnits.push_back(sharedUnit);
    }

    void moveUnit(int id, int x, int y) {
        auto u = unitMgr->getUnitById(id);
        if (!u) { std::cout << "Юнит не найден.\n"; return; }
        if (u->currentAP <= 0) { std::cout << "У юнита нет ОД на движение!\n"; return; }

        int dist = std::max(std::abs(u->getX() - x), std::abs(u->getY() - y));
        if (dist > 1) { std::cout << "Можно двигаться только на 1 клетку!\n"; return; }

        try {
            field->moveUnit(u->getX(), u->getY(), x, y);
            u->spendAP(1);
            std::cout << "Юнит " << u->getName() << " переместился в " << x << "," << y << ". (Осталось ОД: " << u->currentAP << ")\n";
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка движения: " << e.what() << "\n";
        }
    }

    void attack(int attackerId, int targetId) {
        auto a = unitMgr->getUnitById(attackerId);
        if (!a) { std::cout << "Атакующий не найден.\n"; return; }
        if (a->currentAP <= 0) { std::cout << "Нет ОД для атаки.\n"; return; }

        if (targetId == 0) {
            int dist = std::max(std::abs(a->getX() - field->baseX), std::abs(a->getY() - field->baseY));
            if (dist > 1 && a->getType() != UnitType::Scout) { std::cout << "База слишком далеко.\n"; return; }

            std::cout << "Бой: " << a->getName() << " атакует БАЗУ!\n";
            base->takeDamage(a->getAttack());
            a->spendAP(1);

            if (base->isDestroyed()) {
                std::cout << "\n=============================================\n";
                std::cout << "ВНИМАНИЕ! БАЗА УНИЧТОЖЕНА! ИГРА ОКОНЧЕНА.\n";
                std::cout << "=============================================\n";
                isGameOver = true;
            }
            return;
        }

        auto t = unitMgr->getUnitById(targetId);
        if (a && t) {
            int dist = std::max(std::abs(a->getX() - t->getX()), std::abs(a->getY() - t->getY()));
            if (dist > 1 && a->getType() != UnitType::Scout) { std::cout << "Цель слишком далеко.\n"; return; }

            std::cout << "Бой: " << a->getName() << " атакует " << t->getName() << "!\n";
            combSys->resolveCombat(*a, *t);
            a->spendAP(1);
            if (t->isDead()) {
                int tx = t->getX(), ty = t->getY();
                field->removeUnit(tx, ty);
                unitMgr->allUnits.erase(
                    std::remove_if(unitMgr->allUnits.begin(), unitMgr->allUnits.end(),
                        [targetId](const std::shared_ptr<Unit>& u) { return u->getId() == targetId; }),
                    unitMgr->allUnits.end()
                );
            }
        }
        else std::cout << "Неверные цели.\n";
    }

    void collectResource(int unitId, int resId) {
        auto u = unitMgr->getUnitById(unitId);
        if (!u || u->getType() != UnitType::Worker) { std::cout << "Только рабочие собирают ресурсы.\n"; return; }
        auto r = unitMgr->getResourceById(resId);
        if (r && r->amount > 0) {
            int amount = std::min(50, r->amount);
            r->amount -= amount;
            resSys->addResources(r->type, amount);
            u->notify({ UnitEvent::Type::ResourcesCollected, u->getId(), u->getName(), amount });
        }
        else std::cout << "Ресурс пуст или не найден.\n";
    }

    void healUnit(int medicId, int targetId) {
        auto m = unitMgr->getUnitById(medicId);
        auto t = unitMgr->getUnitById(targetId);
        if (m && t && m->getType() == UnitType::Medic) {
            t->heal(50);
            std::cout << "Медик " << m->getName() << " вылечил " << t->getName() << ". (HP: " << t->getHp() << ")\n";
        }
        else std::cout << "Лечение не удалось.\n";
    }

    void buildBuilding(int workerId, BuildingType type, int x, int y) {
        auto u = unitMgr->getUnitById(workerId);
        if (!u || u->getType() != UnitType::Worker) { std::cout << "Только рабочие строят.\n"; return; }
        if (u->currentAP <= 0) { std::cout << "Нет ОД.\n"; return; }
        if (std::abs(u->getX() - x) > 1 || std::abs(u->getY() - y) > 1) { std::cout << "Слишком далеко.\n"; return; }
        if (!resSys->spendResources(ResourceType::Wood, 100)) { std::cout << "Мало дерева.\n"; return; }

        auto b = std::make_shared<Building>(buildingMgr->nextBuildingId++, type, x, y);
        buildingMgr->buildings.push_back(b);
        field->addBuilding(b);
        u->spendAP(1);
        std::cout << "Построено здание: " << b->symbol << " на " << x << "," << y << "\n";
    }

    void endTurn() {
        for (auto& u : unitMgr->allUnits) u->resetAP();
        turnCount++;
        std::cout << "--- Ход " << turnCount << " начался. Все ОД восстановлены. ---\n";
    }

    void printUI(const std::string& lastAction) {
        field->printField();
        std::cout << "\n";
        std::cout << "Ход: " << turnCount << " | ";
        base->printStatus();
        std::cout << "\n";
        if (!lastAction.empty()) std::cout << "Лог: " << lastAction << "\n";
    }

    void getStats(const std::string& arg) {
        if (arg == "units") {
            std::cout << "--- Юниты ---\n";
            for (auto& u : unitMgr->allUnits) {
                std::cout << "ID:" << u->getId() << " " << u->getName() << " HP:" << u->getHp() << " ОД:" << u->currentAP << "/" << u->maxAP << "\n";
            }
        }
        else if (arg == "resources") resSys->printStats();
        else if (arg == "buildings") {
            std::cout << "--- Здания ---\n";
            for (auto& b : buildingMgr->buildings) std::cout << "ID:" << b->id << " Символ:" << b->symbol << "\n";
        }
        else { resSys->printStats(); base->printStatus(); std::cout << "\n"; }
    }
};