#include "headler.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

std::string generateRandomString() {
    using namespace std;
    string chars = "QWERTYUIOPASDFGHJKLZXCVBNM 0123456789јЅ¬√ƒ≈®∆«» ЋћЌќѕ–—“”‘’÷„Ўў№ЏџЁёя,./|<>?:;[]{}()*-+=&^%$#@!~`";
    int length = rand() % 300;

    string result;
    for (int i = 0; i < length; ++i) {
        result += chars[rand() % chars.length()];
    }

    return result;
}
std::vector<std::string> readFromFile() {
    using namespace std;
    vector<string> lines;

    string filename;
    getline(cin, filename);

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                lines.push_back(line);
            }
        }
        file.close();
        cout << "‘айл '" << filename << "' успешно прочитан!" << endl;
    } else {
        cout << "ќшибка: Ќе удалось открыть файл '" << filename << "'" << endl;
    }

    return lines;
}
std::string inputFromKeyboard() {
    using namespace std;
    string input;
    getline(cin, input);
    return input;
}
int inputNumberFromKeyboard() {
    using namespace std;
    int number;
    cout << "¬ведите целое число: ";
    cin >> number;
    cin.ignore(); // ќчищаем буфер
    return number;
}
std::string inputHexFromKeyboard() {
    using namespace std;
    string hex;
    cout << "¬ведите шестнадцатеричное число: ";
    cin>>hex;
    return hex;
}