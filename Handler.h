#pragma once
#include "Command.h"
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

inline std::vector<std::string> tokenize(const std::string& str) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (ss >> token) tokens.push_back(token);
    return tokens;
}

inline bool parsePos(const std::string& str1, const std::string& str2, int& x, int& y) {
    std::string cleanStr = str1;
    if (!str2.empty()) cleanStr += "," + str2;
    cleanStr.erase(std::remove(cleanStr.begin(), cleanStr.end(), ' '), cleanStr.end());
    size_t comma = cleanStr.find(',');
    if (comma != std::string::npos) {
        try { x = std::stoi(cleanStr.substr(0, comma)); y = std::stoi(cleanStr.substr(comma + 1)); return true; }
        catch (...) { return false; }
    }
    return false;
}
inline bool parsePos(const std::string& str, int& x, int& y) { return parsePos(str, "", x, y); }

class GameFacade;
class Handler {
protected:
    std::shared_ptr<Handler> next_;
    GameFacade* facade_;
public:
    Handler(GameFacade* fac) : facade_(fac) {}
    void setNext(std::shared_ptr<Handler> next) { next_ = next; }
    virtual bool handle(const std::string& cmd) = 0;
    virtual ~Handler() = default;
};

class CreateHandler : public Handler { public: CreateHandler(GameFacade* f) : Handler(f) {} bool handle(const std::string& cmd) override; };
class MoveHandler : public Handler { public: MoveHandler(GameFacade* f) : Handler(f) {} bool handle(const std::string& cmd) override; };
class AttackHandler : public Handler { public: AttackHandler(GameFacade* f) : Handler(f) {} bool handle(const std::string& cmd) override; };
class CollectHandler : public Handler { public: CollectHandler(GameFacade* f) : Handler(f) {} bool handle(const std::string& cmd) override; };
class HealHandler : public Handler { public: HealHandler(GameFacade* f) : Handler(f) {} bool handle(const std::string& cmd) override; };
class BuildHandler : public Handler { public: BuildHandler(GameFacade* f) : Handler(f) {} bool handle(const std::string& cmd) override; };
class StatsHandler : public Handler { public: StatsHandler(GameFacade* f) : Handler(f) {} bool handle(const std::string& cmd) override; };
class EndTurnHandler : public Handler { public: EndTurnHandler(GameFacade* f) : Handler(f) {} bool handle(const std::string& cmd) override; };