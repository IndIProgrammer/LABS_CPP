#include <iostream>
#include "head.h"

int main() {
    using namespace std;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    do {
        show_main_menu();
        cin >> choice;

        switch (choice) {
            case 1:
                run_task1();
                break;
            case 2:
                run_task2();
                break;
            case 3:
                run_task3();
                break;
            case 0:
                cout << "\nВыход из программы.\n";
                break;
            default:
                cout << "\nНеверный выбор! Попробуйте снова.\n";
                cout << "Нажмите Enter для продолжения...";
                cin.ignore(1000, '\n');
                cin.get();
                break;
        }
        cout<<"./\\.../\\"<<endl;
        cout<<"(.'0..0'.)"<<endl;
        cout<<" ..=*=.."<<endl;
        cout<<"(.\\.||./.)~~**"<<endl;
        cout<<"МЯУ"<<endl;
    } while (choice != 0);
    return 0;
}
