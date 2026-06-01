#ifndef UNTITLED3_HEAD_H
#define UNTITLED3_HEAD_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

class RightTriangle {
private:
    double a;
    double b;

public:
    RightTriangle();
    RightTriangle(double sideA, double sideB);
    RightTriangle(const RightTriangle& other);

    void setSides(double sideA, double sideB);
    double getArea() const;

    // Геттеры для вывода значений
    double getA() const { return a; }
    double getB() const { return b; }

    RightTriangle& operator++();
    RightTriangle& operator--();

    explicit operator double() const;
    operator bool() const;

    bool operator<=(const RightTriangle& other) const;
    bool operator>=(const RightTriangle& other) const;

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const RightTriangle& rt);
};

class Validator {
private:
    static void clearInputBuffer();

public:
    static int getIntInput(int min, int max, const std::string& prompt);
    static double getDoubleInput(double min, double max, const std::string& prompt);
    static int getMenuChoice(int min, int max, const std::string& prompt);

    static double getRandomDouble(double min, double max);
    static bool fileExists(const std::string& filename);
    static double getDoubleFromFile(const std::string& filename, int index);
};

class MenuManager {
private:
    RightTriangle triangle;
    bool isInitialized;

    void showMainMenu();
    void fillTriangleData();
    void compareTriangles(); // для тестов

public:
    MenuManager();
    void run();
};

#endif
