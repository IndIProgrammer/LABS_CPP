#include "head.h"

// Очистка потока ввода
void clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Получает целое число с проверкой корректности ввода
int getIntInput(const std::string& prompt, bool positiveOnly, bool checkRange, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << "Ошибка: введите целое число!\n";
            clearInputStream();
        } else if (positiveOnly && value <= 0) {
            std::cout << "Ошибка: число должно быть положительным!\n";
        } else if (checkRange && (value < 0 || value > maxValue)) {
            std::cout << "Ошибка: введите число от 1 до " << maxValue << "!\n";
        } else {
            clearInputStream(); // Очищаем буфер после успешного ввода
            return value;
        }
    }
}

// Перегруженная версия для обратной совместимости
int getIntInput(const std::string& prompt, bool positiveOnly) {
    return getIntInput(prompt, positiveOnly, false, 0);
}

// Получает выбор пункта меню с построчным чтением и проверкой на цифры
int getMenuChoice() {
    std::string input;
    int choice;

    while (true) {
        std::cout << "Выберите задачу: ";
        std::getline(std::cin, input);

        // Проверяем, состоит ли строка только из цифр
        bool valid = true;
        for (size_t i = 0; i < input.length(); ++i) {
            if (!isdigit(input[i])) {
                valid = false;
                break;
            }
        }

        if (!valid || input.empty()) {
            std::cout << "Ошибка: введите число!\n";
            continue;
        }

        // Преобразуем строку в число
        choice = 0;
        for (size_t i = 0; i < input.length(); ++i) {
            choice = choice * 10 + (input[i] - '0');
        }

        return choice;
    }
}

// Функции для заполнения вектора(Vector)/списка(List) [ниже] числами
void fillVector(std::vector<int>& cont, const std::string& containerName) {
    int choice;

    do {
        std::cout << "Выберите способ заполнения " << containerName << ":\n";
        std::cout << "1 - Ввод с клавиатуры\n";
        std::cout << "2 - Случайные числа\n";
        std::cout << "3 - Из файла\n";

        choice = getIntInput("Ваш выбор (1-3): ", false, true, 3);

        if (choice < 1 || choice > 3) {
            std::cout << "Ошибка: введите число от 1 до 3!\n";
        }
    } while (choice < 1 || choice > 3);

    switch(choice) {
        case 1: {
            int n = getIntInput("Введите количество элементов: ", true);
            std::cout << "Введите " << n << " целых чисел:\n";
            for (int i = 0; i < n; ++i) {
                int val = getIntInput("", false);
                cont.push_back(val);
            }
            break;
        }
        case 2: {
            int n = getIntInput("Введите количество элементов: ", true);
            std::srand(static_cast<unsigned>(std::time(NULL)));
            for (int i = 0; i < n; ++i) {
                cont.push_back(std::rand() % 100);
            }
            std::cout << "Сгенерировано " << n << " случайных чисел\n";
            break;
        }
        case 3: {
            std::string filename = "input.txt";
            std::ifstream file(filename.c_str());
            if (!file) {
                std::cerr << "Ошибка открытия файла " << filename << "!\n";
                return;
            }

            int val;
            while (file >> val) {
                cont.push_back(val);
            }
            file.close();
            std::cout << "Загружено " << cont.size() << " чисел из файла " << filename << "\n";
            break;
        }
    }
}

void fillList(std::list<int>& cont, const std::string& containerName) {
    int choice;

    do {
        std::cout << "Выберите способ заполнения " << containerName << ":\n";
        std::cout << "1 - Ввод с клавиатуры\n";
        std::cout << "2 - Случайные числа\n";
        std::cout << "3 - Из файла\n";

        choice = getIntInput("Ваш выбор (1-3): ", false, true, 3);

        if (choice < 1 || choice > 3) {
            std::cout << "Ошибка: введите число от 1 до 3!\n";
        }
    } while (choice < 1 || choice > 3);

    switch(choice) {
        case 1: {
            int n = getIntInput("Введите количество элементов: ", true);
            std::cout << "Введите " << n << " целых чисел:\n";
            for (int i = 0; i < n; ++i) {
                int val = getIntInput("", false);
                cont.push_back(val);
            }
            break;
        }
        case 2: {
            int n = getIntInput("Введите количество элементов: ", true);
            std::srand(static_cast<unsigned>(std::time(NULL)));
            for (int i = 0; i < n; ++i) {
                cont.push_back(std::rand() % 100);
            }
            std::cout << "Сгенерировано " << n << " случайных чисел\n";
            break;
        }
        case 3: {
            std::string filename = "input.txt";
            std::ifstream file(filename.c_str());
            if (!file) {
                std::cerr << "Ошибка открытия файла " << filename << "!\n";
                return;
            }

            int val;
            while (file >> val) {
                cont.push_back(val);
            }
            file.close();
            std::cout << "Загружено " << cont.size() << " чисел из файла " << filename << "\n";
            break;
        }
    }
}

