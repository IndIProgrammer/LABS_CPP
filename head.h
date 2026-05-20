#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <limits>
#include <windows.h>

// Класс для узла двусвязного списка / бинарного дерева
class Node {
public:
    int data;
    Node* left;   // prev в списке / левый потомок в дереве
    Node* right;  // next в списке / правый потомок в дереве

    Node(int val);
};

// Класс двусвязного списка
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void clear();
    void pushBack(int value);
    int getSize() const;
    Node* getHead() const;
    Node* getTail() const;
    void printList() const;
};

// Класс бинарного дерева
class BinaryTree {
private:
    Node* root;

    void clearTree(Node* node); // Итеративная безопасная очистка памяти
    void printTreeSideways(Node* node, int level) const;
    int calculateHeight(Node* node) const;

    // Классическая вставка для бинарного дерева поиска (BST)
    void insertBST(Node*& node, int value);

    // Вставка по случайному пути (75% вправо, 25% влево) для дисбаланса
    void insertRandomUnbalanced(Node*& node, int value);

public:
    BinaryTree();
    ~BinaryTree();

    void clear();
    void setRoot(Node* root);
    Node* getRoot() const;

    // Построение честного BST дерева из элементов списка (Задание 2)
    void convertFromListToBST(DoublyLinkedList& originalList);

    // Методы генерации для несбалансированных деревьев (Задачи 6 и 9)
    void generateRandomUnbalanced(int count);
    bool generateFromFileUnbalanced(const std::string& filename);
    void insertSingleUnbalanced(int value);

    void printTree() const;
    int getHeight() const;
};

// Класс итератора для обхода "корень-право-лево"
class TreeIterator {
private:
    Node* root;
    std::stack<Node*> nodeStack;

public:
    TreeIterator(Node* root);
    bool hasNext();
    int next();
    void reset();
};

// Класс для размещения камер
class CameraPlacer {
private:
    int cameras;
    int minCameraCover(Node* node);

public:
    CameraPlacer();
    int getMinCameras(Node* root);
};

// Класс валидации входных данных
class Validator {
private:
    static void clearInputBuffer();

public:
    static int getIntInput(int min, int max, const std::string& prompt);
    static int getIntInput(const std::string& prompt);
    static double getDoubleInput(double min, double max, const std::string& prompt);
    static std::string getStringInput(const std::string& prompt);
    static bool fileExists(const std::string& filename);
    static int getMenuChoice(int min, int max, const std::string& prompt);
};

// Класс менеджера меню
class MenuManager {
private:
    BinaryTree treeTask2;
    BinaryTree treeTask6;
    BinaryTree treeTask9;

    void showMainMenu();
    void fillListMenu(DoublyLinkedList& targetList);        // Заполнение списка в порядке: рандом, клавиатура, файл
    void fillUnbalancedTreeMenu(BinaryTree& tree, int def); // Заполнение дерева в порядке: рандом, клавиатура, файл
    void task2Menu();
    void task6Menu();
    void task9Menu();

public:
    MenuManager();
    void run();
};

#endif
