#include "head.h"

// Реализация RightTriangle

// Конструктор по умолчанию
RightTriangle::RightTriangle() : a(0), b(0) {}

// Конструктор с параметрами
RightTriangle::RightTriangle(double sideA, double sideB) : a(sideA), b(sideB) {}

// Конструктор копирования
RightTriangle::RightTriangle(const RightTriangle& other) : a(other.a), b(other.b) {}

// Установка сторон треугольника
void RightTriangle::setSides(double sideA, double sideB) {
    a = sideA;
    b = sideB;
}

// Если треугольник существует то вернёт площадь иначе -1
double RightTriangle::getArea() const {
    if (*this) return 0.5 * a * b;
    return -1.0;
}

// ПЕРЕГРУЗКА ОПЕРАТОРОВ

// Перегрузка ++: увеличение сторон в 2 раза
RightTriangle& RightTriangle::operator++() {
    a *= 2.0;
    b *= 2.0;
    return *this;
}

// Перегрузка --: уменьшение сторон в 2 раза
RightTriangle& RightTriangle::operator--() {
    a /= 2.0;
    b /= 2.0;
    return *this;
}

// Приведение к double: возвращает площадь
RightTriangle::operator double() const {
    return getArea();
}

// Приведение к bool: проверка сторон на положительность
RightTriangle::operator bool() const {
    return a > 0 && b > 0;
}

// Сравнение площадей <=
bool RightTriangle::operator<=(const RightTriangle& other) const {
    return this->getArea() <= other.getArea();
}

// Сравнение площадей >=
bool RightTriangle::operator>=(const RightTriangle& other) const {
    return this->getArea() >= other.getArea();
}

// Реализация оператора вывода
std::ostream& operator<<(std::ostream& os, const RightTriangle& rt) {
    os << "Прямоугольный треугольник (катеты: " << rt.a << ", " << rt.b << ")";
    return os;
}

// Реализация Validator
void Validator::clearInputBuffer() { std::cin.clear(); std::cin.ignore(10000, '\n'); }

int Validator::getIntInput(int min, int max, const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) return value;
        clearInputBuffer();
        std::cout << "Ошибка ввода." << std::endl;
    }
}

double Validator::getDoubleInput(double min, double max, const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) return value;
        clearInputBuffer();
        std::cout << "Ошибка ввода." << std::endl;
    }
}

int Validator::getMenuChoice(int min, int max, const std::string& prompt) { return getIntInput(min, max, prompt); }

double Validator::getRandomDouble(double min, double max) { return min + (double)rand() / RAND_MAX * (max - min); }

bool Validator::fileExists(const std::string& filename) { std::ifstream f(filename); return f.good(); }

double Validator::getDoubleFromFile(const std::string& filename, int index) {
    std::ifstream f(filename);
    double val = 0.0;
    for(int i = 0; i <= index; ++i) f >> val;
    return val;
}

// Реализация MenuManager
MenuManager::MenuManager() : isInitialized(false) {}

void MenuManager::showMainMenu() {
    std::cout << "\nГлавное меню:" << std::endl;
    std::cout << "1) Задать параметры" << std::endl;
    std::cout << "2) Операции (++ / --)" << std::endl;
    std::cout << "3) Вывести площадь" << std::endl;
    std::cout << "4) Сравнить с другим треугольником" << std::endl;
    std::cout << "0) Выход" << std::endl;
}

void MenuManager::fillTriangleData() {
    std::cout << "Выберите способ ввода:" << std::endl;
    std::cout << "1) Клавиатура" << std::endl;
    std::cout << "2) Случайно" << std::endl;
    std::cout << "3) Файл input.txt" << std::endl;

    int method = Validator::getMenuChoice(1, 3, "Ваш выбор: ");
    double a = 0, b = 0;

    if (method == 1) {
        a = Validator::getDoubleInput(0.1, 1000.0, "Катет a: ");
        b = Validator::getDoubleInput(0.1, 1000.0, "Катет b: ");
    } else if (method == 2) {
        a = Validator::getRandomDouble(1.0, 100.0);
        b = Validator::getRandomDouble(1.0, 100.0);
    } else if (Validator::fileExists("input.txt")) {
        a = Validator::getDoubleFromFile("input.txt", 0);
        b = Validator::getDoubleFromFile("input.txt", 1);
    } else {
        std::cout << "Файл input.txt не найден!" << std::endl;
        return;
    }

    triangle.setSides(a, b);
    isInitialized = true;
    std::cout << "Установлено: " << triangle << std::endl;
}

void MenuManager::compareTriangles() {
    if (!isInitialized) {
        std::cout << "Сначала задайте параметры!" << std::endl;
        return;
    }

    double a2 = Validator::getDoubleInput(0.1, 1000.0, "Катет a 2-го треугольника: ");
    double b2 = Validator::getDoubleInput(0.1, 1000.0, "Катет b 2-го треугольника: ");

    RightTriangle other(a2, b2);

    // Добавляем вывод площадей для наглядности
    std::cout << "\nСравнение площадей" << std::endl;
    std::cout << "Площадь 1-го: " << (double)triangle << std::endl;
    std::cout << "Площадь 2-го: " << (double)other << std::endl;

    // Результаты сравнения
    std::cout << "Т1 <= Т2: " << (triangle <= other ? "Да" : "Нет") << std::endl;
    std::cout << "Т1 >= Т2: " << (triangle >= other ? "Да" : "Нет") << std::endl;
}

void MenuManager::run() {
    int choice;
    do {
        showMainMenu();
        choice = Validator::getMenuChoice(0, 4, "Ваш выбор: ");

        switch (choice) {
            case 1:
                fillTriangleData();
                break;
            case 2:
                if (!isInitialized) {
                    std::cout << "Нет данных" << std::endl;
                } else {
                    int act = Validator::getMenuChoice(1, 2, "1-Увеличить\n 2-Уменьшить\n Ваш выбор: ");
                    (act == 1) ? ++triangle : --triangle;
                    std::cout << "Результат: " << triangle << std::endl;
                }
                break;
            case 3:
                if (isInitialized) {
                    std::cout << "Площадь: " << (double)triangle << std::endl;
                } else {
                    std::cout << "Нет данных" << std::endl;
                }
                break;
            case 4:
                compareTriangles();
                break;
            case 0:
                std::cout << "Завершение программы..." << std::endl;
                break;
            default:
                std::cout << "Ошибка: неверный выбор!" << std::endl;
                break;
        }
    } while (choice != 0);
}
