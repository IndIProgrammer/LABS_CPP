#ifndef UNTITLED1_HEAD_H
#define UNTITLED1_HEAD_H

#include <windows.h>
#include <string>
#include <vector>

//для BackRec10
void BackRec10();
void backtrack(int index,
               std::vector<int>& current,
               int currentWeight,
               int currentTax,
               const std::vector<int>& weights,
               const std::vector<int>& taxes,
               int Z, int N,
               std::vector<int>& bestCombination,
               int& bestWeight,
               int& minTax,
               bool& foundSolution);

//для homedyn4
void HomeDyn4();

//для homedyn16
void HomeDyn16();


#endif //UNTITLED1_HEAD_H
