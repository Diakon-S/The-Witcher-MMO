#pragma once
#include "Handler.h"

class GameFacade {
private:
    std::shared_ptr<GameMediator> mediator;
    std::shared_ptr<Handler> handlerChain;
public:
    GameFacade() {
        mediator = std::make_shared<GameMediator>();

        auto create = std::make_shared<CreateHandler>(this);
        auto move = std::make_shared<MoveHandler>(this);
        auto attack = std::make_shared<AttackHandler>(this);
        auto collect = std::make_shared<CollectHandler>(this);
        auto heal = std::make_shared<HealHandler>(this);
        auto build = std::make_shared<BuildHandler>(this);
        auto stats = std::make_shared<StatsHandler>(this);
        auto endturn = std::make_shared<EndTurnHandler>(this);

        create->setNext(move); move->setNext(attack); attack->setNext(collect);
        collect->setNext(heal); heal->setNext(build); build->setNext(stats);
        stats->setNext(endturn);

        handlerChain = create;
    }

    std::shared_ptr<GameMediator> getMediator() { return mediator; }
    void executeCommand(std::shared_ptr<Command> cmd) { cmd->execute(); }
    void processInput(const std::string& input) {
        if (input.empty()) return;
        if (!handlerChain->handle(input)) {
            std::cout << "Неизвестная команда.\n";
        }
    }
};

inline bool CreateHandler::handle(const std::string& cmd) {
    auto t = tokenize(cmd);
    if (t.size() >= 5 && t[0] == "create" && t[1] == "unit") {
        Faction f = Faction::Heroes;
        if (t[2] == "north") f = Faction::North;
        else if (t[2] == "nilfgaard") f = Faction::Nilfgaard;
        else if (t[2] == "monsters") f = Faction::Monsters;
        else if (t[2] == "scoiatael") f = Faction::Scoiatael;

        UnitType ut = UnitType::Infantry;
        if (t[3] == "scout") ut = UnitType::Scout;
        else if (t[3] == "tank") ut = UnitType::Tank;
        else if (t[3] == "worker") ut = UnitType::Worker;
        else if (t[3] == "medic") ut = UnitType::Medic;

        int x, y;
        if (t.size() == 5 && parsePos(t[4], "", x, y)) {
            facade_->executeCommand(std::make_shared<CreateUnitCommand>(facade_->getMediator(), f, ut, x, y));
        }
        else if (t.size() == 6 && parsePos(t[4], t[5], x, y)) {
            facade_->executeCommand(std::make_shared<CreateUnitCommand>(facade_->getMediator(), f, ut, x, y));
        }
        else {
            std::cout << "Ошибка: неверный формат координат.\n";
        }
        return true;
    }
    return next_ ? next_->handle(cmd) : false;
}

inline bool MoveHandler::handle(const std::string& cmd) {
    auto t = tokenize(cmd);
    if (t.size() >= 3 && t[0] == "move") {
        try {
            int id = std::stoi(t[1]);
            int x, y;
            if (t.size() == 3 && parsePos(t[2], "", x, y)) {
                facade_->executeCommand(std::make_shared<MoveUnitCommand>(facade_->getMediator(), id, x, y));
            }
            else if (t.size() == 4 && parsePos(t[2], t[3], x, y)) {
                facade_->executeCommand(std::make_shared<MoveUnitCommand>(facade_->getMediator(), id, x, y));
            }
            else { std::cout << "Ошибка: неверный формат координат.\n"; }
        }
        catch (...) { std::cout << "Ошибка: неверный ID.\n"; }
        return true;
    }
    return next_ ? next_->handle(cmd) : false;
}

inline bool AttackHandler::handle(const std::string& cmd) {
    auto t = tokenize(cmd);
    if (t.size() >= 3 && t[0] == "attack") {
        try {
            int id1 = std::stoi(t[1]);
            int id2 = std::stoi(t[2]);
            facade_->executeCommand(std::make_shared<AttackCommand>(facade_->getMediator(), id1, id2));
        }
        catch (...) { std::cout << "Ошибка: неверные ID.\n"; }
        return true;
    }
    return next_ ? next_->handle(cmd) : false;
}

inline bool CollectHandler::handle(const std::string& cmd) {
    auto t = tokenize(cmd);
    if (t.size() >= 3 && t[0] == "collect") {
        try {
            int id1 = std::stoi(t[1]);
            int id2 = std::stoi(t[2]);
            facade_->executeCommand(std::make_shared<CollectResourceCommand>(facade_->getMediator(), id1, id2));
        }
        catch (...) { std::cout << "Ошибка: неверные ID.\n"; }
        return true;
    }
    return next_ ? next_->handle(cmd) : false;
}

inline bool HealHandler::handle(const std::string& cmd) {
    auto t = tokenize(cmd);
    if (t.size() >= 3 && t[0] == "heal") {
        try {
            int id1 = std::stoi(t[1]);
            int id2 = std::stoi(t[2]);
            facade_->executeCommand(std::make_shared<HealCommand>(facade_->getMediator(), id1, id2));
        }
        catch (...) { std::cout << "Ошибка: неверные ID.\n"; }
        return true;
    }
    return next_ ? next_->handle(cmd) : false;
}

inline bool BuildHandler::handle(const std::string& cmd) {
    auto t = tokenize(cmd);
    if (t.size() >= 4 && t[0] == "build") {
        try {
            int wId = std::stoi(t[1]);
            BuildingType bt = BuildingType::Barracks;
            if (t[2] == "powerplant") bt = BuildingType::PowerPlant;
            else if (t[2] == "laboratory") bt = BuildingType::Laboratory;
            else if (t[2] == "warehouse") bt = BuildingType::Warehouse;
            else if (t[2] == "hospital") bt = BuildingType::Hospital;

            int x, y;
            if (t.size() == 4 && parsePos(t[3], "", x, y)) {
                facade_->executeCommand(std::make_shared<BuildBuildingCommand>(facade_->getMediator(), wId, bt, x, y));
            }
            else if (t.size() == 5 && parsePos(t[3], t[4], x, y)) {
                facade_->executeCommand(std::make_shared<BuildBuildingCommand>(facade_->getMediator(), wId, bt, x, y));
            }
            else { std::cout << "Ошибка: неверный формат координат.\n"; }
        }
        catch (...) { std::cout << "Ошибка: неверный ID.\n"; }
        return true;
    }
    return next_ ? next_->handle(cmd) : false;
}

inline bool StatsHandler::handle(const std::string& cmd) {
    auto t = tokenize(cmd);
    if (t.size() >= 1 && t[0] == "stats") {
        std::string arg = t.size() > 1 ? t[1] : "";
        facade_->executeCommand(std::make_shared<StatsCommand>(facade_->getMediator(), arg));
        return true;
    }
    return next_ ? next_->handle(cmd) : false;
}

inline bool EndTurnHandler::handle(const std::string& cmd) {
    auto t = tokenize(cmd);
    if (t.size() == 1 && t[0] == "end_turn") {
        facade_->executeCommand(std::make_shared<EndTurnCommand>(facade_->getMediator()));
        return true;
    }
    return next_ ? next_->handle(cmd) : false;
}