// Функция для заполнения файла тремя способами
void fillFileThreeWays(const std::string& filename) {
    int choice;

    do {
        std::cout << "Выберите способ заполнения файла " << filename << ":\n";
        std::cout << "1 - Ввод с клавиатуры\n";
        std::cout << "2 - Случайные числа\n";
        std::cout << "3 - Из другого файла (source.txt)\n";

        choice = getIntInput("Ваш выбор (1-3): ", false, true, 3);
    } while (choice < 1 || choice > 3);

    std::ofstream outFile(filename.c_str());
    if (!outFile) {
        std::cerr << "Ошибка создания файла " << filename << "!\n";
        return;
    }

    switch(choice) {
        case 1: {
            int n = getIntInput("Введите количество чисел: ", true);
            std::cout << "Введите " << n << " целых чисел:\n";
            for (int i = 0; i < n; ++i) {
                int val = getIntInput("", false);
                outFile << val << " ";
            }
            std::cout << "Данные записаны в файл " << filename << std::endl;
            break;
        }
        case 2: {
            int n = getIntInput("Введите количество случайных чисел: ", true);
            std::srand(static_cast<unsigned>(std::time(NULL)));
            for (int i = 0; i < n; ++i) {
                outFile << (std::rand() % 100) << " ";
            }
            std::cout << "Сгенерировано " << n << " случайных чисел в файл " << filename << std::endl;
            break;
        }
        case 3: {
            std::string sourceFile = "source.txt";
            std::ifstream inFile(sourceFile.c_str());
            if (!inFile) {
                std::cerr << "Ошибка открытия исходного файла " << sourceFile << "!\n";
                std::cerr << "Создайте файл source.txt с числами или выберите другой способ.\n";
                outFile.close();
                remove(filename.c_str()); // Удаляем пустой файл
                return;
            }

            int val;
            while (inFile >> val) {
                outFile << val << " ";
            }
            inFile.close();
            std::cout << "Данные скопированы из файла " << sourceFile << " в " << filename << std::endl;
            break;
        }
    }
    outFile.close();
}

