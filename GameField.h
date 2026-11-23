#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Unit.h"
#include "Terrain.h"
#include "NeutralObject.h"
#include "ConsoleColor.h"
#include "Domain.h"

class GameField {
private:
    int width, height;
    std::vector<std::vector<std::shared_ptr<Unit>>> grid;
    std::vector<std::vector<std::unique_ptr<TerrainProxy>>> terrainMap;
    std::vector<std::vector<std::unique_ptr<NeutralObject>>> neutralMap;
    std::vector<std::vector<std::shared_ptr<Building>>> buildingMap;

public:
    int baseX = 2, baseY = 2;

    GameField(int w, int h) : width(w), height(h) {
        grid.resize(height); terrainMap.resize(height); neutralMap.resize(height); buildingMap.resize(height);
        for (int y = 0; y < height; ++y) {
            grid[y].resize(width); terrainMap[y].resize(width); neutralMap[y].resize(width); buildingMap[y].resize(width);
            for (int x = 0; x < width; ++x) terrainMap[y][x] = std::make_unique<TerrainProxy>(new Plains());
        }
    }

    void setTerrain(int x, int y, Terrain* terrain) { if (x >= 0 && x < width && y >= 0 && y < height) terrainMap[y][x] = std::make_unique<TerrainProxy>(terrain); }
    void setNeutralObject(int x, int y, std::unique_ptr<NeutralObject> obj) { if (x >= 0 && x < width && y >= 0 && y < height) neutralMap[y][x] = std::move(obj); }
    void addBuilding(std::shared_ptr<Building> b) { if (b->x >= 0 && b->x < width && b->y >= 0 && b->y < height) buildingMap[b->y][b->x] = b; }

    std::shared_ptr<Unit> getUnit(int x, int y) const { if (x >= 0 && x < width && y >= 0 && y < height) return grid[y][x]; return nullptr; }

    void addUnit(std::shared_ptr<Unit> unit, int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) throw std::out_of_range("Вне поля");
        if (grid[y][x] != nullptr) throw std::runtime_error("Клетка занята");
        if (x == baseX && y == baseY) throw std::runtime_error("Клетка занята Базой");
        unit->move(x, y);
        grid[y][x] = unit;
    }

    void moveUnit(int ox, int oy, int nx, int ny) {
        if (ox < 0 || ox >= width || oy < 0 || oy >= height || nx < 0 || nx >= width || ny < 0 || ny >= height) throw std::out_of_range("Вне поля");
        if (grid[oy][ox] == nullptr) throw std::runtime_error("Начальная клетка пуста");
        if (grid[ny][nx] != nullptr) throw std::runtime_error("Клетка занята юнитом");
        if (buildingMap[ny][nx] != nullptr) throw std::runtime_error("Клетка занята зданием");
        if (nx == baseX && ny == baseY) throw std::runtime_error("Клетка занята Базой");
        if (!terrainMap[ny][nx]->isPassable(grid[oy][ox]->getType())) throw std::runtime_error("Ландшафт непреодолим");

        grid[ny][nx] = grid[oy][ox];
        grid[oy][ox] = nullptr;
        grid[ny][nx]->move(nx, ny);

        if (neutralMap[ny][nx] != nullptr) {
            neutralMap[ny][nx]->interact(*grid[ny][nx]);
            neutralMap[ny][nx].reset();
        }
    }

    void removeUnit(int x, int y) { if (grid[y][x]) grid[y][x].reset(); }

    void printField() const {
        for (int y = 0; y < height; ++y) {
            Color::set(Color::Default);
            std::cout << (y < 10 ? " " : "") << y << " ";
            for (int x = 0; x < width; ++x) {
                if (x == baseX && y == baseY) { Color::set(Color::Cyan); std::cout << "U "; }
                else if (grid[y][x]) { Color::set(Color::Default); std::cout << grid[y][x]->getSymbol() << " "; }
                else if (buildingMap[y][x]) { Color::set(Color::Yellow); std::cout << buildingMap[y][x]->symbol << " "; }
                else if (neutralMap[y][x]) { Color::set(neutralMap[y][x]->getColor()); std::cout << neutralMap[y][x]->getSymbol() << " "; }
                else { Color::set(terrainMap[y][x]->getColor()); std::cout << terrainMap[y][x]->getSymbol() << " "; }
            }
            std::cout << "  \n";
        }
        Color::set(Color::Default);
        std::cout << "   ";
        for (int x = 0; x < width; ++x) std::cout << x % 10 << " ";
        std::cout << "  \n";
    }
};