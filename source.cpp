#include "head.h"

// Заполнение вектора с клавиатуры
void fillVectorFromKeyboard(std::vector<int>& v) {
    v.clear();
    int n = getPositiveIntInput("Введите количество элементов: ");
    std::cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; ++i) {
        int val = getIntInput("", INT_MIN, INT_MAX);
        v.push_back(val);
    }
}

// Заполнение вектора рандомом
void fillVectorRandom(std::vector<int>& v, int size) {
    v.clear();
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < size; ++i) {
        int val = rand() % 101 - 50;
        v.push_back(val);
    }
    std::cout << "Сгенерировано " << size << " случайных элементов." << std::endl;
}

// Заполнение вектора из файла
void fillVectorFromFile(std::vector<int>& v) {
    v.clear();
    std::string filename = "input.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
        std::cout << "Убедитесь, что файл существует в текущей директории." << std::endl;
        return;
    }
    int val;
    while (file >> val) {
        v.push_back(val);
    }
    file.close();
    std::cout << "Загружено " << v.size() << " элементов из файла " << filename << "." << std::endl;
}

// Заполнение списка сс клавиатуры
void fillListFromKeyboard(std::list<int>& l) {
    l.clear();
    int n = getPositiveIntInput("Введите количество элементов: ");
    std::cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; ++i) {
        int val = getIntInput("", INT_MIN, INT_MAX);
        l.push_back(val);
    }
}

// Заполнение списка рандомом
void fillListRandom(std::list<int>& l, int size) {
    l.clear();
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < size; ++i) {
        int val = rand() % 101 - 50;
        l.push_back(val);
    }
    std::cout << "Сгенерировано " << size << " случайных элементов." << std::endl;
}

// Заполнение списка из файла
void fillListFromFile(std::list<int>& l) {
    l.clear();
    std::string filename = "input.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
        std::cout << "Убедитесь, что файл существует в текущей директории." << std::endl;
        return;
    }
    int val;
    while (file >> val) {
        l.push_back(val);
    }
    file.close();
    std::cout << "Загружено " << l.size() << " элементов из файла " << filename << "." << std::endl;
}

// Заполнение списка словами с клавиатуры
void fillStringListFromKeyboard(std::list<std::string>& l) {
    l.clear();
    int n = getPositiveIntInput("Введите количество элементов: ");
    std::cout << "Введите " << n << " слов: ";
    for (int i = 0; i < n; ++i) {
        std::string val;
        std::cin >> val;
        l.push_back(val);
    }
}

// Заполнение списка словами рандомом
void fillStringListRandom(std::list<std::string>& l, int size) {
    l.clear();
    static std::vector<std::string> words = {"ABC", "XYZ", "PSU", "APPLE", "BANANA", "CAT", "DOG", "TREE", "HOUSE", "DND"};
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < size; ++i) {
        int index = rand() % words.size();
        l.push_back(words[index]);
    }
    std::cout << "Сгенерировано " << size << " случайных слов." << std::endl;
}

// Заполнение списка словами из файла
void fillStringListFromFile(std::list<std::string>& l) {
    l.clear();
    std::string filename = "input_List_Words.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
        std::cout << "Убедитесь, что файл существует в текущей директории." << std::endl;
        return;
    }
    std::string val;
    while (file >> val) {
        l.push_back(val);
    }
    file.close();
    std::cout << "Загружено " << l.size() << " элементов из файла " << filename << "." << std::endl;
}

