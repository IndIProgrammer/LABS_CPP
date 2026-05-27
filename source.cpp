#include "head.h"

// КЛАСС ПРОВЕРОК

// Очистка буфера ввода
void Validator::clearInputBuffer() {
    if (std::cin.fail()) {
        std::cin.clear();
    }
    while (std::cin.get() != '\n') {
        continue;
    }
}

// Проверка на целые числа
int Validator::getIntInput(int min, int max, const std::string& prompt) {
    std::string input;
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        bool valid = true;
        size_t start = 0;
        if (input[0] == '+') start = 1;

        for (size_t i = start; i < input.length(); ++i) {
            if (input[i] < '0' || input[i] > '9') {
                valid = false;
                break;
            }
        }

        if (valid && !input.empty()) {
            int temp = 0;
            for (size_t i = start; i < input.length(); ++i) {
                temp = temp * 10 + (input[i] - '0');
            }
            value = temp;
            if (value >= min && value <= max) {
                clearInputBuffer();
                return value;
            }
        }
        std::cout << "Некорректный ввод. Повторите попытку.\n";
        clearInputBuffer();
    }
}

// Проверка строк
std::string Validator::getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

// Существование файла
bool Validator::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Получение строки из файла
std::string Validator::getFileString(const std::string& filename) {
    std::ifstream file(filename);
    std::string content = "";
    if (file.is_open()) {
        std::getline(file, content);
        file.close();
    }
    return content;
}

// КОД ХЭММИНГА

