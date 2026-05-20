#include "head.h"
// Основная функция
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));

    ExpressionTree tree;
    MenuManager menu(tree);
    menu.run();

    return 0;
}