// Вывод вектора на экран
void printVector(const std::vector<int>& v, const std::string& name) {
    std::cout << name << ": ";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

// Вывод списка на экран
void printList(const std::list<int>& l, const std::string& name) {
    std::cout << name << ": ";
    for (std::list<int>::const_iterator it = l.begin(); it != l.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Вывод списка слов на экран
void printStringList(const std::list<std::string>& l, const std::string& name) {
    std::cout << name << ": ";
    for (std::list<std::string>::const_iterator it = l.begin(); it != l.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Вывод дека содержащий слова на экран
void printStringDeque(const std::deque<std::string>& d, const std::string& name) {
    std::cout << name << ": ";
    for (size_t i = 0; i < d.size(); ++i) {
        std::cout << d[i] << " ";
    }
    std::cout << std::endl;
}

// Вывод дека на экран
void printIntDeque(const std::deque<int>& d, const std::string& name) {
    std::cout << name << ": ";
    for (size_t i = 0; i < d.size(); ++i) {
        std::cout << d[i] << " ";
    }
    std::cout << std::endl;
}

// Задание STL3Alg3: удаление первого и последнего нулевого элемента в списке
void solveAlg3(std::list<int>& l) {
    if (l.empty()) {
        std::cout << "Список пуст, удаление невозможно." << std::endl;
        return;
    }

    // Поиск первого нулевого элемента
    std::list<int>::iterator firstZero = std::find(l.begin(), l.end(), 0);
    if (firstZero == l.end()) {
        std::cout << "Нулевых элементов нет." << std::endl;
        return;
    }

    std::cout << "Первый нулевой элемент удалён." << std::endl;
    l.erase(firstZero);

    // Поиск последнего нулевого элемента
    std::list<int>::reverse_iterator lastZeroRev = std::find(l.rbegin(), l.rend(), 0);

    if (lastZeroRev != l.rend()) {
        l.erase((++lastZeroRev).base());
        std::cout << "Последний нулевой элемент удалён." << std::endl;
    } else {
        std::cout << "Больше нулевых элементов нет." << std::endl;
    }
}

// Функциональный объект для генерации убывающей последовательности
struct Generator {
    int val;
    int operator()() { return val--; } // operator позволяет структуре вести себя как функция
};

// Задание STL3Alg19: вставка в дек элементов в начало 1, 2, ... N и в конец N, N-1, ... 1
void solveAlg19(std::deque<int>& d, int N) {
    if (N <= 0) {
        std::cout << "N должно быть положительным." << std::endl;
        return;
    }
    d.clear();

    // Добавляем в начало: 1, ..., N
    // Генерируем в обратном порядке, после чего front_inserter добавляет в начало сгенерированные значения
    std::generate_n(std::front_inserter(d), N, Generator{N});

    // Добавляем в конец: N, ..., 1
    std::generate_n(std::back_inserter(d), N, Generator{N});
}

// Задание STL3Alg47: использованием методов сортировки и слияния в векторе
void solveAlg47(std::vector<int>& v) {
    if (v.size() % 2 != 0) {
        std::cout << "Вектор должен иметь чётное количество элементов для этого задания." << std::endl;
        return;
    }

    size_t mid = v.size() / 2;

    std::cout << "Исходный вектор: ";
    printVector(v, "V");

    std::sort(v.begin() + mid, v.end());
    std::cout << "После сортировки второй половины: ";
    printVector(v, "V");

    std::inplace_merge(v.begin(), v.begin() + mid, v.end());
    std::cout << "После слияния: ";
    printVector(v, "V");
}

// Функциональный объект для комбинирования строк
struct StringCombiner {
    std::string operator()(const std::string& a, const std::string& b) const {
        return std::string{b.front(), a.back()};
    }
};

// Задание STL3Alg61: создать дек строк по парам соседних слов
void solveAlg61(const std::list<std::string>& l, std::deque<std::string>& d) {
    if (l.size() < 2) {
        std::cout << "Список должен содержать минимум 2 элемента." << std::endl;
        return;
    }
    d.clear();

    std::adjacent_difference(
            l.begin(), l.end(),
            std::front_inserter(d),
            StringCombiner()
    );

    // Удаляем последний лишний элемент
    if (!d.empty()) {
        d.erase(std::prev(d.end()));
    }

    std::reverse(d.begin(), d.end());
}

// Получение целых чисел при вводе
int getIntInput(const std::string& prompt, int minVal, int maxVal) {
    int val;
    bool valid = false;
    while (!valid) {
        if (!prompt.empty()) {
            std::cout << prompt;
        }
        if (std::cin >> val) {
            if (val >= minVal && val <= maxVal) {
                valid = true;
            } else {
                std::cout << "Ошибка: число должно быть в диапазоне [" << minVal << ", " << maxVal << "]. Повторите ввод." << std::endl;
            }
        } else {
            std::cout << "Ошибка: введите целое число." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return val;
}

// Проверка на ввод положительных чисел
int getPositiveIntInput(const std::string& prompt) {
    return getIntInput(prompt, 1, INT_MAX);
}

// Меню заполнения списка
void fillListMenu(std::list<int>& l) {
    std::cout << "\nВыберите способ заполнения списка:\n";
    std::cout << "1. С клавиатуры\n";
    std::cout << "2. Случайными числами\n";
    std::cout << "3. Из файла (input.txt)\n";
    std::cout << "Ваш выбор: ";

    int choice = getIntInput("", 1, 3);

    switch (choice) {
        case 1:
            fillListFromKeyboard(l);
            break;
        case 2: {
            int size = getPositiveIntInput("Введите количество элементов: ");
            fillListRandom(l, size);
            break;
        }
        case 3: {
            fillListFromFile(l);
            break;
        }
    }
}

// Меню заполнения вектора
void fillVectorMenu(std::vector<int>& v) {
    std::cout << "\nВыберите способ заполнения вектора:\n";
    std::cout << "1. С клавиатуры\n";
    std::cout << "2. Случайными числами\n";
    std::cout << "3. Из файла (input.txt)\n";
    std::cout << "Ваш выбор: ";

    int choice = getIntInput("", 1, 3);

    switch (choice) {
        case 1:
            fillVectorFromKeyboard(v);
            break;
        case 2: {
            int size = getPositiveIntInput("Введите количество элементов: ");
            fillVectorRandom(v, size);
            break;
        }
        case 3: {
            fillVectorFromFile(v);
            break;
        }
    }
}

// Меню для заполнения списка словами
void fillStringListMenu(std::list<std::string>& l) {
    std::cout << "\nВыберите способ заполнения списка слов:\n";
    std::cout << "1. С клавиатуры\n";
    std::cout << "2. Случайными словами\n";
    std::cout << "3. Из файла (input_List_Words.txt)\n";
    std::cout << "Ваш выбор: ";

    int choice = getIntInput("", 1, 3);

    switch (choice) {
        case 1:
            fillStringListFromKeyboard(l);
            break;
        case 2: {
            int size = getPositiveIntInput("Введите количество элементов: ");
            fillStringListRandom(l, size);
            break;
        }
        case 3: {
            fillStringListFromFile(l);
            break;
        }
    }
}
