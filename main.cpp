#include "head.h"

void Menu() {
    std::cout << "ЛАБОРАТОРНАЯ РАБОТА 9\n";
    std::cout << "1. File9  - Создать файл из начального и конечного элементов\n";
    std::cout << "2. File32 - Удалить первую половину \n";
    std::cout << "3. File51 - Объединить три упорядоченных по убыванию файла\n";
    std::cout << "4. Recur15 - Вычислить выражение с *, +, -\n";
    std::cout << "5. СОЗДАТЬ ТЕСТОВЫЕ ФАЙЛЫ (со случайными значениями)\n";
    std::cout << "6. ПРОСМОТРЕТЬ тестовые файлы\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;

    do {
        Menu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string file1, file2;
                std::cout << "Введите имя существующего файла: ";
                std::cin >> file1;
                std::cout << "Введите имя нового файла: ";
                std::cin >> file2;
                File9(file1, file2);
                break;
            }
            case 2: {
                std::string filename;
                std::cout << "Введите имя файла: ";
                std::cin >> filename;
                File32(filename);
                break;
            }
            case 3: {
                std::string file1, file2, file3, result;
                std::cout << "Введите имя первого файла: ";
                std::cin >> file1;
                std::cout << "Введите имя второго файла: ";
                std::cin >> file2;
                std::cout << "Введите имя третьего файла: ";
                std::cin >> file3;
                std::cout << "Введите имя результирующего файла: ";
                std::cin >> result;
                File51(file1, file2, file3, result);
                break;
            }
            case 4: {
                std::string expression;
                std::cout << "Введите выражение (цифры и операции + - *): ";
                std::cin >> expression;
                int result = Recur15(expression);
                std::cout << "Результат: " << result << std::endl;
                break;
            }
            case 5:
                createTestFiles();
                break;
            case 6:
                viewBinaryFiles();
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
