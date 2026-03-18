#include "head.h"

// Главная функция
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    LinkedListTwo list;
    int choice;
    std::string filename;

    do {
        std::cout << "\n=== МЕНЮ ===\n";
        std::cout << "1. Заполнить список из файла\n";
        std::cout << "2. Заполнить список случайными числами\n";
        std::cout << "3. Заполнить список с клавиатуры\n";  // Новый пункт
        std::cout << "4. Вывести список (прямой порядок)\n";
        std::cout << "5. Вывести список (обратный порядок)\n";
        std::cout << "6. Вывести элементы между мин и макс (задача 41)\n";
        std::cout << "7. Сохранить в обратном порядке в файл с удалением (задача 63)\n";
        std::cout << "8. Проверить строку на симметричность (задача 4)\n";
        std::cout << "9. Преобразовать в циклический список с барьером (задача 46)\n";
        std::cout << "10. Вывести в файл с шагом k и удалить (задача 69)\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";

        // Обработка ввода с проверкой на ошибки
        std::string input;
        std::getline(std::cin, input);

        // Проверяем, является ли ввод числом
        bool isValidNumber = true;
        for (char c : input) {
            if (!isdigit(c) && c != '-') {
                isValidNumber = false;
                break;
            }
        }

        if (!isValidNumber || input.empty()) {
            std::cout << "Ошибка: введите число!" << std::endl;
            continue; // Возвращаемся в начало цикла
        }

        // Преобразуем строку в число
        choice = std::stoi(input);

        switch (choice) {
            case 1:
                std::cout << "Введите имя файла: ";
                std::getline(std::cin, filename);
                list.fillFromFile(filename);
                break;

            case 2: {
                int count = LinkedListTwo::getValidatedInt("Введите количество элементов: ", 1, 100);
                list.fillRandom(count);
                break;
            }

            case 3:  // Новый случай
                list.fillFromKeyboard();
                break;

            case 4:
                list.print();
                break;

            case 5:
                list.printReverse();
                break;

            case 6:
                list.printBetweenMinAndMax();
                break;

            case 7:
                std::cout << "Введите имя файла для сохранения: ";
                std::getline(std::cin, filename);
                list.saveReverseToFileAndClear(filename);
                break;

            case 8: {
                std::string str;
                std::cout << "Введите строку для проверки: ";
                std::getline(std::cin, str);

                if (LinkedListTwo::isStringSymmetric(str)) {
                    std::cout << "Строка \"" << str << "\" симметрична" << std::endl;
                } else {
                    std::cout << "Строка \"" << str << "\" не симметрична" << std::endl;
                }
                break;
            }

            case 9: {
                Node* barrier = list.transformToCircularWithBarrier();
                std::cout << "Указатель на барьерный элемент: " << barrier << std::endl;
                break;
            }

            case 10: {
                if (list.getHead() == nullptr) {
                    std::cout << "Список пуст! Сначала заполните его." << std::endl;
                    break;
                }

                std::cout << "Введите имя файла для сохранения: ";
                std::getline(std::cin, filename);

                int k = LinkedListTwo::getValidatedInt("Введите шаг k (целое положительное число): ", 1, 100);
                list.saveWithStepToFileAndRemove(filename, k);
                break;
            }

            case 0:
                std::cout << "Программа завершена." << std::endl;
                break;

            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
