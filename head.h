#ifndef UNTITLED2_HEAD_H
#define UNTITLED2_HEAD_H

#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

// Проверка существования файла
bool fileExists(const std::string& filename);

// ============= ФАЙЛОВЫЕ ОПЕРАЦИИ =============
// File9: Создать файл из конечного и начального элементов существующего файла
void File9(const std::string& existingFile, const std::string& newFile);

// File32: Удалить первую половину элементов из файла
void File32(const std::string& filename);

// File51: Объединить три упорядоченных по убыванию файла
void File51(const std::string& file1, const std::string& file2,
                 const std::string& file3, const std::string& resultFile);

// ============= РЕКУРСИЯ =============
// Recur15: Вычисление арифметического выражения с операциями +, -, *
int Recur15(const std::string& expression);

// Вспомогательные функции для Recur15
bool isDigit(char c);
int parseTerm(const std::string& s, int& pos);
int parseExpression(const std::string& s, int& pos);

// ============= ФУНКЦИИ ДЛЯ ТЕСТИРОВАНИЯ =============
// Создание тестовых файлов со случайными значениями
void createTestFiles();
// Просмотр содержимого бинарных файлов
void viewBinaryFiles();

// Сортировка массива double по убыванию
void sortDescending(double* arr, int size);

#endif
