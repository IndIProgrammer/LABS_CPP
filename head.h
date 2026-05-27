#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>
#include <windows.h>

// Класс для проверки и получения ввода
class Validator {
private:
    static void clearInputBuffer();
public:
    static int getIntInput(int min, int max, const std::string& prompt);
    static std::string getStringInput(const std::string& prompt);
    static std::string getFileString(const std::string& filename);
    static bool fileExists(const std::string& filename);
};

// Задача 1: Код Хемминга
class Hamming {
public:
    void runTask(const std::string& inputStr);
private:
    bool isPowerOfTwo(int n);
    int calcParityBitsCount(int m);
    std::vector<int> encode(const std::vector<int>& dataBits, int r);
    int getSyndrome(const std::vector<int>& encoded, int r);
};

// Класс узла для дерева Хаффмана
class HuffmanNode {
private:
    std::string data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
public:
    HuffmanNode(std::string d, int f);
    std::string getData() const;
    int getFreq() const;
    HuffmanNode* getLeft() const;
    HuffmanNode* getRight() const;
    void setLeft(HuffmanNode* l);
    void setRight(HuffmanNode* r);
    bool isLeaf() const;
};

// Компаратор для приоритетной очереди
class CompareNodes {
public:
    bool operator()(HuffmanNode* l, HuffmanNode* r);
};

// Задача 2: Код Хаффмана
class Huffman {
public:
    void runTask(const std::string& text);
private:
    void generateCodes(HuffmanNode* root, const std::string& str, std::map<std::string, std::string>& huffmanCode);
    void destroyTree(HuffmanNode* root);
    void printTreeSideways(HuffmanNode* node, int level, std::ostream& out, std::string path = "");
};

// Задача 3: Столбчатый шифр
class ColumnarCipher {
public:
    void runTask(const std::string& text, const std::string& key);
private:
    std::string encrypt(const std::string& text, const std::string& key);
    std::string decrypt(const std::string& text, const std::string& key);
    std::vector<int> getOrder(const std::string& key);
};

// Класс менеджера циклического меню
class MenuManager {
public:
    MenuManager();
    void run();
private:
    void showMainMenu();
    void task1Menu();
    void task2Menu();
    void task3Menu();
};

#endif
