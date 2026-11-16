#include <iostream>
#include "GameController.h"
#include "Terrain.h"
#include "NeutralObject.h"

void separator() { std::cout << "\n--------------------------------------------------\n\n"; }

int main() {
    setlocale(LC_ALL, "Russian");

    GameController game;
    auto& field = game.getField();
    auto& base = game.getBase();

    NorthFactory northFab;
    NilfgaardFactory nilfFab;
    MonsterFactory monsterFab;
    ScoiataelFactory scoiFab;
    HeroFactory heroFab;

    std::cout << "СЦЕНАРИЙ 1: Создание большой карты и армий\n";

    for (int y = 5; y <= 6; ++y)
        for (int x = 5; x <= 6; ++x)
            field.setTerrain(x, y, new Mountains());

    for (int y = 10; y <= 12; ++y)
        for (int x = 10; x <= 12; ++x)
            field.setTerrain(x, y, new Swamp());

    auto geralt = game.spawnUnit(heroFab, UnitType::Infantry, 1, 1);
    auto yennefer = game.spawnUnit(heroFab, UnitType::Mage, 2, 1);
    auto ciri = game.spawnUnit(heroFab, UnitType::Archer, 3, 1);

    auto roche = game.spawnUnit(northFab, UnitType::Infantry, 4, 1);
    auto harpy = game.spawnUnit(monsterFab, UnitType::Flying, 4, 4);

    auto letho = game.spawnUnit(nilfFab, UnitType::Archer, 8, 8);
    auto iorveth = game.spawnUnit(scoiFab, UnitType::Archer, 9, 9);

    field.addUnit(std::move(geralt), 1, 1);
    field.addUnit(std::move(yennefer), 2, 1);
    field.addUnit(std::move(ciri), 3, 1);
    field.addUnit(std::move(roche), 4, 1);
    field.addUnit(std::move(harpy), 4, 4);
    field.addUnit(std::move(letho), 8, 8);
    field.addUnit(std::move(iorveth), 9, 9);

    field.setNeutralObject(1, 2, std::make_unique<TreasureChest>());
    field.setNeutralObject(2, 2, std::make_unique<Altar>());
    field.setNeutralObject(3, 2, std::make_unique<Trap>());
    field.setNeutralObject(4, 2, std::make_unique<EnergySource>());

    std::cout << "Игровое поле 15x15 (в центре горы (^), внизу болото (~)):\n";
    field.printField();
    separator();

    std::cout << "СЦЕНАРИЙ 2: Ландшафт и работа Прокси\n";

    std::cout << "Пытаемся переместить Вернона Роше (Пехота) в горы (5,5):\n";
    try {
        field.moveUnit(4, 1, 5, 5);
    }
    catch (const std::exception& e) {
        std::cout << ">>> Ошибка: " << e.what() << "\n";
    }
    std::cout << "\n";

    std::cout << "Пытаемся переместить Гарпию (Летающая) в горы (5,5):\n";
    try {
        field.moveUnit(4, 4, 5, 5);
        std::cout << ">>> Успех! Гарпия перелетела через горы.\n";
    }
    catch (const std::exception& e) {
        std::cout << ">>> Ошибка: " << e.what() << "\n";
    }
    std::cout << "\n";

    std::cout << "Пытаемся переместить Геральта в болото (10,10):\n";
    field.moveUnit(1, 1, 10, 10);
    std::cout << ">>> Успех! Геральт вошел в болото (скорость снижена).\n";

    field.printField();
    separator();

    std::cout << "СЦЕНАРИЙ 3: Нейтральные объекты\n";

    if (auto* chest = dynamic_cast<TreasureChest*>(field.getNeutralObject(1, 2))) {
        std::cout << "Йеннифэр открывает сундук (c):\n";
        *field.getUnit(2, 1) + *chest;
        field.removeNeutralObject(1, 2);
        std::cout << "Сундук исчез.\n\n";
        base.printStatus();
    }

    if (auto* trap = dynamic_cast<Trap*>(field.getNeutralObject(3, 2))) {
        std::cout << "Цири наступает на ловушку (t):\n";
        *field.getUnit(3, 1) - *trap;
        field.removeNeutralObject(3, 2);
        std::cout << "Ловушка исчезла.\n\n";
    }

    auto* altar = dynamic_cast<Altar*>(field.getNeutralObject(2, 2));
    if (altar) {
        std::cout << "Йеннифер (Маг) у Алтаря:\n";
        *field.getUnit(2, 1)** altar;
        std::cout << "Цири (Стрелок) у Алтаря:\n";
        *field.getUnit(3, 1)** altar;
        field.removeNeutralObject(2, 2);
        std::cout << "Алтарь исчез.\n\n";
    }

    if (auto* source = dynamic_cast<EnergySource*>(field.getNeutralObject(4, 2))) {
        std::cout << "Йеннифэр взаимодействует с источником (e):\n";
        *field.getUnit(2, 1) / *source;
        field.removeNeutralObject(4, 2);
        std::cout << "Источник иссяк.\n\n";
    }

    separator();

    std::cout << "СЦЕНАРИЙ 4: Смерть и Наблюдатель\n";

    std::cout << "Лето (Нильфгаард) атакует Иорвета (Скоя'таэли):\n";
    auto lethoPtr = field.getUnit(8, 8);
    auto iorvethPtr = field.getUnit(9, 9);

    if (lethoPtr && iorvethPtr) {
        lethoPtr->attackUnit(*iorvethPtr);
        std::cout << "Иорвет получает смертельный урон...\n";
        iorvethPtr->takeDamage(1000);
    }

    field.removeDeadUnits();

    std::cout << "\nИтоговое поле (Иорвет погиб, объекты использованы):\n";
    field.printField();
    base.printStatus();

    return 0;
}