// STL2Seq2: заполнить список L числами и вывести в прямом и обратном порядке
void STL2Seq2() {
    std::cout << "\nSTL2Seq2\n";
    std::cout << "Заполнение списка числами и вывод в прямом и обратном порядке\n\n";

    std::list<int> L;
    fillList(L, "списка");

    if (L.empty()) {
        std::cout << "Список пуст!\n";
        return;
    }

    std::cout << "\nИсходный порядок: ";
    for (std::list<int>::iterator it = L.begin(); it != L.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Обратный порядок: ";
    for (std::list<int>::reverse_iterator rit = L.rbegin(); rit != L.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;
}

// STL2Seq11: вставить после 5-го элемента списка первые 5 элементов вектора в обратном порядке
void STL2Seq11() {
    std::cout << "\nSTL2Seq11\n";
    std::cout << "Вставка после 5-го элемента списка первых 5 элементов вектора в обратном порядке\n\n";

    std::vector<int> V;
    std::list<int> L;

    fillVector(V, "вектора");
    fillList(L, "списка");

    // Проверка условий задачи
    if (V.size() < 5) {
        std::cout << "Ошибка: вектор должен содержать не менее 5 элементов!\n";
        return;
    }

    if (L.size() < 5) {
        std::cout << "Ошибка: список должен содержать не менее 5 элементов!\n";
        return;
    }

    std::cout << "\nИсходный вектор: ";
    for (std::vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\nИсходный список: ";
    for (std::list<int>::iterator it = L.begin(); it != L.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Находим позицию после 5-го элемента (индексация с 0, поэтому после 5-го = позиция 5)
    std::list<int>::iterator it = L.begin();
    int pos = 5;
    while (pos > 0 && it != L.end()) {
        ++it;
        --pos;
    }

    // Создаем вектор с первыми 5 элементами в обратном порядке
    std::vector<int> first5;
    for (int i = 4; i >= 0; --i) {
        first5.push_back(V[i]);
    }

    // Вставляем
    L.insert(it, first5.begin(), first5.end());

    std::cout << "Результат: ";
    for (std::list<int>::iterator it2 = L.begin(); it2 != L.end(); ++it2) {
        std::cout << *it2 << " ";
    }
    std::cout << std::endl;
}

// STL2Seq27: удалить из вектора элементы с нечётными порядковыми номерами
void STL2Seq27() {
    std::cout << "\nSTL2Seq27\n";
    std::cout << "Удаление из вектора элементов с нечётными порядковыми номерами\n\n";

    std::vector<int> V;
    fillVector(V, "вектора");

    if (V.empty()) {
        std::cout << "Вектор пуст!\n";
        return;
    }

    std::cout << "\nИсходный вектор: ";
    for (std::vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Удаляем элементы с нечётными номерами
    for (std::vector<int>::iterator i = V.begin(); i != V.end(); ) {
        // Вычисляем индекс элемента (1-индексация для порядковых номеров)
        int index = (i - V.begin()) + 1;
        if (index % 2 == 1) {
            i = V.erase(i);
        } else {
            ++i;
        }
        // Проверяем, не достигнут ли конец вектора
        if (i == V.end()) {
            break;
        }
    }

    if (V.empty()) {
        std::cout << "После удаления вектор стал пустым\n";
    } else {
        std::cout << "После удаления: ";
        for (std::vector<int>::iterator it2 = V.begin(); it2 != V.end(); ++it2) {
            std::cout << *it2 << " ";
        }
        std::cout << std::endl;
    }
}

// STL1Iter15: заменить 0 на 10 и записать в файл с двумя пробелами после каждого числа
void STL1Iter15() {
    std::cout << "\nSTL1Iter15\n";
    std::cout << "Замена 0 на 10 и запись в файл\n\n";

    std::string filename = "name.txt";

    // Заполняем файл тремя способами
    std::cout << "Сначала заполним файл " << filename << ":\n";
    fillFileThreeWays(filename);

    // Читаем числа из файла
    std::ifstream inFile(filename.c_str());
    if (!inFile) {
        std::cerr << "Ошибка открытия файла " << filename << " для чтения!\n";
        return;
    }

    // Создаем файл для результата
    std::string resultFilename = "result_name.txt";
    std::ofstream outFile(resultFilename.c_str());
    if (!outFile) {
        std::cerr << "Ошибка создания файла результата!\n";
        inFile.close();
        return;
    }

    // Используем replace_copy для замены 0 на 10 и записи с двумя пробелами
    std::replace_copy(
            std::istream_iterator<int>(inFile),
            std::istream_iterator<int>(),
            std::ostream_iterator<int>(outFile, "  "),
            0, 10
    );

    inFile.close();
    outFile.close();

    std::cout << "Результат записан в файл " << resultFilename << std::endl;

    // Показываем результат, прочитав из файла
    std::ifstream resultFile(resultFilename.c_str());
    if (resultFile) {
        std::cout << "Числа после замены (из файла " << resultFilename << "): ";

        int num;
        while (resultFile >> num) {
            std::cout << num << " ";
        }

        std::cout << std::endl;
        resultFile.close();
    }
}

// Главное меню
void showMenu() {
    std::cout << "\nГЛАВНОЕ МЕНЮ\n";
    std::cout << "1 - STL2Seq2 (список: прямой и обратный порядок)\n";
    std::cout << "2 - STL2Seq11 (вставка из вектора в список)\n";
    std::cout << "3 - STL2Seq27 (удаление элементов с нечётными номерами)\n";
    std::cout << "4 - STL1Iter15 (замена 0 на 10 и запись в файл)\n";
    std::cout << "5 - Заполнить файл\n";
    std::cout << "0 - Выход\n";
}