// Проверка на степень двойки
bool Hamming::isPowerOfTwo(int n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

// Расчет минимального кол-ва контрольных разрядов
int Hamming::calcParityBitsCount(int m) {
    int r = 0;
    while (std::pow(2, r) < m + r + 1) {
        r++;
    }
    return r;
}

// Создает закодированное сообщение
std::vector<int> Hamming::encode(const std::vector<int>& dataBits, int r) {
    int n = dataBits.size() + r;
    std::vector<int> encoded(n + 1, 0);
    int j = 0;

    for (int i = 1; i <= n; i++) {
        if (!isPowerOfTwo(i)) encoded[i] = dataBits[j++];
    }

    std::cout << "\n--- Расчет контрольных разрядов ---" << std::endl;
    for (int i = 0; i < r; i++) {
        int parityPos = std::pow(2, i);
        int parity = 0;
        std::cout << "Контрольный разряд P" << parityPos << " (позиция " << parityPos << "): ";

        for (int k = 1; k <= n; k++) {
            if ((k & parityPos) != 0 && k != parityPos) {
                parity ^= encoded[k];
                std::cout << (encoded[k] ? "1" : "0") << " ";
            }
        }
        encoded[parityPos] = parity;
        std::cout << "=> XOR = " << parity << std::endl;
    }
    return encoded;
}

// Вычисление синдромов для контрольных разрядов
int Hamming::getSyndrome(const std::vector<int>& encoded, int r) {
    int syndrome = 0;
    std::cout << "\n--- Расчет синдрома (проверка контрольных разрядов) ---" << std::endl;
    for (int i = 0; i < r; i++) {
        int parityPos = std::pow(2, i);
        int parity = 0;
        std::cout << "Проверка для P" << parityPos << " (позиция " << parityPos << "): ";

        for (size_t k = 1; k < encoded.size(); k++) {
            if ((k & parityPos) != 0) {
                parity ^= encoded[k];
                std::cout << encoded[k] << " ";
            }
        }

        if (parity != 0) {
            syndrome += parityPos;
            std::cout << "=> XOR = " << parity << " (Ошибка в этой группе)" << std::endl;
        } else {
            std::cout << "=> XOR = " << parity << " (OK)" << std::endl;
        }
    }
    return syndrome;
}

// Выполнение задачи
void Hamming::runTask(const std::string& inputStr) {
    std::vector<int> dataBits;
    for (char c : inputStr) {
        if (c == '0' || c == '1') {
            dataBits.push_back(c - '0');
        }
    }

    int m = dataBits.size();
    if (m == 0) {
        std::cout << "Пустое или недопустимое сообщение.\n";
        return;
    }

    int r = calcParityBitsCount(m);
    std::vector<int> encoded = encode(dataBits, r);

    std::cout << "\nЗакодированное сообщение с контрольными битами: ";
    for (size_t i = 1; i < encoded.size(); i++) {
        std::cout << encoded[i];
    }
    std::cout << "\n";

    int errorPos = Validator::getIntInput(0, encoded.size() - 1, "Введите номер бита для имитации ошибки (0 для пропуска): ");

    if (errorPos > 0) {
        encoded[errorPos] ^= 1;
        std::cout << "Сообщение после внесения ошибки: ";
        for (size_t i = 1; i < encoded.size(); i++) std::cout << encoded[i];
        std::cout << "\n";
    }

    int syndrome = getSyndrome(encoded, r);
    std::cout << "Вычисленный синдром: " << syndrome << "\n";

    if (syndrome == 0) {
        std::cout << "Ошибок не обнаружено.\n";
    } else {
        std::cout << "Обнаружена одиночная ошибка в бите номер: " << syndrome << "\n";
        encoded[syndrome] ^= 1;
        std::cout << "Исправленное сообщение: ";
        for (size_t i = 1; i < encoded.size(); i++) std::cout << encoded[i];
        std::cout << "\n";
    }
}

// УЗЕЛ ДЛЯ ХАФФМАНА

// Конструктор и геттеры, сеттеры
HuffmanNode::HuffmanNode(std::string d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
std::string HuffmanNode::getData() const { return data; }
int HuffmanNode::getFreq() const { return freq; }
HuffmanNode* HuffmanNode::getLeft() const { return left; }
HuffmanNode* HuffmanNode::getRight() const { return right; }
void HuffmanNode::setLeft(HuffmanNode* l) { left = l; }
void HuffmanNode::setRight(HuffmanNode* r) { right = r; }

// Проверка на лист
bool HuffmanNode::isLeaf() const { return !left && !right; }

// Функтор для сравнения узлов дерева Хаффмана
bool CompareNodes::operator()(HuffmanNode* l, HuffmanNode* r) {
    return l->getFreq() > r->getFreq();
}

// КОД ХАФФМАНА

// Генерация кодовых слов для букв
void Huffman::generateCodes(HuffmanNode* root, const std::string& str, std::map<std::string, std::string>& huffmanCode) {
    if (!root) return;
    if (root->isLeaf()) huffmanCode[root->getData()] = str;
    generateCodes(root->getLeft(), str + "0", huffmanCode);
    generateCodes(root->getRight(), str + "1", huffmanCode);
}

// Удаление дерева
void Huffman::destroyTree(HuffmanNode* root) {
    if (!root) return;
    destroyTree(root->getLeft());
    destroyTree(root->getRight());
    delete root;
}

// Вывод дерева боком
void Huffman::printTreeSideways(HuffmanNode* node, int level, std::ostream& out, std::string path) {
    if (!node) return;

    // Сначала идем вправо (для отображения дерева "боком")
    printTreeSideways(node->getRight(), level + 1, out, path + "1");

    // Вывод отступов
    for (int i = 0; i < level * 4; i++) out << " ";

    // Вывод узла
    if (node->isLeaf()) {
        out << "[" << node->getData() << ":" << path << "]" << std::endl;
    } else {
        // Выводим бит, пришедший к этому узлу, если это не корень
        if (level == 0) out << "[01]" << std::endl;
        else out << "(" << path.back() << ")" << std::endl;
    }

    // Идем влево
    printTreeSideways(node->getLeft(), level + 1, out, path + "0");
}

// Выполнение задачи
void Huffman::runTask(const std::string& text) {
    if (text.empty()) return;

    std::map<std::string, int> freqMap;
    for (char c : text) {
        std::string s(1, c);
        freqMap[s]++;
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;
    for (auto pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        int sum = left->getFreq() + right->getFreq();
        HuffmanNode* parent = new HuffmanNode("", sum);
        parent->setLeft(left);
        parent->setRight(right);
        pq.push(parent);
    }

    HuffmanNode* root = pq.top();
    std::map<std::string, std::string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    std::cout << "\nКоды Хаффмана для символов:\n";
    for (auto pair : huffmanCode) {
        std::cout << "'" << pair.first << "' : " << pair.second << "\n";
    }

    std::cout << "\nДерево кодирования:\n";
    printTreeSideways(root, 0, std::cout);

    int uniformBitsPerChar = 0;
    while (std::pow(2, uniformBitsPerChar) < freqMap.size()) {
        uniformBitsPerChar++;
    }
    int uniformSize = text.length() * uniformBitsPerChar;

    int huffmanSize = 0;
    for (char c : text) {
        std::string s(1, c);
        huffmanSize += huffmanCode[s].length();
    }

    std::cout << "\nРазмер при равномерном кодировании: " << uniformSize << " бит\n";
    std::cout << "Размер при кодировании Хаффмана: " << huffmanSize << " бит\n";

    destroyTree(root);
}

// СТОЛБЧАТЫЙ ШИФР ТРАНСПОНИРОВАНИЯ

// Вычисляет порядок считывания столбцов на основе алфавитной сортировки ключа
std::vector<int> ColumnarCipher::getOrder(const std::string& key) {
    std::vector<int> order(key.length());

    // Создаем пары {буква, исходный_индекс}.
    std::vector<std::pair<char, int>> keyChars;
    for (size_t i = 0; i < key.length(); i++) {
        keyChars.push_back({key[i], i});
    }

    // Сортировка по алфавиту
    for (size_t i = 0; i < keyChars.size(); i++) {
        for (size_t j = i + 1; j < keyChars.size(); j++) {
            if (keyChars[j].first < keyChars[i].first) {
                std::swap(keyChars[i], keyChars[j]);
            }
        }
    }
    for (size_t i = 0; i < keyChars.size(); i++) {
        order[keyChars[i].second] = i;
    }
    return order;
}

// Шифрование
std::string ColumnarCipher::encrypt(const std::string& text, const std::string& key) {
    int cols = key.length();

    // Создаем контейнер для столбцов таблицы.
    std::vector<std::string> grid(cols, "");

    // Создаем таблицу и расставляем символы по япо строкам
    for (size_t i = 0; i < text.length(); i++) {
        grid[i % cols] += text[i];
    }

    std::vector<int> order = getOrder(key);
    std::string result = "";

    // Считываем столбцы в порядке ключа
    for (int currOrder = 0; currOrder < cols; currOrder++) {
        for (int i = 0; i < cols; i++) {
            if (order[i] == currOrder) {
                result += grid[i];
                break;
            }
        }
    }
    return result;
}

// Дешифрование
std::string ColumnarCipher::decrypt(const std::string& text, const std::string& key) {
    int cols = key.length();
    // Вычисляем количество строк, необходимых для размещения текста.
    int rows = std::ceil((double)text.length() / cols);

    int extraChars = text.length() % cols;
    if (extraChars == 0) extraChars = cols;

    std::vector<int> order = getOrder(key);
    std::vector<std::string> grid(cols, "");

    // Восстанавливаем столбцы из зашифрованного текста в правильном порядке
    int textIdx = 0;
    for (int currOrder = 0; currOrder < cols; currOrder++) {
        for (int i = 0; i < cols; i++) {
            if (order[i] == currOrder) {
                // Длина текущего столбца
                int colLen = (i < extraChars) ? rows : rows - 1;
                grid[i] = text.substr(textIdx, colLen);
                textIdx += colLen;
                break;
            }
        }
    }

    // Читаем сетку построчно (строка за строкой), чтобы получить исходный текст
    std::string result = "";
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            // Проверяем, существует ли символ в данной ячейке (для неполных строк)
            if (r < (int)grid[c].length()) {
                result += grid[c][r];
            }
        }
    }
    return result;
}

// Выполнение задачи
void ColumnarCipher::runTask(const std::string& text, const std::string& key) {
    std::cout << "Исходный текст: " << text << "\n";
    std::cout << "Ключ: " << key << "\n";

    std::string enc = encrypt(text, key);
    std::cout << "\nЗашифрованный текст: " << enc << "\n";

    std::string dec = decrypt(enc, key);
    std::cout << "Расшифрованный текст: " << dec << "\n";
}

// КЛАСС МЕНЮ
MenuManager::MenuManager() {}

void MenuManager::showMainMenu() {
    std::cout << "\nГЛАВНОЕ МЕНЮ\n";
    std::cout << "1. Задача 1 (Код Хемминга)\n";
    std::cout << "2. Задача 2 (Код Хаффмана)\n";
    std::cout << "3. Задача 3 (Столбчатый шифр)\n";
    std::cout << "0. Выход\n";
}

void MenuManager::task1Menu() {
    int choice = Validator::getIntInput(1, 2, "1. Ввод с клавиатуры\n2. Чтение из файла inputForHam.txt\nВыберите вариант: ");
    std::string msg;
    if (choice == 1) {
        msg = Validator::getStringInput("Введите двоичное сообщение: ");
    } else {
        std::string filename = "inputForHam.txt";
        if (Validator::fileExists(filename)) {
            msg = Validator::getFileString(filename);
        } else {
            std::cout << "Файл inputForHam.txt не найден.\n";
            return;
        }
    }
    Hamming task;
    task.runTask(msg);
}

void MenuManager::task2Menu() {
    int choice = Validator::getIntInput(1, 2, "1. Ввод с клавиатуры\n2. Чтение из файла inputForHaf.txt\nВыберите вариант: ");
    std::string msg;
    if (choice == 1) {
        msg = Validator::getStringInput("Введите текст для кодирования: ");
    } else {
        std::string filename = "inputForHaf.txt";
        if (Validator::fileExists(filename)) {
            msg = Validator::getFileString(filename);
        } else {
            std::cout << "Файл inputForHaf.txt не найден.\n";
            return;
        }
    }
    Huffman task;
    task.runTask(msg);
}

void MenuManager::task3Menu() {
    int choice = Validator::getIntInput(1, 2, "1. Ввод с клавиатуры\n2. Чтение из файла inputForCipher.txt\nВыберите вариант: ");
    std::string msg, key;
    if (choice == 1) {
        msg = Validator::getStringInput("Введите исходный текст: ");
        key = Validator::getStringInput("Введите ключевое слово: ");
    } else {
        std::string filename = "inputForCipher.txt";
        if (Validator::fileExists(filename)) {
            msg = Validator::getFileString(filename);
            key = Validator::getStringInput("Введите ключевое слово вручную: ");
        } else {
            std::cout << "Файл inputForCipher.txt не найден.\n";
            return;
        }
    }
    ColumnarCipher task;
    task.runTask(msg, key);
}

void MenuManager::run() {
    int choice = -1;
    while (choice != 0) {
        showMainMenu();
        choice = Validator::getIntInput(0, 3, "Выберите пункт меню: ");
        if (choice == 1) task1Menu();
        else if (choice == 2) task2Menu();
        else if (choice == 3) task3Menu();
    }
}
