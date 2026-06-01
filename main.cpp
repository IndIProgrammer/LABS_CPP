#include "head.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned int>(time(0)));

    // Блок тестирования конструкторов
    std::cout << "Тестирование конструкторов" << std::endl;
    RightTriangle t1;
    RightTriangle t2(3.0, 4.0);
    RightTriangle t3(t2);
    std::cout << "Конструктор по умолчанию: " << t1 << std::endl;
    std::cout << "Конструктор с параметрами: " << t2 << std::endl;
    std::cout << "Конструктор копирования: " << t3 << std::endl;

    MenuManager menu;
    menu.run();

    return 0;
}
