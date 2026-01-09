#ifndef UNTITLED2_HEADLER_H
#define UNTITLED2_HEADLER_H
#include <string>
#include <vector>
#include <windows.h>
void solveTask1();
void solveTask2();
void solveTask3();

//структура для работы с книгами
struct Book {
    std::string title;
    std::string author;
    int year;

    Book(const std::string& t = "", const std::string& a = "", int y = 0)
            : title(t), author(a), year(y) {}
};

//структура содержащая параметры для фитнесс центра
struct FitnessRecord {
    int month;
    int year;
    int clientCode;
    int duration;
};

//структура для работы с обучающимися
struct Student {
    std::string lastName;
    std::string firstName;
    int classNum;

    union AdditionalData {
        short readingSpeed;      // для 1-х классов
        short mathScore;         // для 2-х и 3-х классов
        float examScore;         // для 4-х классов
    } data;
};
#endif
