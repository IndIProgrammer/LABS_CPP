#ifndef UNTITLED5_HEAD_H
#define UNTITLED5_HEAD_H
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <windows.h>

// STL2Seq2
void STL2Seq2();

// STL2Seq11
void STL2Seq11();

// STL2Seq27
void STL2Seq27();

// STL1Iter15
void STL1Iter15();

// Вспомогательные функции
void clearInputStream();
int getIntInput(const std::string& prompt, bool positiveOnly = false);
int getIntInput(const std::string& prompt, bool positiveOnly, bool checkRange, int maxValue);
int getMenuChoice();
void showMenu();
void fillFileThreeWays(const std::string& filename);

#endif
