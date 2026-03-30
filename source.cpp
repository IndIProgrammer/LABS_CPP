#include "head.h"

// Реализация безопасного ввода целого числа
int safeGetInt(const std::string& prompt) {
    int value;
    if (!prompt.empty()) {
        std::cout << prompt;
    }
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка! Введите целое число: ";
    }
    return value;
}

// Безопасное получение положительного целого числа
int safeGetPositiveInt(const std::string& prompt) {
    int value;
    do {
        value = safeGetInt(prompt);
        if (value <= 0) {
            std::cout << "Ошибка! Число должно быть положительным.\n";
        }
    } while (value <= 0);
    return value;
}

// Безопасное получение выбора меню
int safeGetMenuChoice(int min, int max) {
    int choice;
    do {
        choice = safeGetInt();
        if (choice < min || choice > max) {
            std::cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
        }
    } while (choice < min || choice > max);
    return choice;
}

// Заполнение вектора с клавиатуры
void fillVectorFromKeyboard(std::vector<int>& vec, const std::string& name) {
    int n = safeGetPositiveInt("Введите количество элементов вектора " + name + ": ");

    vec.clear();
    std::cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; i++) {
        int val;
        while (!(std::cin >> val)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите целое число: ";
        }
        vec.push_back(val);
    }
}

// Заполнение вектора случайными числами
void fillVectorRandom(std::vector<int>& vec, int size, int minVal, int maxVal) {
    vec.clear();
    if (minVal > maxVal) {
        std::swap(minVal, maxVal);
    }
    for (int i = 0; i < size; i++) {
        vec.push_back(minVal + rand() % (maxVal - minVal + 1));
    }
}

// Заполнение вектора из файла input.txt
void fillVectorFromFile(std::vector<int>& vec) {
    const std::string filename = "input.txt";
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
        std::cout << "Создайте файл " << filename << " в папке с программой\n";
        return;
    }

    vec.clear();
    int val;
    while (file >> val) {
        vec.push_back(val);
    }
    file.close();

    if (vec.empty()) {
        std::cout << "Файл пуст или содержит некорректные данные\n";
    } else {
        std::cout << "Загружено " << vec.size() << " элементов из файла " << filename << std::endl;
    }
}

// Заполнение строкового вектора с клавиатуры
void fillStringVectorFromKeyboard(std::vector<std::string>& vec, const std::string& name) {
    int n = safeGetPositiveInt("Введите количество элементов вектора " + name + ": ");

    vec.clear();
    std::cout << "Введите " << n << " слов (заглавными буквами): ";
    for (int i = 0; i < n; i++) {
        std::string word;
        while (!(std::cin >> word)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите слово: ";
        }
        // Преобразование в заглавные буквы
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        vec.push_back(word);
    }
}

// Заполнение строкового вектора случайными словами
void fillStringVectorRandom(std::vector<std::string>& vec, int size) {
    vec.clear();
    const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < size; i++) {
        int wordLen = 3 + rand() % 8;
        std::string word;
        for (int j = 0; j < wordLen; j++) {
            word += letters[rand() % letters.length()];
        }
        vec.push_back(word);
    }
}

// Заполнение строкового вектора из файла input_words.txt
void fillStringVectorFromFile(std::vector<std::string>& vec) {
    const std::string filename = "input_words.txt";
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
        std::cout << "Создайте файл " << filename << " в папке с программой\n";
        return;
    }

    vec.clear();
    std::string word;
    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        vec.push_back(word);
    }
    file.close();

    if (vec.empty()) {
        std::cout << "Файл пуст или содержит некорректные данные\n";
    } else {
        std::cout << "Загружено " << vec.size() << " слов из файла " << filename << std::endl;
    }
}

// Заполнение векторов для задачи 3
void fillVectorsSet(std::vector<int>& V0, std::vector<std::vector<int>>& Vn) {
    std::cout << "\nЗаполнение данных для задачи 3\n";

    std::cout << "Заполнение V0:\n";
    std::cout << "1. С клавиатуры\n2. Случайными числами\n3. Из файла (input.txt)\n";
    int choice = safeGetMenuChoice(1, 3);

    switch(choice) {
        case 1:
            fillVectorFromKeyboard(V0, "V0");
            break;
        case 2: {
            int size = safeGetPositiveInt("Введите размер: ");
            int minVal = safeGetInt("Введите min значение: ");
            int maxVal = safeGetInt("Введите max значение: ");
            fillVectorRandom(V0, size, minVal, maxVal);
            std::cout << "Сгенерировано " << size << " случайных чисел\n";
            break;
        }
        case 3:
            fillVectorFromFile(V0);
            break;
    }

    int N = safeGetPositiveInt("\nВведите количество векторов V1...VN: ");

    Vn.clear();
    Vn.resize(N);

    for (int i = 0; i < N; i++) {
        std::cout << "\nЗаполнение V" << i+1 << ":\n";
        std::cout << "1. С клавиатуры\n2. Случайными числами\n3. Из файла (input.txt)\n";
        choice = safeGetMenuChoice(1, 3);

        switch(choice) {
            case 1:
                fillVectorFromKeyboard(Vn[i], "V" + std::to_string(i+1));
                break;
            case 2: {
                int size = safeGetPositiveInt("Введите размер: ");
                int minVal = safeGetInt("Введите min значение: ");
                int maxVal = safeGetInt("Введите max значение: ");
                fillVectorRandom(Vn[i], size, minVal, maxVal);
                std::cout << "Сгенерировано " << size << " случайных чисел\n";
                break;
            }
            case 3:
                fillVectorFromFile(Vn[i]);
                break;
        }
    }
}

