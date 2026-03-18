#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <windows.h>

class Node {
public:
    int Data;
    Node* Next;
    Node* Prev;

    Node(int value) : Data(value), Next(nullptr), Prev(nullptr) {}
};

class LinkedListTwo {
private:
    Node* head;
    Node* tail;

public:
    // Конструкторы и деструктор
    LinkedListTwo() : head(nullptr), tail(nullptr) {}
    LinkedListTwo(const LinkedListTwo& other);
    ~LinkedListTwo();

    // Основные операции
    void clear();
    int getSize() const;
    void append(int value);
    void prepend(int value);
    void insertAfter(Node* node, int value);
    void insertBefore(Node* node, int value);
    bool remove(Node* node);

    // Поиск
    Node* findNodeByPosition(int position);
    Node* findNodeByValue(int value) const;
    bool findElement(int value) const;

    // Вывод
    void print() const;
    void printReverse() const;

    // Заполнение
    void fillFromFile(const std::string& filename);
    void fillRandom(int count);
    void fillFromKeyboard();

    // Валидация
    static int getValidatedInt(const std::string& prompt, int min = 0, int max = 1000);

    // Задача 41: печать эл-а между макс. и мин.
    void printBetweenMinAndMax();

    // Задача 63: ввод в файл в обратном порядке и удаление списка после
    void saveReverseToFileAndClear(const std::string& filename);

    // Задача 4: Проверка симметричности строки
    static bool isStringSymmetric(const std::string& str);

    // Задача 46: Преобразование в циклический список с барьерным элементом
    Node* transformToCircularWithBarrier();

    // Задача 69: Вывод в файл с шагом k и удалением
    void saveWithStepToFileAndRemove(const std::string& filename, int k);

    // Для доступа к узлам в статических методах
    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }
    void setHead(Node* newHead) { head = newHead; }
    void setTail(Node* newTail) { tail = newTail; }
};

#endif
