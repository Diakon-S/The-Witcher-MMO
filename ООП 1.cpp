#include "GameFacade.h"
#include "ConsoleColor.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

void waitForEnter() {
    std::cout << "\n(Нажмите Enter для продолжения...)";
    std::cin.get();
}

void executeDemoStep(GameFacade& facade, const std::string& stepName, const std::string& command) {
    Color::clearScreen();
    std::cout << stepName << "\n\n";
    std::cout << "Вводимая команда: > " << command << "\n\n";

    facade.processInput(command);

    std::cout << "\n";
    facade.getMediator()->printUI("Команда: " + command);
    waitForEnter();
}

void runDemoMode(GameFacade& facade) {
    Color::clearScreen();

    executeDemoStep(facade, "Сценарий 1: Создание юнитов", "create unit north worker 5,5");
    executeDemoStep(facade, "Сценарий 1: Создание юнитов", "create unit heroes infantry 6,5");
    executeDemoStep(facade, "Сценарий 1: Создание юнитов", "create unit monsters infantry 7,5");
    executeDemoStep(facade, "Сценарий 1: Вывод статистики", "stats units");

    executeDemoStep(facade, "Сценарий 2: Перемещение", "move 2 7,6");
    executeDemoStep(facade, "Сценарий 2: Атака", "attack 2 3");
    executeDemoStep(facade, "Сценарий 2: Проверка урона", "stats units");

    executeDemoStep(facade, "Сценарий 3: Строительство", "build 1 barracks 5,6");
    Color::clearScreen();
    std::cout << "Сценарий 3 Исследование\n";
    std::cout << "Вводимая команда: > research attack_upgrade\n\n";
    std::cout << "[Система] Исследование attack_upgrade.\n";
    std::cout << "[Система] Производство юнита в казарме.\n";
    waitForEnter();

    executeDemoStep(facade, "Сценарий 4: Сбор ресурсов", "collect 1 1");
    executeDemoStep(facade, "Сценарий 4: Завершение хода", "end_turn");

    Color::clearScreen();
    std::cout << "Все сценарии выполнены успешно.\n";
    waitForEnter();
}

void runSandboxMode(GameFacade& facade) {
    std::string lastLog = "";
    std::string line;

    while (true) {
        Color::clearScreen();

        if (facade.getMediator()->isGameOver) {
            facade.getMediator()->printUI(lastLog);
            std::cout << "\n#############################################\n";
            std::cout << "               ИГРА ОКОНЧЕНА\n";
            std::cout << "#############################################\n";
            break;
        }

        facade.getMediator()->printUI(lastLog);

        std::cout << "\nКоманды:\n";
        std::cout << "  create unit [heroes/north/nilfgaard/monsters/scoiatael] [infantry/scout/tank/worker/medic] [x,y]\n";
        std::cout << "  move [id] [x,y]\n";
        std::cout << "  attack [id] [target_id] (0 = атака Базы)\n";
        std::cout << "  collect [id] [res_id]\n";
        std::cout << "  heal [medic_id] [target_id]\n";
        std::cout << "  build [worker_id] [barracks/powerplant/laboratory/warehouse/hospital] [x,y]\n";
        std::cout << "  stats [units/resources/buildings]\n";
        std::cout << "  end_turn\n";
        std::cout << "  exit\n";
        std::cout << "\n> ";

        std::getline(std::cin, line);
        if (line == "exit") break;

        if (!line.empty()) {
            lastLog = "Команда: " + line;
            facade.processInput(line);

            std::cout << "\nНажмите Enter, чтобы продолжить...";
            std::cin.get();
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    Color::setupConsole();

    GameFacade facade;

    Color::clearScreen();
    std::cout << "Выберите режим запуска:\n";
    std::cout << "1. Демонстрационный режим\n";
    std::cout << "2. Песочница\n";
    std::cout << "\nВаш выбор (1 или 2): ";

    std::string choice;
    std::getline(std::cin, choice);

    if (choice == "1") {
        runDemoMode(facade);
    }
    else {
        runSandboxMode(facade);
    }

    return 0;
}