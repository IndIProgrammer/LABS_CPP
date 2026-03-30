#ifndef UNTITLED2_HEAD_H
#define UNTITLED2_HEAD_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <windows.h>

// Функции для безопасного ввода
int safeGetInt(const std::string& prompt = "");
int safeGetPositiveInt(const std::string& prompt);
int safeGetMenuChoice(int min, int max);

// Функции для заполнения векторов
void fillVectorFromKeyboard(std::vector<int>& vec, const std::string& name);
void fillVectorRandom(std::vector<int>& vec, int size, int minVal, int maxVal);
void fillVectorFromFile(std::vector<int>& vec);
void fillStringVectorFromKeyboard(std::vector<std::string>& vec, const std::string& name);
void fillStringVectorRandom(std::vector<std::string>& vec, int size);
void fillStringVectorFromFile(std::vector<std::string>& vec);

// Функции для заполнения данных (теперь принимают ссылки на нужные векторы)
void fillVectorsSet(std::vector<int>& V0, std::vector<std::vector<int>>& Vn);
void fillVectorsForMap(std::vector<int>& V);
void fillVectorsForMultimap(std::vector<std::string>& Vwords);

// Функции для решения задач
void taskSTL5Assoc3(const std::vector<int>& V0, const std::vector<std::vector<int>>& Vn);
void taskSTL5Assoc15(const std::vector<int>& V);
void taskSTL5Assoc22(const std::vector<std::string>& Vwords);

#endif
