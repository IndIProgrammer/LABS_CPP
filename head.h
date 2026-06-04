#ifndef UNTITLED3_HEAD_H
#define UNTITLED3_HEAD_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <iomanip>

class Validator {
public:
    static void clearInputBuffer();
    static int getIntInput(int min, int max, const std::string& prompt);
    static bool fileExists(const std::string& filename);
};

class GraphSolver {
private:
    static std::vector<int> bfs(int startNode, int n, const std::vector<std::vector<int>>& adj);

public:
    static void inputMethodMenu(int &n, std::vector<std::vector<int>> &adj, const std::string& defaultFile, int maxN);
    static void readFromFile(int &n, std::vector<std::vector<int>> &adj, const std::string& filename);
    static void readFromConsole(int &n, std::vector<std::vector<int>> &adj, int maxN);
    static void generateRandom(int &n, std::vector<std::vector<int>> &adj, int maxN);

    static void solveGraf2();
    static void solveGraf7();
    static void solveGraf8();
};

class MenuManager {
private:
    void showMainMenu();
public:
    MenuManager();
    void run();
};

#endif
