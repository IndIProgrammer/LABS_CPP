#include "head.h"

void showMenu() {
    std::cout << "\nГЛАВНОЕ МЕНЮ\n";
    std::cout << "1. STL3Alg3 Удалить первый и последний нулевой элемент списка\n";
    std::cout << "2. STL3Alg19 Добавить в начало дека 1..N, в конец N..1\n";
    std::cout << "3. STL3Alg47 Сортировка вектора (первая половина отсортирована)\n";
    std::cout << "4. STL3Alg61 Создать дек строк по парам соседних слов\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите задание: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::list<int> listForAlg3;
    std::deque<int> dequeForAlg19;
    std::vector<int> vectorForAlg47;
    std::list<std::string> listForAlg61;
    std::deque<std::string> dequeForAlg61;

    int choice;

    do {
        showMenu();
        choice = getIntInput("", 0, 4);

        switch (choice) {
            case 1: {
                std::cout << "\nSTL3Alg3 Удалить первый и последний нулевой элемент списка\n";
                fillListMenu(listForAlg3);
                if (!listForAlg3.empty()) {
                    std::cout << "Исходный список: ";
                    printList(listForAlg3, "L");
                    solveAlg3(listForAlg3);
                    std::cout << "Результат: ";
                    printList(listForAlg3, "L");
                }
                break;
            }

            case 2: {
                std::cout << "\nSTL3Alg19 Добавить в начало дека 1..N, в конец N..1\n";
                int N = getPositiveIntInput("Введите N (> 0): ");
                dequeForAlg19.clear();
                std::cout << "Исходный дек (пустой): ";
                printIntDeque(dequeForAlg19, "D");
                solveAlg19(dequeForAlg19, N);
                std::cout << "Результат: ";
                printIntDeque(dequeForAlg19, "D");
                break;
            }

            case 3: {
                std::cout << "\nSTL3Alg47 Сортировка вектора (первая половина отсортирована)\n";
                fillVectorMenu(vectorForAlg47);

                if (vectorForAlg47.empty()) {
                    std::cout << "Вектор пуст. Операция отменена.\n";
                    break;
                }

                if (vectorForAlg47.size() % 2 != 0) {
                    std::cout << "Вектор должен иметь чётное количество элементов. Добавляем элемент (0).\n";
                    vectorForAlg47.push_back(0);
                }

                size_t mid = vectorForAlg47.size() / 2;
                std::sort(vectorForAlg47.begin(), vectorForAlg47.begin() + mid);
                std::cout << "Первая половина отсортирована: ";
                printVector(vectorForAlg47, "V");

                solveAlg47(vectorForAlg47);
                break;
            }

            case 4: {
                std::cout << "\nSTL3Alg61 Создать дек строк по парам соседних слов\n";
                fillStringListMenu(listForAlg61);

                if (listForAlg61.size() < 2) {
                    std::cout << "Список должен содержать минимум 2 элемента для выполнения операции.\n";
                    break;
                }

                std::cout << "Исходный список: ";
                printStringList(listForAlg61, "L");

                solveAlg61(listForAlg61, dequeForAlg61);
                std::cout << "Результат (дек): ";
                printStringDeque(dequeForAlg61, "D");
                break;
            }

            case 0:
                std::cout << "Выход из программы.\n";
                break;

            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }

    } while (choice != 0);

    return 0;
}
