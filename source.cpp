#include "headler.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <map>

void string44(const std::string& str) {
    using namespace std;
    cout << "\n=== Обработка строки ===" << endl;
    cout << "Получена строка: " << str << endl;
    cout << "Длина строки: " << str.length() << endl;

    int count = 0;
    int a_count = 0;
    bool in_word = false;
    char symb = 'А';

    for (size_t i = 0; i <= str.length(); i++) {
        if (i < str.length() && str[i] != ' ') {
            in_word = true;
            if (str[i] == symb) {
                a_count++;
            }
        }
        else if (in_word) {
            if (a_count == 3) {
                count++;
            }
            a_count = 0;
            in_word = false;
        }
    }

    cout << "Количество слов с тремя 'А': " << count << endl;
}
void string44_2(const std::vector<std::string>& lines) {
    using namespace std;
    cout << "\n=== Обработка данных из файла ===" << endl;
    cout << "Получено строк: " << lines.size() << endl;

    string combined;
    for (const auto& line : lines) {
        combined += line + " ";
        cout << "Строка: " << line << endl;
    }

    string44(combined);
}

void Str16(const std::string& str) {
    using namespace std;
    cout << "\n=== Преобразование строки ===" << endl;
    cout << "Исходная строка: \"" << str << "\"" << endl;

    string result = str;

    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] == ' ') {
            result[i] = 35; // ASCII-35 = '#'
        }
    }

    result += 33; // ASCII-33 = '!'

    cout << "Преобразованная строка: \"" << result << "\"" << endl;
    cout << "Длина исходной строки: " << str.length() << endl;
    cout << "Длина преобразованной строки: " << result.length() << endl;

    cout << "\nДетали преобразования:" << endl;
    cout << "• Пробелы заменены на '#' (ASCII 35)" << endl;
    cout << "• В конец добавлен '!' (ASCII 33)" << endl;
}
void Str16_2(const std::vector<std::string>& lines) {
    using namespace std;
    cout << "\n=== Преобразование строки (данные из файла) ===" << endl;
    string combined;
    for (const auto& line : lines) {
        combined += line + " ";
    }

    if (!combined.empty() && combined.back() == ' ') {
        combined.pop_back();
    }

    Str16(combined);
}

void Str25(int number) {
    using namespace std;
    cout << "\n=== Форматирование числа с разделением на триады ===" << endl;
    cout << "Исходное число: " << number << endl;

    bool is_negative = (number < 0);
    long long abs_number = abs(static_cast<long long>(number));
    string num_str = to_string(abs_number);

    string result;
    int count = 0;

    for (int i = num_str.length() - 1; i >= 0; i--) {
        result = num_str[i] + result;
        count++;

        if (count % 3 == 0 && i > 0) {
            result = " " + result;
        }
    }
    if (is_negative) {
        result = "-" + result;
    }

    cout << "Форматированное число: " << result << endl;
    cout << "Результат (строка): \"" << result << "\"" << endl;
}

void Str40(const std::string& str) {
    using namespace std;
    cout << "\n=== Поиск уникальных символов ===" << endl;
    cout << "Исходная строка: \"" << str << "\"" << endl;
    cout << "Длина строки: " << str.length() << endl;

    map<char, int> char_count;
    for (char c : str) {
        char_count[c]++;
    }

    string unique_chars;
    for (char c : str) {
        if (char_count[c] == 1) {
            unique_chars += c;
        }
    }

    cout << "Уникальные символы (в порядке появления): \"" << unique_chars << "\"" << endl;
    cout << "Количество уникальных символов: " << unique_chars.length() << endl;

    if (unique_chars.empty()) {
        cout << "\nВ строке нет уникальных символов!" << endl;
    }
}
void Str40_2(const std::vector<std::string>& lines) {
    using namespace std;
    cout << "\n=== Поиск уникальных символов (данные из файла) ===" << endl;

    string combined;
    for (const auto& line : lines) {
        combined += line;
    }

    cout << "Объединенная строка из " << lines.size() << " строк файла" << endl;

    Str40(combined);
}

std::string hexCharToBinary(char hexChar) {
    using namespace std;
    if (hexChar >= 'a' && hexChar <= 'f') {
        hexChar = hexChar - 'a' + 'A';
    }

    switch (hexChar) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
        default: return "";
    }
}
bool isValidHex(const std::string& hexStr) {
    using namespace std;
    if (hexStr.empty()) return false;

    for (char c : hexStr) {
        // Проверяем допустимые символы: 0-9, A-F, a-f
        if (!((c >= '0' && c <= '9') ||
              (c >= 'A' && c <= 'F') ||
              (c >= 'a' && c <= 'f'))) {
            return false;
        }
    }
    return true;
}
void hexToBinary(const std::string& hexStr) {
    using namespace std;
    cout << "\n=== Перевод из шестнадцатеричной в двоичную систему ===" << endl;
    cout << "Исходное hex число: " << hexStr << endl;

    if (!isValidHex(hexStr)) {
        cout << "Ошибка: Некорректное шестнадцатеричное число!" << endl;
        return;
    }

    string binaryResult;

    for (size_t i = 0; i < hexStr.length(); i++) {
        char hexChar = hexStr[i];
        string binary4bit = hexCharToBinary(hexChar);
        binaryResult += binary4bit;
    }

    bool foundOne = false;
    string finalResult;

    for (char bit : binaryResult) {
        if (bit == '1') {
            foundOne = true;
        }
        if (foundOne) {
            finalResult += bit;
        }
    }

    if (!foundOne) {
        finalResult = "0";
    }

    cout << "Двоичное представление: " << finalResult << endl;
    cout << "Результат (строка): \"" << finalResult << "\"" << endl;

    cout << "\nДетали преобразования:" << endl;
    cout << "Hex цифра | Двоичное (4 бита)" << endl;
    cout << "----------|------------------" << endl;

    for (size_t i = 0; i < hexStr.length(); i++) {
        char hexChar = hexStr[i];
        char upperChar = hexChar;
        if (hexChar >= 'a' && hexChar <= 'f') {
            upperChar = hexChar - 'a' + 'A';
        }

        cout << "    " << upperChar << "     |    " << hexCharToBinary(hexChar) << endl;
    }

    cout << "Общая длина: " << finalResult.length() << " бит" << endl;
}

