#include "head.h"

void printMenu() {
    std::cout << "\nЛАБОРАТОРНАЯ РАБОТА №14\n";
    std::cout << "1. Задача STL5Assoc3 (множества с повторениями)\n";
    std::cout << "2. Задача STL5Assoc15 (отображение map)\n";
    std::cout << "3. Задача STL5Assoc22 (мультиотображение multimap)\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите задачу: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Объявляем переменные для хранения данных
    std::vector<int> V0;
    std::vector<int> V;
    std::vector<std::vector<int>> Vn;
    std::vector<std::string> Vwords;

    int choice;

    do {
        printMenu();
        choice = safeGetInt();

        switch(choice) {
            case 1:
                fillVectorsSet(V0, Vn);
                taskSTL5Assoc3(V0, Vn);
                break;

            case 2:
                fillVectorsForMap(V);
                taskSTL5Assoc15(V);
                break;

            case 3:
                fillVectorsForMultimap(Vwords);
                taskSTL5Assoc22(Vwords);
                break;

            case 0:
                std::cout << "Выход из программы...\n";
                break;

            default:
                std::cout << "Неверный выбор! Введите число от 0 до 3.\n";
        }

    } while (choice != 0);

    return 0;
}
