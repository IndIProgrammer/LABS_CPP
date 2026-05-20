#ifndef UNTITLED3_HEAD_H
#define UNTITLED3_HEAD_H
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <limits>
#include <functional>
#include <memory>
#include <map>
#include <utility>
#include <sstream>

// КЛАСС ПРОВЕРОК
class Validator {
public:
    static int getIntInput(int min, int max, const std::string& prompt);
    static int getIntInput(const std::string& prompt);
    static double getDoubleInput(double min, double max, const std::string& prompt);
    static std::string getStringInput(const std::string& prompt);
    static bool fileExists(const std::string& filename);
    static bool isNumber(const std::string& str);
    static bool isValidOperator(char op);
};

// КЛАСС УЗЛА ДЕРЕВА
class TreeNode {
public:
    int value;
    char op;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val);
    TreeNode(char operation);
    ~TreeNode();

    bool isOperator() const;
    bool isVariable() const;
    std::string toString() const;
};

// КЛАСС ДЕРЕВА ВЫРАЖЕНИЙ
class ExpressionTree {
private:
    TreeNode* root;

    TreeNode* buildFromRPN(const std::string& expression);
    int getOperatorCode(char op);
    char getOperatorFromCode(int code);
    TreeNode* evaluateDivision(TreeNode* node);
    int calculate(TreeNode* node);

    int getPriority(char op);
    std::vector<std::string> infixToRPN(const std::string& expression);
    TreeNode* buildFromRPNForTask26(const std::vector<std::string>& rpn);
    int evaluate(TreeNode* node, int x);
    TreeNode* replaceXWithValue(TreeNode* node, int x);
    void printTreeSideways(TreeNode* node, int level, std::ofstream& out);

    void deleteTree(TreeNode* node);
    TreeNode* copyTree(TreeNode* node);
    void printGraphical(TreeNode* node, int space, std::ostream& out);

public:
    ExpressionTree();
    ~ExpressionTree();

    void clear();

    // ДЛЯ ЗАДАЧИ 4
    void loadFromFileForTask4(const std::string& fn);
    void loadRandomForTask4();
    void loadFromKeyboardForTask4();
    void transformDivision();
    void saveTreeToFileForTask4(const std::string& fn);

    // ДЛЯ ЗАДАЧИ 26
    void loadFromFileForTask26(const std::string& fn1);
    void loadRandomForTask26();
    void loadFromKeyboardForTask26();
    int evaluateAndTransform(int x);
    void saveResultToFile(const std::string& fn2);
    void printTreeToFile(const std::string& fn2);

    // ОБЩИЕ МЕТОДЫ
    void fillRandom();
    void fillFromKeyboard();
    void fillFromFile(const std::string& inputFile);

    void printGraphical();
    void printGraphicalToFile(const std::string& filename);

    TreeNode* getRoot() const { return root; }
    void setRoot(TreeNode* newRoot) {
        if (root) deleteTree(root);
        root = newRoot;
    }

    bool isEmpty() const { return root == nullptr; }
};

// КЛАСС МЕНЮ
class MenuManager {
private:
    ExpressionTree& tree;

    void showMainMenu();
    void fillMenu();
    void task4Menu();
    void task26Menu();

public:
    MenuManager(ExpressionTree& t);
    void run();
};

#endif
