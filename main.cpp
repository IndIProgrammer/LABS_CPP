#include "head.h"

// Функция для заполнения файла
void fillFileManually() {
    std::cout << "\nЗАПОЛНЕНИЕ ФАЙЛА\n";
    std::cout << "Какой файл хотите заполнить?\n";
    std::cout << "1 - input.txt (для STL2Seq задач)\n";
    std::cout << "2 - name.txt (для STL1Iter15)\n";
    std::cout << "3 - source.txt (для копирования в STL1Iter15)\n";
    std::cout << "0 - Назад в меню\n";

    int choice = getIntInput("Ваш выбор (0-3): ", false, true, 3);

    if (choice == 0) return;

    std::string filename;
    switch(choice) {
        case 1: filename = "input.txt"; break;
        case 2: filename = "name.txt"; break;
        case 3: filename = "source.txt"; break;
    }

    std::cout << "\nЗаполняем файл " << filename << ":\n";
    fillFileThreeWays(filename);
    std::cout << "Файл " << filename << " успешно заполнен!\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;

    do {
        showMenu();
        choice = getMenuChoice();

        switch(choice) {
            case 1:
                STL2Seq2();
                break;
            case 2:
                STL2Seq11();
                break;
            case 3:
                STL2Seq27();
                break;
            case 4:
                STL1Iter15();
                break;
            case 5:
                fillFileManually();
                break;
            case 0:
                std::cout << "Программа завершена.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }

    } while (choice != 0);

    return 0;
}
