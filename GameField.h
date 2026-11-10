#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "Unit.h"

class GameField {
private:
    int width;
    int height;
    int maxUnits;
    std::vector<std::vector<std::unique_ptr<Unit>>> grid;

public:
    GameField(int w, int h, int maxU) : width(w), height(h), maxUnits(maxU) {
        grid.resize(height);
        for (int y = 0; y < height; ++y) {
            grid[y].resize(width);
        }
    }

    GameField(const GameField& other)
        : width(other.width), height(other.height), maxUnits(other.maxUnits) {
        grid.resize(height);
        for (int y = 0; y < height; ++y) {
            grid[y].resize(width);
            for (int x = 0; x < width; ++x) {
                if (other.grid[y][x]) grid[y][x] = other.grid[y][x]->clone();
            }
        }
    }

    GameField& operator=(const GameField& other) {
        if (this != &other) {
            width = other.width; height = other.height; maxUnits = other.maxUnits;
            grid.clear(); grid.resize(height);
            for (int y = 0; y < height; ++y) {
                grid[y].resize(width);
                for (int x = 0; x < width; ++x) {
                    if (other.grid[y][x]) grid[y][x] = other.grid[y][x]->clone();
                    else grid[y][x].reset();
                }
            }
        }
        return *this;
    }

    GameField(GameField&& other) noexcept
        : width(other.width), height(other.height), maxUnits(other.maxUnits), grid(std::move(other.grid)) {
        other.width = 0; other.height = 0; other.maxUnits = 0;
    }

    GameField& operator=(GameField&& other) noexcept {
        if (this != &other) {
            grid = std::move(other.grid);
            width = other.width; height = other.height; maxUnits = other.maxUnits;
            other.width = 0; other.height = 0; other.maxUnits = 0;
        }
        return *this;
    }

    ~GameField() = default;

    void addUnit(std::unique_ptr<Unit> unit, int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) throw std::out_of_range("Вне поля!");
        if (grid[y][x] != nullptr) throw std::runtime_error("Клетка занята!");
        if (getSize() >= maxUnits) throw std::runtime_error("Лимит юнитов!");

        unit->move(x, y);
        std::cout << "Добавлен юнит: " << unit->getName() << " [" << unit->getSymbol() << "] на позицию (" << x << ", " << y << ").\n";
        grid[y][x] = std::move(unit);
    }

    void moveUnit(int ox, int oy, int nx, int ny) {
        if (grid[oy][ox] == nullptr) throw std::runtime_error("Начальная клетка пуста!");
        if (grid[ny][nx] != nullptr) throw std::runtime_error("Целевая клетка занята!");

        std::cout << "Юнит " << grid[oy][ox]->getName() << " перемещен из (" << ox << ", " << oy << ") в (" << nx << ", " << ny << ").\n";
        grid[ny][nx] = std::move(grid[oy][ox]);
        grid[ny][nx]->move(nx, ny);
    }

    void removeDeadUnits() {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (grid[y][x] && grid[y][x]->isDead()) {
                    std::cout << ">>> Юнит " << grid[y][x]->getName() << " [" << grid[y][x]->getSymbol() << "] удален с поля (" << x << ", " << y << ").\n";
                    grid[y][x].reset();
                }
            }
        }
    }

    int getSize() const {
        int count = 0;
        for (const auto& row : grid)
            for (const auto& unit : row)
                if (unit) count++;
        return count;
    }

    void printField() const {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                    std::cout << "X ";
                }
                else if (grid[y][x]) {
                    std::cout << grid[y][x]->getSymbol() << " ";
                }
                else {
                    std::cout << ". ";
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    class Iterator {
    private:
        GameField* field;
        int currX, currY;
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