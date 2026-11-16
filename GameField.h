#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "Unit.h"
#include "Terrain.h"
#include "NeutralObject.h"
#include "ConsoleColor.h"

class GameField {
private:
    int width;
    int height;
    int maxUnits;
    int currentUnits;
    std::vector<std::vector<std::unique_ptr<Unit>>> grid;
    std::vector<std::vector<std::unique_ptr<TerrainProxy>>> terrainMap;
    std::vector<std::vector<std::unique_ptr<NeutralObject>>> neutralMap;

public:
    GameField(int w, int h, int maxU) : width(w), height(h), maxUnits(maxU), currentUnits(0) {
        grid.resize(height); terrainMap.resize(height); neutralMap.resize(height);
        for (int y = 0; y < height; ++y) {
            grid[y].resize(width); terrainMap[y].resize(width); neutralMap[y].resize(width);
            for (int x = 0; x < width; ++x) {
                terrainMap[y][x] = std::make_unique<TerrainProxy>(new Plains());
            }
        }
    }

    GameField(const GameField& other)
        : width(other.width), height(other.height), maxUnits(other.maxUnits), currentUnits(other.currentUnits) {
        try {
            grid.resize(height); terrainMap.resize(height); neutralMap.resize(height);
            for (int y = 0; y < height; ++y) {
                grid[y].resize(width); terrainMap[y].resize(width); neutralMap[y].resize(width);
                for (int x = 0; x < width; ++x) {
                    if (other.grid[y][x]) grid[y][x] = other.grid[y][x]->clone();
                    if (other.terrainMap[y][x]) terrainMap[y][x] = std::make_unique<TerrainProxy>(*other.terrainMap[y][x]);
                    if (other.neutralMap[y][x]) neutralMap[y][x] = other.neutralMap[y][x]->clone();
                }
            }
        }
        catch (...) { throw; }
    }

    GameField& operator=(const GameField& other) {
        if (this != &other) {
            GameField temp(other);
            std::swap(width, temp.width); std::swap(height, temp.height);
            std::swap(maxUnits, temp.maxUnits); std::swap(currentUnits, temp.currentUnits);
            std::swap(grid, temp.grid); std::swap(terrainMap, temp.terrainMap);
            std::swap(neutralMap, temp.neutralMap);
        }
        return *this;
    }

    GameField(GameField&& other) noexcept
        : width(other.width), height(other.height), maxUnits(other.maxUnits),
        currentUnits(other.currentUnits), grid(std::move(other.grid)), terrainMap(std::move(other.terrainMap)), neutralMap(std::move(other.neutralMap)) {
        other.width = 0; other.height = 0; other.maxUnits = 0; other.currentUnits = 0;
    }

    GameField& operator=(GameField&& other) noexcept {
        if (this != &other) {
            grid = std::move(other.grid); terrainMap = std::move(other.terrainMap); neutralMap = std::move(other.neutralMap);
            width = other.width; height = other.height; maxUnits = other.maxUnits; currentUnits = other.currentUnits;
            other.width = 0; other.height = 0; other.maxUnits = 0; other.currentUnits = 0;
        }
        return *this;
    }

    ~GameField() = default;

    void setTerrain(int x, int y, Terrain* terrain) {
        if (x >= 0 && x < width && y >= 0 && y < height) terrainMap[y][x] = std::make_unique<TerrainProxy>(terrain);
    }

    void setNeutralObject(int x, int y, std::unique_ptr<NeutralObject> obj) {
        if (x >= 0 && x < width && y >= 0 && y < height) neutralMap[y][x] = std::move(obj);
    }

    void removeNeutralObject(int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            neutralMap[y][x].reset();
        }
    }

    Unit* getUnit(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) return grid[y][x].get();
        return nullptr;
    }

    NeutralObject* getNeutralObject(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) return neutralMap[y][x].get();
        return nullptr;
    }

    void addUnit(std::unique_ptr<Unit> unit, int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) throw std::out_of_range("Вне поля!");
        if (grid[y][x] != nullptr) throw std::runtime_error("Клетка занята!");
        if (currentUnits >= maxUnits) throw std::runtime_error("Лимит юнитов!");
        unit->move(x, y);
        grid[y][x] = std::move(unit);
        currentUnits++;
    }

    void moveUnit(int ox, int oy, int nx, int ny) {
        if (ox < 0 || ox >= width || oy < 0 || oy >= height || nx < 0 || nx >= width || ny < 0 || ny >= height)
            throw std::out_of_range("Координаты вне поля!");
        if (grid[oy][ox] == nullptr) throw std::runtime_error("Начальная клетка пуста!");
        if (grid[ny][nx] != nullptr) throw std::runtime_error("Целевая клетка занята!");
        if (!terrainMap[ny][nx]->isPassable(grid[oy][ox]->getType())) throw std::runtime_error("Ландшафт непреодолим!");

        grid[ny][nx] = std::move(grid[oy][ox]);
        grid[ny][nx]->move(nx, ny);
    }

    void removeDeadUnits() {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (grid[y][x] && grid[y][x]->isDead()) { grid[y][x].reset(); currentUnits--; }
            }
        }
    }

    void printField() const {
        Color::set(Color::Default);
        std::cout << "\n";

        for (int y = 0; y < height; ++y) {
            Color::set(Color::Default);
            for (int x = 0; x < width; ++x) {
                if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                    Color::set(Color::Default); std::cout << "X ";
                }
                else if (grid[y][x]) {
                    Color::set(Color::Default); std::cout << grid[y][x]->getSymbol() << " ";
                }
                else if (neutralMap[y][x]) {
                    Color::set(neutralMap[y][x]->getColor()); std::cout << neutralMap[y][x]->getSymbol() << " ";
                }
                else {
                    Color::set(terrainMap[y][x]->getColor()); std::cout << terrainMap[y][x]->getSymbol() << " ";
                }
            }
            std::cout << "\n";
        }
        Color::set(Color::Default);
        std::cout << "\n";
    }

    class Iterator {
    private:
        GameField* field; int currX, currY;
        void skipEmpty() {
            while (currY < field->height) {
                if (currX >= field->width) { currX = 0; currY++; }
                else if (field->grid[currY][currX] == nullptr) { currX++; }
                else break;
            }
            if (currY >= field->height) { currX = field->width; currY = field->height; }
        }
    public:
        Iterator(GameField* f, int x, int y) : field(f), currX(x), currY(y) { skipEmpty(); }
        Unit* operator*() const { return field->grid[currY][currX].get(); }
        Iterator& operator++() { currX++; skipEmpty(); return *this; }
        bool operator!=(const Iterator& other) const { return currX != other.currX || currY != other.currY; }
    };

    Iterator begin() { return Iterator(this, 0, 0); }
    Iterator end() { return Iterator(this, width, height); }
};