#include "head.h"


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "  Лабораторная работа 10" << std::endl;

    while (true) {
        std::cout << "\nГЛАВНОЕ МЕНЮ" << std::endl;
        std::cout << "1. Dynamic6 - Стек (извлечь 9 элементов)" << std::endl;
        std::cout << "2. Dynamic21 - Очередь (переместить элементы)" << std::endl;
        std::cout << "3. ListWork4 - Список (пятый элемент)" << std::endl;
        std::cout << "4. ListWork25 - Список (вставка после каждого 2-го)" << std::endl;
        std::cout << "5. ListWork62 - Список (упорядоченный по убыванию)" << std::endl;
        std::cout << "0. Выход из программы" << std::endl;
        std::cout << "Выберите задание: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: demonstrateDynamic6(); break;
            case 2: demonstrateDynamic21(); break;
            case 3: demonstrateListWork4(); break;
            case 4: demonstrateListWork25(); break;
            case 5: demonstrateListWork62(); break;
            case 0:
                std::cout << "Программа завершена!" << std::endl;
                return 0;
            default:
                std::cout << "Неверный выбор! Пожалуйста, выберите 0-5." << std::endl;
        }
    }
}
