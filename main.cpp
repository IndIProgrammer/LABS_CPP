#include <iostream>
#include "headler.h"

int main() {
    using namespace std;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;

    do {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
        cout << "0. Выход\n";
        cout << "1. Задача 1 - Фитнес-центр (c4)\n";
        cout << "2. Задача 2 - Ученики школы (2)\n";
        cout << "3. Задача 3 - Управление книгами (1)\n";
        cout << "Выберите задачу: ";
        cin >> choice;

        switch(choice) {
            case 1:
                solveTask1();
                break;
            case 2:
                solveTask2();
                break;
            case 3:
                solveTask3();
                break;
            case 0:
                cout << "Выход из программы...\n";
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
        }
        cout<<"./\\.../\\"<<endl;
        cout<<"(.'0..0'.)"<<endl;
        cout<<" ..=*=.."<<endl;
        cout<<"(.\\.||./.)~~**"<<endl;
        cout<<"МЯУ"<<endl;
    } while (choice != 0);

    return 0;
}
