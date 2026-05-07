#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <limits>  // для numeric_limits

class BinaryTree {
private:
    // Поля узла
    int data;
    BinaryTree* left;
    BinaryTree* right;

    // Корень дерева
    BinaryTree* root;

    // Вспомогательные методы
    int getHeight(BinaryTree* node);
    void getLeavesLeftToRight(BinaryTree* node, std::vector<int>& leaves);
    int countLeavesHelper(BinaryTree* node);
    bool isAVLHelper(BinaryTree* node, int& height);
    void clearTree(BinaryTree*& node);

public:
    BinaryTree();  // Конструктор
    BinaryTree(int val);  // Конструктор с значением
    ~BinaryTree();  // Деструктор

    // Способы ввода
    void inputManual();
    void inputRandom();
    void inputFromFile();

    // Основные методы задач
    void printLeavesLeftToRight();  // TreeWork4
    int countLeaves();               // TreeWork13
    bool isAVLBalanced();            // TreeWork20

    // Вспомогательные методы
    void printGraphicalTree();
    BinaryTree* getRoot() { return root; }
    void setRoot(BinaryTree* newRoot) { root = newRoot; }

    // Геттеры для доступа к полям (нужны для класса проверок)
    int getData() const { return data; }
    BinaryTree* getLeft() const { return left; }
    BinaryTree* getRight() const { return right; }
    void setLeft(BinaryTree* node) { left = node; }
    void setRight(BinaryTree* node) { right = node; }
};

// КЛАСС ПРОВЕРОК
class InputValidator {
private:
    // Очистка буфера ввода
    static void clearInputStream() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

public:
    // Проверка ввода целого числа
    static int getInt(const std::string& prompt) {
        int value;
        std::cout << prompt;
        while (!(std::cin >> value)) {
            std::cout << "Ошибка! Введите целое число: ";
            clearInputStream();
        }
        return value;
    }

    // Проверка ввода положительного целого числа
    static int getPositiveInt(const std::string& prompt) {
        int value;
        std::cout << prompt;
        while (!(std::cin >> value) || value <= 0) {
            if (!std::cin) {
                std::cout << "Ошибка! Введите целое число: ";
            } else {
                std::cout << "Ошибка! Введите число больше 0: ";
            }
            clearInputStream();
        }
        return value;
    }

    // Проверка ввода числа в диапазоне
    static int getIntInRange(const std::string& prompt, int min, int max) {
        int value;
        std::cout << prompt;
        while (!(std::cin >> value) || value < min || value > max) {
            if (!std::cin) {
                std::cout << "Ошибка! Введите целое число: ";
            } else {
                std::cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
            }
            clearInputStream();
        }
        return value;
    }

    // Проверка ввода значения узла (может быть любое целое число)
    static int getNodeValue(const std::string& prompt) {
        int value;
        std::cout << prompt;
        while (!(std::cin >> value)) {
            std::cout << "Ошибка! Введите целое число: ";
            clearInputStream();
        }
        return value;
    }

    // Проверка выбора меню
    static int getMenuChoice(int min, int max) {
        return getIntInRange("Выберите пункт: ", min, max);
    }

    // Проверка выбора способа ввода
    static int getInputMethod() {
        return getIntInRange("Выберите способ: ", 1, 3);
    }

    // Проверка ввода размера массива
    static int getArraySize() {
        return getPositiveInt("Введите размер массива: ");
    }

    // Проверка ввода количества узлов
    static int getNodeCount() {
        return getPositiveInt("Введите количество узлов: ");
    }

    // Проверка ввода диапазона случайных чисел
    static void getRange(int& min, int& max) {
        min = getInt("Введите минимальное значение: ");
        max = getInt("Введите максимальное значение: ");
        while (min >= max) {
            std::cout << "Ошибка! Минимум должен быть меньше максимума!" << std::endl;
            min = getInt("Введите минимальное значение: ");
            max = getInt("Введите максимальное значение: ");
        }
    }

    // Проверка, что дерево не пустое
    static bool isTreeNotEmpty(BinaryTree* root) {
        if (!root) {
            std::cout << "Дерево пусто! Сначала введите дерево (пункт 1)" << std::endl;
            return false;
        }
        return true;
    }
};

// Функции меню
void showMainMenu();
void handleMenuChoice(int choice, BinaryTree& tree);
void inputTree(BinaryTree& tree);

#endif
