#include <iostream>
#include <vector>
#include <string>
#include "headler.h"

int main() {
    using namespace std;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));
    int par, zad;

    cout << "=== Выберите способ написания строки ===" << endl;
    cout << "1. Случайными символами" << endl;
    cout << "2. Ввод с клавиатуры" << endl;
    cout << "3. Чтение из файла" << endl;
    cout << "4. Ввод числа для задания Str25" << endl;
    cout << "5. Ввод 16-ричного числа для задания Str29" << endl;
    cout << "6. Генератор паролей" << endl;
    cout << "7. Проверка ДЗ" << endl;
    cin >> par;
    cin.ignore();
    switch (par) {
        case 1: {
            string randomstr = generateRandomString();
            cout << "Введите номер задачи:\n";
            cout << "1 - String44"<<endl;
            cout << "2 - Str16"<<endl;
            cout << "3 - Str40"<<endl;
            cin >> zad;
            switch (zad){
                case 1: string44(randomstr); break;
                case 2: Str16(randomstr); break;
                case 3: Str40(randomstr); break;
                default:
                    cout << "Неверный номер задачи!" << endl;
                    cout << "./\\.../\\" << endl;
                    cout << "(.'0.0'.)" << endl;
                    cout << " ..=*=.." << endl;
                    cout << "(.\\.||./.)~~**" << endl;
            }
            break;
        }
        case 2: {
            cout << "Введите строку: ";
            string keyboardInput = inputFromKeyboard();
            cout << "Введите номер задачи:\n";
            cout << "1 - String44"<<endl;
            cout << "2 - Str16"<<endl;
            cout << "3 - Str40"<<endl;
            cin >> zad;
            switch (zad){
                case 1: string44(keyboardInput); break;
                case 2: Str16(keyboardInput); break;
                case 3: Str40(keyboardInput); break;
                default:
                    cout << "Неверный номер задачи!" << endl;
                    cout << "./\\.../\\" << endl;
                    cout << "(.'0.0'.)" << endl;
                    cout << " ..=*=.." << endl;
                    cout << "(.\\.||./.)~~**" << endl;
            }
            break;
        }
        case 3: {
            cout << "Укажите путь для файла: ";
            vector<string> fileLines = readFromFile();
            if (!fileLines.empty()) {
                cout << "Успешно прочитано " << fileLines.size() << " строк:" << endl;
                for (size_t i = 0; i < fileLines.size(); i++) {
                    cout << i + 1 << ". " << fileLines[i] << endl;
                }
            }
            cout << "1 - String44"<<endl;
            cout << "2 - Str16"<<endl;
            cout << "3 - Str40"<<endl;
            cin >> zad;
            switch (zad){
                case 1: string44_2(fileLines); break;
                case 2: Str16_2(fileLines); break;
                case 3: Str40_2(fileLines); break;
                default:
                    cout << "Неверный номер задачи!" << endl;
                    cout << "./\\.../\\" << endl;
                    cout << "(.'0.0'.)" << endl;
                    cout << " ..=*=.." << endl;
                    cout << "(.\\.||./.)~~**" << endl;
            }
            break;
        }
        case 4: {
            int number = inputNumberFromKeyboard();
            cout << "Введите номер задачи:\n";
            cout << "3 - Str25"<<endl;
            cin >> zad;
            if (zad == 3) {
                Str25(number);
            } else {
                cout << "Неверный номер задачи!" << endl;
            }
            break;
        }
        case 5: {
            string hexNumber = inputHexFromKeyboard();
            cout << "Введите номер задачи:\n";
            cout << "5 - Str29\n";
            cin >> zad;
            if (zad == 5) {
                hexToBinary(hexNumber);
            } else {
                cout << "Неверный номер задачи!" << endl;
            }
            break;
        }
        case 6: generatePassword(); break;
        case 7: checkMathHomework(); break;
        default:
            cout << "Неверный выбор!" << endl;
            cout << "./\\.../\\" << endl;
            cout << "(.'0.0'.)" << endl;
            cout << " ..=*=.." << endl;
            cout << "(.\\.||./.)~~**" << endl;
            return 1;
    }
    cout << "./\\.../\\" << endl;
    cout << "(.'0.0'.)" << endl;
    cout << " ..=*=.." << endl;
    cout << "(.\\.||./.)~~**" << endl;
    return 0;
}

//C:\Users\comp\CLionProjects\untitled2\test.txt
//C:\Users\comp\CLionProjects\untitled2\FN1.txt   дз файл
//C:\Users\comp\CLionProjects\untitled2\FN2.txt   проверенное дз файл
