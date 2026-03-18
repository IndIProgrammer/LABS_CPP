#ifndef UNTITLED3_HEAD_H
#define UNTITLED3_HEAD_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <limits>
#include <string>

// Узел для стека и очереди
struct Node {
    int Data;
    Node* Next;

    // Конструктор (вызывается при создании нового узла)
    Node(int data) : Data(data), Next(nullptr) {}
};

// Класс для стека (используется в Dynamic6)
// LIFO
class Stack {
private:
    Node* top;

public:
    // По умолчанию пустой стэк
    Stack() : top(nullptr) {}

    // Конструктор копирования
    Stack(const Stack& other);

    // Деструктор
    ~Stack();

    // Методы для работы со стеком
    void push(int value);
    int pop();
    bool isEmpty() const;
    Node* getTop() const { return top; }
    void setTop(Node* newTop) { top = newTop; }

    // Метод для Dynamic6
    void popNineElements();

    // Поиск элемента по значению
    bool findElement(int value) const;

    // Поиск с выводом информации
    void searchAndDisplay(int value) const;

    // Вспомогательные методы
    void print() const;
    void fillFromFile(const std::string& filename);
    void fillRandom(int count);

    // Защита от дурака при вводе чисел
    static int getValidatedInt(const std::string& prompt, int min = std::numeric_limits<int>::min(),
                               int max = std::numeric_limits<int>::max());
};

// Класс для очереди (используется в Dynamic21)
// FIFO (добавление в конец удаление из начала)
class Queue {
private:
    Node* head;
    Node* tail;

public:
    // Конструкторы и деструктор
    Queue() : head(nullptr), tail(nullptr) {}
    Queue(const Queue& other);
    ~Queue();

    // Методы для работы с очередью
    void enqueue(int value);
    int dequeue();
    bool isEmpty() const;
    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }
    void setHead(Node* newHead) { head = newHead; }
    void setTail(Node* newTail) { tail = newTail; }

    // Метод для Dynamic21
    void moveAllTo(Queue& dest);

    // Поиск элемента по значению
    bool findElement(int value) const;

    // Поиск с выводом информации
    void searchAndDisplay(int value) const;

    // Вспомогательные методы
    void print() const;
    void fillFromFile(const std::string& filename);
    void fillRandom(int count);

    // Защита от дурака при вводе чисел
    static int getValidatedInt(const std::string& prompt, int min = std::numeric_limits<int>::min(),
                               int max = std::numeric_limits<int>::max());
};

// Класс для односвязного списка (используется в ListWork4, ListWork25, ListWork62)
class LinkedList {
private:
    Node* head;

public:
    // Конструкторы и деструктор
    LinkedList() : head(nullptr) {}
    LinkedList(const LinkedList& other);
    ~LinkedList();

    // Методы для работы со списком
    void append(int value);           // Добавление в конец
    void insertAfter(Node* prev, int value);
    void insertBefore(Node* next, int value);
    Node* findNodeByPosition(int position); // Поиск узла по позиции (1-based)
    Node* getLastNode();

    // Методы для задач
    Node* getElementAtPosition(int pos); // ListWork4
    LinkedList insertBeforeEverySecond(int m) const; // ListWork25 (исправлено)
    void insertSortedDescending(int value); // ListWork62

    // Поиск элемента по значению
    bool findElement(int value) const;

    // Поиск с выводом информации
    void searchAndDisplay(int value) const;

    // Поиск узла по значению (возвращает указатель на узел)
    Node* findNodeByValue(int value) const;

    // Вспомогательные методы
    Node* getHead() const { return head; }
    void setHead(Node* newHead) { head = newHead; }
    void print() const;
    void fillFromFile(const std::string& filename);
    void fillRandom(int count);
    void fillSortedDescendingFromFile(const std::string& filename);
    void clear();

    // Защита от дурака при вводе чисел
    static int getValidatedInt(const std::string& prompt, int min = std::numeric_limits<int>::min(),
                               int max = std::numeric_limits<int>::max());
};

// Функции для демонстрации
void demonstrateDynamic6();
void demonstrateDynamic21();
void demonstrateListWork4();
void demonstrateListWork25();
void demonstrateListWork62();

// Вспомогательная функция для очистки буфера ввода
void clearInputBuffer();

#endif //UNTITLED3_HEAD_H