// Заполнение векторов для задачи 15
void fillVectorsForMap(std::vector<int>& V) {
    std::cout << "\nЗаполнение данных для задачи 15\n";
    std::cout << "Заполнение вектора V:\n";
    std::cout << "1. С клавиатуры\n2. Случайными числами\n3. Из файла (input.txt)\n";
    int choice = safeGetMenuChoice(1, 3);

    switch(choice) {
        case 1:
            fillVectorFromKeyboard(V, "V");
            break;
        case 2: {
            int size = safeGetPositiveInt("Введите размер: ");
            int minVal = safeGetInt("Введите min значение: ");
            int maxVal = safeGetInt("Введите max значение: ");
            fillVectorRandom(V, size, minVal, maxVal);
            std::cout << "Сгенерировано " << size << " случайных чисел\n";
            break;
        }
        case 3:
            fillVectorFromFile(V);
            break;
    }
}

// Заполнение векторов для задачи 22
void fillVectorsForMultimap(std::vector<std::string>& Vwords) {
    std::cout << "\nЗаполнение данных для задачи 22\n";
    std::cout << "Заполнение вектора слов:\n";
    std::cout << "1. С клавиатуры\n2. Случайными словами\n3. Из файла (input.txt)\n";
    int choice = safeGetMenuChoice(1, 3);

    switch(choice) {
        case 1:
            fillStringVectorFromKeyboard(Vwords, "V");
            break;
        case 2: {
            int size = safeGetPositiveInt("Введите количество слов: ");
            fillStringVectorRandom(Vwords, size);
            std::cout << "Сгенерировано " << size << " случайных слов\n";
            break;
        }
        case 3:
            fillStringVectorFromFile(Vwords);
            break;
    }
}

// Задачи STL5Assoc3
void taskSTL5Assoc3(const std::vector<int>& V0, const std::vector<std::vector<int>>& Vn) {
    std::cout << "\nЗадача STL5Assoc3\n";

    if (V0.empty()) {
        std::cout << "Вектор V0 пуст! Невозможно выполнить задачу.\n";
        return;
    }

    std::cout << "V0: ";
    for (std::vector<int>::const_iterator it = V0.begin(); it != V0.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::multiset<int> msV0(V0.begin(), V0.end()); // мультимножество V0

    int count = 0;
    for (size_t i = 0; i < Vn.size(); i++) {
        if (Vn[i].empty()) {
            std::cout << "V" << i+1 << " пуст, пропускаем\n";
            continue;
        }

        std::multiset<int> msVn(Vn[i].begin(), Vn[i].end()); // мультимножество n-ого вектора

        if (std::includes(msVn.begin(), msVn.end(), msV0.begin(), msV0.end())) { // проверка содержит ли n-ый диапазон все эл-ы V0 с учетом повторений
            count++;
            std::cout << "V" << i+1 << " содержит все элементы V0 (с учетом повторений)\n";
        } else {
            std::cout << "V" << i+1 << " НЕ содержит все элементы V0 (с учетом повторений)\n";
        }
    }

    std::cout << "\nКоличество векторов, содержащих все элементы V0: " << count << std::endl;
}

// Задачи STL5Assoc15
void taskSTL5Assoc15(const std::vector<int>& V) {
    std::cout << "\nЗадача STL5Assoc15\n";

    if (V.empty()) {
        std::cout << "Вектор V пуст! Невозможно выполнить задачу.\n";
        return;
    }

    std::cout << "Вектор V: ";
    for (std::vector<int>::const_iterator it = V.begin(); it != V.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::map<int, int> M; // словарь (ключ(first) - значение(second))

    for (std::vector<int>::const_iterator it = V.begin(); it != V.end(); ++it) {
        M[*it]++; // [] если ключа с *it нет то создает его и инициализирует значение нулём
    }

    std::cout << "\nРезультат (элемент -> количество повторений):\n";
    for (std::map<int, int>::const_iterator it = M.begin(); it != M.end(); ++it) {
        std::cout << it->first << " -> " << it->second << std::endl; //first - сам элемент, second - кол-во повторений
    }
}

// Задачи STL5Assoc22
void taskSTL5Assoc22(const std::vector<std::string>& Vwords) {
    std::cout << "\nЗадача STL5Assoc22\n";

    if (Vwords.empty()) {
        std::cout << "Вектор слов пуст! Невозможно выполнить задачу.\n";
        return;
    }

    std::cout << "Вектор слов: ";
    for (std::vector<std::string>::const_iterator it = Vwords.begin(); it != Vwords.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::multimap<char, std::string> M; // мультисловарь

    for (int i = Vwords.size() - 1; i >= 0; i--) { // заполнение мультисловаря в обратном порядке
        const std::string& word = Vwords[i];
        if (!word.empty()) {
            char lastChar = word.back();
            M.insert(std::make_pair(lastChar, word)); // вставка в мультисловарь пары ласт символ - слово
        }
    }

    std::cout << "\nРезультат группировки (последняя буква -> слово):\n";
    for (std::multimap<char, std::string>::const_iterator it = M.begin(); it != M.end(); ++it) {
        std::cout << it->first << " -> " << it->second << std::endl;
    }
}
