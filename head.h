#ifndef UNTITLED2_HEAD_H
#define UNTITLED2_HEAD_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <memory>
#include <windows.h>
#include <ctime>
#include <cstdlib>

// Функции для ввода с защитой
int safeInputInt(const std::string& prompt, int minVal = -1, int maxVal = -1);
std::string safeInputString(const std::string& prompt, bool checkName = false);
bool isValidName(const std::string& name);

// Задача 1: Человек
class Person {
private:
    std::string name;
    int height;

public:
    // Конструкторы
    Person();
    Person(std::string n, int h);

    // Геттеры
    std::string getName() const { return name; }
    int getHeight() const { return height; }

    // Сеттеры
    void setName(std::string n) { name = n; }
    void setHeight(int h) { height = h; }

    // Функция вывода
    void print() const;
    std::string toString() const;

    // Заполнение данными
    void inputFromKeyboard();
    void inputRandom();
    void inputFromFile(std::ifstream& file);
};

// Задача 2: Пистолет
class Gun {
private:
    int bullets;

public:
    // Конструкторы
    Gun();
    Gun(int b);

    // Методы
    void shoot();
    int getBullets() const { return bullets; }
    void setBullets(int b) { bullets = b; }

    // Функция вывода
    void print() const;

    // Заполнение данными
    void inputFromKeyboard();
    void inputRandom();
    void inputFromFile(std::ifstream& file);
};

// Задача 3: Имя (три параметра)
class Name {
private:
    std::string surname;
    std::string firstName;
    std::string patronymic;

public:
    // Конструкторы
    Name();
    Name(std::string fn);
    Name(std::string fn, std::string s);
    Name(std::string fn, std::string s, std::string p);

    // Геттеры
    std::string getSurname() const { return surname; }
    std::string getFirstName() const { return firstName; }
    std::string getPatronymic() const { return patronymic; }

    // Сеттеры
    void setSurname(std::string s) { surname = s; }
    void setFirstName(std::string fn) { firstName = fn; }
    void setPatronymic(std::string p) { patronymic = p; }

    // Функция вывода
    void print() const;
    std::string toString() const;

    // Заполнение данными
    void inputFromKeyboard();
    void inputRandom();
    void inputFromFile(std::ifstream& file);
};

// Задача 4: Сотрудники и отделы
class Department;
class Employee {
private:
    std::string name;
    Department* department;

public:
    // Конструкторы
    Employee();
    Employee(std::string n);
    Employee(std::string n, Department* dept);

    // Геттеры
    std::string getName() const { return name; }
    Department* getDepartment() const { return department; }

    // Сеттеры
    void setName(std::string n) { name = n; }
    void setDepartment(Department* dept);

    // Функция вывода
    void print() const;
    std::string toString() const;

    // Заполнение данными
    void inputFromKeyboard(std::vector<Department*>& depts);
    void inputRandom(std::vector<Department*>& depts);
    void inputFromFile(std::ifstream& file, std::vector<Department*>& depts);
};

class Department {
private:
    std::string name;
    Employee* boss;
    std::vector<Employee*> employees;

public:
    // Конструкторы
    Department();
    Department(std::string n);
    Department(std::string n, Employee* b);

    // Геттеры
    std::string getName() const { return name; }
    Employee* getBoss() const { return boss; }
    std::vector<Employee*> getEmployees() const { return employees; }

    // Сеттеры
    void setName(std::string n) { name = n; }
    void setBoss(Employee* b);
    void addEmployee(Employee* emp);

    // Функция вывода
    void print() const;
    std::string toString() const;

    // Получить список сотрудников отдела
    std::vector<Employee*> getEmployeeList() const { return employees; }

    // Заполнение данными
    void inputFromKeyboard(std::vector<Employee*>& employees);
    void inputRandom(std::vector<Employee*>& employees);
    void inputFromFile(std::ifstream& file, std::vector<Employee*>& employees);
};

// Задача 5: Имена (расширенная версия)
class ExtendedName {
private:
    std::string firstName;
    std::string surname;
    std::string patronymic;

public:
    // Конструкторы
    ExtendedName();
    ExtendedName(std::string fn);
    ExtendedName(std::string fn, std::string s);
    ExtendedName(std::string fn, std::string s, std::string p);

    // Геттеры
    std::string getFirstName() const { return firstName; }
    std::string getSurname() const { return surname; }
    std::string getPatronymic() const { return patronymic; }

    // Сеттеры
    void setFirstName(std::string fn) { firstName = fn; }
    void setSurname(std::string s) { surname = s; }
    void setPatronymic(std::string p) { patronymic = p; }

    // Функция вывода
    void print() const;
    std::string toString() const;

    // Заполнение данными
    void inputFromKeyboard();
    void inputRandom();
    void inputFromFile(std::ifstream& file);
};

// Задача 6: Сотрудники и отделы с возможностью получить список отдела
class AdvancedDepartment;
class AdvancedEmployee {
private:
    std::string name;
    AdvancedDepartment* department;

public:
    // Конструкторы
    AdvancedEmployee();
    AdvancedEmployee(std::string n);
    AdvancedEmployee(std::string n, AdvancedDepartment* dept);

    // Геттеры
    std::string getName() const { return name; }
    AdvancedDepartment* getDepartment() const { return department; }

    // Сеттеры
    void setName(std::string n) { name = n; }
    void setDepartment(AdvancedDepartment* dept);

    // Функции вывода
    void print() const;
    std::string toString() const;

    // Заполнение данных
    void inputFromKeyboard(std::vector<AdvancedDepartment*>& depts);
    void inputRandom(std::vector<AdvancedDepartment*>& depts);
    void inputFromFile(std::ifstream& file, std::vector<AdvancedDepartment*>& depts);
};

class AdvancedDepartment {
private:
    std::string name;
    AdvancedEmployee* boss;
    std::vector<AdvancedEmployee*> employees;

public:
    // Конструкторы
    AdvancedDepartment();
    AdvancedDepartment(std::string n);
    AdvancedDepartment(std::string n, AdvancedEmployee* b);

    // Геттеры
    std::string getName() const { return name; }
    AdvancedEmployee* getBoss() const { return boss; }
    std::vector<AdvancedEmployee*> getEmployees() const { return employees; }

    // Сеттеры
    void setName(std::string n) { name = n; }
    void setBoss(AdvancedEmployee* b);
    void addEmployee(AdvancedEmployee* emp);

    // Функции вывода
    void print() const;
    std::string toString() const;

    // Метод для получения списка всех сотрудников отдела
    std::vector<AdvancedEmployee*> getAllEmployees() const { return employees; }

    // Заполнение данных
    void inputFromKeyboard(std::vector<AdvancedEmployee*>& employees);
    void inputRandom(std::vector<AdvancedEmployee*>& employees);
    void inputFromFile(std::ifstream& file, std::vector<AdvancedEmployee*>& employees);
};

// Функции для отображения меню
void showMainMenu();
void showInputMethodMenu();

// Функции для демонстрации задач
void task1();
void task2();
void task3();
void task4();
void task5();
void task6();

#endif