void generatePassword() {
    using namespace std;
    cout << "\n=== ГЕНЕРАТОР ПАРОЛЕЙ ===" << endl;

    const string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    const string symbols = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    int level;
    cout << "Выберите уровень сложности пароля:" << endl;
    cout << "1 - Простой (8 символов, только буквы)" << endl;
    cout << "2 - Средний (12 символов, буквы + цифры)" << endl;
    cout << "3 - Сложный (16 символов, буквы + цифры + символы)" << endl;
    cin >> level;

    int length;
    string charPool;
    string description;

    switch (level) {
        case 1:
            length = 8;
            charPool = lowercase + uppercase;
            description = "Простой (только буквы)";
            break;
        case 2:
            length = 12;
            charPool = lowercase + uppercase + digits;
            description = "Средний (буквы + цифры)";
            break;
        case 3:
            length = 16;
            charPool = lowercase + uppercase + digits + symbols;
            description = "Сложный (буквы + цифры + символы)";
            break;
        default:
            cout << "Неверный выбор! Используется уровень по умолчанию (Средний)" << endl;
            length = 12;
            charPool = lowercase + uppercase + digits;
            description = "Средний (буквы + цифры)";
            break;
    }

    string password;
    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % charPool.length();
        password += charPool[randomIndex];
    }

    cout << "\n--- РЕЗУЛЬТАТ ГЕНЕРАЦИИ ---" << endl;
    cout << "Уровень: " << description << endl;
    cout << "Длина: " << length << " символов" << endl;
    cout << "Пароль: " << password << endl;
    cout << "Результат (строка): \"" << password << "\"" << endl;

    cout << "\n--- АНАЛИЗ ПАРОЛЯ ---" << endl;

    int lowerCount = 0, upperCount = 0, digitCount = 0, symbolCount = 0;
    for (char c : password) {
        if (c >= 'a' && c <= 'z') lowerCount++;
        else if (c >= 'A' && c <= 'Z') upperCount++;
        else if (c >= '0' && c <= '9') digitCount++;
        else symbolCount++;
    }

    cout << "Строчные буквы: " << lowerCount << endl;
    cout << "Прописные буквы: " << upperCount << endl;
    cout << "Цифры: " << digitCount << endl;
    cout << "Символы: " << symbolCount << endl;

    cout << "\n--- ОЦЕНКА НАДЕЖНОСТИ ---" << endl;
    if (level >= 3 && symbolCount > 0 && digitCount > 0 && lowerCount > 0 && upperCount > 0) {
        cout << "Отличный пароль! Высокая надежность" << endl;
    } else if (level >= 2 && digitCount > 0 && (lowerCount > 0 || upperCount > 0)) {
        cout << "Хороший пароль! Средняя надежность" << endl;
    } else {
        cout << "Простой пароль! Рекомендуется использовать более сложный уровень" << endl;
    }
}

void checkMathHomework() {
    using namespace std;
    string inputFile, outputFile;

    cout << "Укажите путь к файлу который надо проверить: ";
    getline(cin, inputFile);
    cout << "Укажите путь к фалу куда нужно записать ответ: ";
    getline(cin, outputFile);

    ifstream in(inputFile);
    ofstream out(outputFile);

    if (!in.is_open() || !out.is_open()) {
        cout << "Ошибка открытия файлов!" << endl;
        return;
    }

    string line;
    int correct = 0, total = 0;

    while (getline(in, line)) {
        if (line.empty()) continue;

        total++;

        size_t mult = line.find('*');
        size_t div = line.find(':');
        size_t eq = line.find('=');

        if (eq == string::npos) {
            out << line << " !" << endl;
            continue;
        }

        char op = (mult != string::npos && mult < eq) ? '*' : ':';
        size_t opPos = (op == '*') ? mult : div;

        if (opPos == string::npos || opPos >= eq) {
            out << line << " !" << endl;
            continue;
        }

        int a = stoi(line.substr(0, opPos));
        int b = stoi(line.substr(opPos + 1, eq - opPos - 1));
        int studentAns = stoi(line.substr(eq + 1));

        int correctAns = (op == '*') ? a * b : a / b;

        if (studentAns == correctAns && (op != ':' || b != 0) && (op != ':' || a % b == 0)) {
            out << line << endl;
            correct++;
        } else {
            out << line << " !" << endl;
        }
    }

    in.close();
    out.close();

    cout << "Проверено: " << total << " примеров" << endl;
    cout << "Решено правильно: " << correct << endl;
    cout << "Результат находится в файле: " << outputFile << endl;
}
