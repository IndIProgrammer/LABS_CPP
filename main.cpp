#include "head.h"

// Главная функция
int main() {
    // Настройка консоли на кодировку Windows-1251
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MenuManager menu;
    menu.run();

    return 0;
}
