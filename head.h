#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>
#include <windows.h>
#include <ctime>

// Заполнение контейнеров (вектор, список) 3-мя способами
void fillVectorFromKeyboard(std::vector<int>& v);
void fillVectorRandom(std::vector<int>& v, int size);
void fillVectorFromFile(std::vector<int>& v);

void fillListFromKeyboard(std::list<int>& l);
void fillListRandom(std::list<int>& l, int size);
void fillListFromFile(std::list<int>& l);

void fillStringListFromKeyboard(std::list<std::string>& l);
void fillStringListRandom(std::list<std::string>& l, int size);
void fillStringListFromFile(std::list<std::string>& l);

// Вывод структур на экран
void printVector(const std::vector<int>& v, const std::string& name);
void printList(const std::list<int>& l, const std::string& name);
void printStringList(const std::list<std::string>& l, const std::string& name);
void printStringDeque(const std::deque<std::string>& d, const std::string& name);
void printIntDeque(const std::deque<int>& d, const std::string& name);

// Задачи из лабы
void solveAlg3(std::list<int>& l);
void solveAlg19(std::deque<int>& d, int N);
void solveAlg47(std::vector<int>& v);
void solveAlg61(const std::list<std::string>& l, std::deque<std::string>& d);

// Проверка ввода
int getIntInput(const std::string& prompt, int minVal, int maxVal);
int getPositiveIntInput(const std::string& prompt);

// Менюшки
void fillListMenu(std::list<int>& l);
void fillVectorMenu(std::vector<int>& v);
void fillStringListMenu(std::list<std::string>& l);

#endif
