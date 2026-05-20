#include "head.h"
// Основная функция
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(nullptr));  // Инициализация генератора случайных чисел
    MenuManager menu;
    menu.run();
    return 0;
}
