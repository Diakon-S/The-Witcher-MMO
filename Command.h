#pragma once
#include "GameMediator.h"

class Command {
protected:
    std::shared_ptr<GameMediator> mediator;
public:
    Command(std::shared_ptr<GameMediator> m) : mediator(m) {}
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class CreateUnitCommand : public Command {
    Faction faction; UnitType type; int x, y;
public:
    CreateUnitCommand(std::shared_ptr<GameMediator> m, Faction f, UnitType t, int x, int y) : Command(m), faction(f), type(t), x(x), y(y) {}
    void execute() override { mediator->createUnit(faction, type, x, y); }
};
class MoveUnitCommand : public Command {
    int id, x, y;
public:
    MoveUnitCommand(std::shared_ptr<GameMediator> m, int id, int x, int y) : Command(m), id(id), x(x), y(y) {}
    void execute() override { mediator->moveUnit(id, x, y); }
};
class AttackCommand : public Command {
    int attackerId, targetId;
public:
    AttackCommand(std::shared_ptr<GameMediator> m, int aId, int tId) : Command(m), attackerId(aId), targetId(tId) {}
    void execute() override { mediator->attack(attackerId, targetId); }
};
class CollectResourceCommand : public Command {
    int unitId, resId;
public:
    CollectResourceCommand(std::shared_ptr<GameMediator> m, int uId, int rId) : Command(m), unitId(uId), resId(rId) {}
    void execute() override { mediator->collectResource(unitId, resId); }
};
class HealCommand : public Command {
    int medicId, targetId;
public:
    HealCommand(std::shared_ptr<GameMediator> m, int mId, int tId) : Command(m), medicId(mId), targetId(tId) {}
    void execute() override { mediator->healUnit(medicId, targetId); }
};
class BuildBuildingCommand : public Command {
    int workerId; BuildingType type; int x, y;
public:
    BuildBuildingCommand(std::shared_ptr<GameMediator> m, int wId, BuildingType t, int x, int y) : Command(m), workerId(wId), type(t), x(x), y(y) {}
    void execute() override { mediator->buildBuilding(workerId, type, x, y); }
};
class StatsCommand : public Command {
    std::string arg;
public:
    StatsCommand(std::shared_ptr<GameMediator> m, std::string a) : Command(m), arg(a) {}
    void execute() override { mediator->getStats(arg); }
};
class EndTurnCommand : public Command {
public:
    EndTurnCommand(std::shared_ptr<GameMediator> m) : Command(m) {}
    void execute() override { mediator->endTurn(); }
};