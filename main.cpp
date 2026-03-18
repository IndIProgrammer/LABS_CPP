#include <iostream>
#include "head.h"

void showMenu() {
    std::cout << "ЛАБОРАТОРНАЯ РАБОТА №8\n";
    std::cout << "1. BackRec10 - Археолог (налоги)\n";
    std::cout << "2. HomeDyn4 - Хромой король\n";
    std::cout << "3. HomeDyn16 - K-ичные числа\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие (0-3): ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice = -1;

    while (choice != 0) {
        showMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: {
                BackRec10();
                break;
            }
            case 2: {
                HomeDyn4();
                break;
            }
            case 3: {
                HomeDyn16();
                break;
            }
            case 0: {
                std::cout << "\nВыход из программы. . .\n";
                break;
            }
            default: {
                std::cout << "\nОшибка: неверный выбор. Пожалуйста, выберите от 0 до 3.\n";
                std::cin.ignore(10000, '\n');
                break;
            }
        }
    }

    return 0;
}
