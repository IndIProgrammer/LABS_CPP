#include "head.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    BinaryTree tree;
    int choice;

    do {
        showMainMenu();
        choice = InputValidator::getMenuChoice(0, 5);
        handleMenuChoice(choice, tree);

    } while (choice != 0);

    return 0;
}
