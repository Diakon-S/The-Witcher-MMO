#include <iostream>
#include "GameField.h"
#include "UnitsFactory.h"

void separator() { std::cout << "\n--------------------------------------------------\n\n"; }

int main() {
    setlocale(LC_ALL, "Russian");

    NorthFactory northFab;
    NilfgaardFactory nilfFab;
    MonsterFactory monsterFab;
    ScoiataelFactory scoiFab;
    HeroFactory heroFab;


    std::cout << "СЦЕНАРИЙ 1: Создание поля и заполнение через фабрики\n";

    GameField field(10, 10, 20);

    field.addUnit(heroFab.createUnit(Role::Melee, 1, 1), 1, 1);
    field.addUnit(heroFab.createUnit(Role::Ranged, 2, 1), 2, 1);
    field.addUnit(northFab.createUnit(Role::Melee, 7, 7), 7, 7);
    field.addUnit(nilfFab.createUnit(Role::Ranged, 8, 8), 8, 8);
    field.addUnit(monsterFab.createUnit(Role::Universal, 4, 4), 4, 4);
    field.addUnit(scoiFab.createUnit(Role::Ranged, 5, 5), 5, 5);

    field.printField();
    separator();

    std::cout << "СЦЕНАРИЙ 2: Статус юнитов\n";

    for (auto it = field.begin(); it != field.end(); ++it) {
        (*it)->printStats();
    }
    separator();

    std::cout << "СЦЕНАРИЙ 3: Геноцид (нанесение массового урона)\n";

    std::cout << "Наносим 150 урона всем юнитам...\n\n";
    for (auto it = field.begin(); it != field.end(); ++it) {
        (*it)->takeDamage(150);
    }

    field.removeDeadUnits();

    std::cout << "\nПоле после нанесения урона:\n";
    field.printField();
    std::cout << "Выжили сильнейшие.\n";
    separator();

    std::cout << "СЦЕНАРИЙ 4: Демонстрация глубокого копирования\n";

    GameField copyField = field;
    std::cout << "Создана копия поля. Двигаем Геральта в КОПИИ с (1,1) на (3,3)...\n";
    copyField.moveUnit(1, 1, 3, 3);

    std::cout << "\nОРИГИНАЛ (Геральт остался на 1,1):\n";
    field.printField();

    std::cout << "КОПИЯ (Геральт переместился на 3,3):\n";
    copyField.printField();

    std::cout << "Изменения в копии не затронули оригинал.\n";

    return 0;
}