#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

struct UnitEvent {
    enum class Type { Created, Damaged, Destroyed, ResourcesCollected };
    Type eventType;
    int unitId;
    std::string unitName;
    int value;
};

class IObserver;

class IObservable {
protected:
    std::vector<IObserver*> observers;
public:
    virtual ~IObservable() = default;
    void subscribe(IObserver* obs) {
        if (obs && std::find(observers.begin(), observers.end(), obs) == observers.end())
            observers.push_back(obs);
    }
    void unsubscribe(IObserver* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }
    void notify(const UnitEvent& event);
};

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onUnitEvent(const UnitEvent& event) = 0;
};