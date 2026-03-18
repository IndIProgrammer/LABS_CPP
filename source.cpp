#include "head.h"

//ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ

// Существование файла
bool fileExists(const std::string& filename) {
    std::ifstream file(filename.c_str());
    return file.good();
}

// Сортировка пузырьком массива double по убыванию
void sortDescending(double* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// FILE9. Создать файл из конечного и начального элементов существующего файла
void File9(const std::string& existingFile, const std::string& newFile) {
    std::cout << "\n--- Выполнение File9 ---\n";

    // Проверяем существование файла
    if (!fileExists(existingFile)) {
        std::cout << "Ошибка: Файл " << existingFile << " не существует.\n";
        return;
    }

    // Открываем существующий файл для чтения
    std::ifstream inFile(existingFile.c_str(), std::ios::binary);
    if (!inFile) {
        std::cout << "Ошибка открытия файла " << existingFile << std::endl;
        return;
    }

    // Проверяем, что файл не пустой
    inFile.seekg(0, std::ios::end);  // Переходим в конец файла
    std::streampos fileSize = inFile.tellg();  // Получаем размер файла

    if (fileSize == 0) {
        std::cout << "Ошибка: Файл " << existingFile << " пуст.\n";
        inFile.close();
        return;
    }

    // Проверяем, что размер файла кратен размеру double
    if (fileSize % sizeof(double) != 0) {
        std::cout << "Ошибка: Файл " << existingFile << " поврежден (некорректный размер).\n";
        inFile.close();
        return;
    }

    // Читаем первый элемент
    inFile.seekg(0, std::ios::beg);  // В начало файла
    double firstElement;
    inFile.read(reinterpret_cast<char*>(&firstElement), sizeof(double));

    // Читаем последний элемент
    inFile.seekg(-static_cast<int>(sizeof(double)), std::ios::end);  // Смещение от конца на размер double
    double lastElement;
    inFile.read(reinterpret_cast<char*>(&lastElement), sizeof(double));

    inFile.close();

    std::cout << "Исходный файл содержит " << (fileSize / sizeof(double)) << " элементов\n";
    std::cout << "Первый элемент: " << firstElement << std::endl;
    std::cout << "Последний элемент: " << lastElement << std::endl;

    // Создаем новый файл и записываем конечный и начальный элементы
    std::ofstream outFile(newFile.c_str(), std::ios::binary);
    if (!outFile) {
        std::cout << "Ошибка создания файла " << newFile << std::endl;
        return;
    }

    // Записываем конечный элемент
    outFile.write(reinterpret_cast<const char*>(&lastElement), sizeof(double));
    // Записываем начальный элемент
    outFile.write(reinterpret_cast<const char*>(&firstElement), sizeof(double));

    outFile.close();
    std::cout << "Файл " << newFile << " успешно создан.\n";
    std::cout << "Записаны элементы: " << lastElement << " (последний), "
              << firstElement << " (первый)\n";
}

//FILE32. Удалить первую половину элементов из файла
void File32(const std::string& filename) {
    std::cout << "\n--- Выполнение File32 ---\n";

    // Проверяем существование файла
    if (!fileExists(filename)) {
        std::cout << "Ошибка: Файл " << filename << " не существует.\n";
        return;
    }

    // Открываем файл для чтения
    std::ifstream inFile(filename.c_str(), std::ios::binary);
    if (!inFile) {
        std::cout << "Ошибка открытия файла " << filename << std::endl;
        return;
    }

    // Читаем все числа из файла
    std::vector<int> numbers;
    int value;
    while (inFile.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        numbers.push_back(value);
    }
    inFile.close();

    std::cout << "Исходный файл содержит " << numbers.size() << " элементов\n";

    if (numbers.size() % 2 != 0) {
        std::cout << "Ошибка: Файл должен содержать четное количество элементов.\n";
        std::cout << "Текущее количество элементов: " << numbers.size() << " (нечетное)\n";
        return;
    }

    std::cout << "Исходные элементы: ";
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    // Удаляем первую половину
    int halfSize = numbers.size() / 2;
    std::cout << "Удаляем первую половину (" << halfSize << " элементов)\n";

    std::vector<int> newNumbers;
    for (int i = halfSize; i < numbers.size(); i++) {
        newNumbers.push_back(numbers[i]);
    }

    // Записываем обратно в файл
    std::ofstream outFile(filename.c_str(), std::ios::binary | std::ios::trunc);
    if (!outFile) {
        std::cout << "Ошибка открытия файла для записи " << filename << std::endl;
        return;
    }

    for (int i = 0; i < newNumbers.size(); i++) {
        outFile.write(reinterpret_cast<const char*>(&newNumbers[i]), sizeof(int));
    }

    outFile.close();

    std::cout << "Результирующие элементы: ";
    for (int i = 0; i < newNumbers.size(); i++) {
        std::cout << newNumbers[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Удалена первая половина элементов. Осталось " << newNumbers.size() << " элементов.\n";
}

//FILE51. Объединить три упорядоченных по убыванию файла
void File51(const std::string& file1, const std::string& file2,
                 const std::string& file3, const std::string& resultFile) {
    std::cout << "\n--- Выполнение File51 ---\n";

    // Проверяем существование файлов
    if (!fileExists(file1) || !fileExists(file2) || !fileExists(file3)) {
        std::cout << "Ошибка: Один из исходных файлов не существует.\n";
        return;
    }

    // Открываем файлы для чтения
    std::ifstream inFile1(file1.c_str(), std::ios::binary);
    std::ifstream inFile2(file2.c_str(), std::ios::binary);
    std::ifstream inFile3(file3.c_str(), std::ios::binary);

    if (!inFile1 || !inFile2 || !inFile3) {
        std::cout << "Ошибка открытия исходных файлов.\n";
        return;
    }

    // Считаем общее количество элементов
    int count1 = 0, count2 = 0, count3 = 0;
    double temp;

    while (inFile1.read(reinterpret_cast<char*>(&temp), sizeof(double))) {
        count1++;
    }
    while (inFile2.read(reinterpret_cast<char*>(&temp), sizeof(double))) {
        count2++;
    }
    while (inFile3.read(reinterpret_cast<char*>(&temp), sizeof(double))) {
        count3++;
    }

    std::cout << "Количество элементов в файлах:\n";
    std::cout << file1 << ": " << count1 << "\n";
    std::cout << file2 << ": " << count2 << "\n";
    std::cout << file3 << ": " << count3 << "\n";

    // Возвращаемся в начало файлов
    inFile1.clear();
    inFile1.seekg(0, std::ios::beg);
    inFile2.clear();
    inFile2.seekg(0, std::ios::beg);
    inFile3.clear();
    inFile3.seekg(0, std::ios::beg);

    // Создаем массив для всех чисел
    int totalSize = count1 + count2 + count3;
    double* numbers = new double[totalSize];
    int index = 0;

    // Читаем первый файл
    std::cout << "Содержимое первого файла: ";
    while (inFile1.read(reinterpret_cast<char*>(&temp), sizeof(double))) {
        numbers[index++] = temp;
        std::cout << temp << " ";
    }
    // Читаем второй файл
    std::cout << "\nСодержимое второго файла: ";
    while (inFile2.read(reinterpret_cast<char*>(&temp), sizeof(double))) {
        numbers[index++] = temp;
        std::cout << temp << " ";
    }
    // Читаем третий файл
    std::cout << "\nСодержимое третьего файла: ";
    while (inFile3.read(reinterpret_cast<char*>(&temp), sizeof(double))) {
        numbers[index++] = temp;
        std::cout << temp << " ";
    }
    std::cout << std::endl;

    inFile1.close();
    inFile2.close();
    inFile3.close();

    std::cout << "Сортируем все элементы по убыванию...\n";
    sortDescending(numbers, totalSize);

    // Записываем в результирующий файл
    std::ofstream outFile(resultFile.c_str(), std::ios::binary);
    if (!outFile) {
        std::cout << "Ошибка создания файла " << resultFile << std::endl;
        delete[] numbers;
        return;
    }

    std::cout << "Результирующий файл (отсортирован по убыванию): ";
    for (int i = 0; i < totalSize; i++) {
        outFile.write(reinterpret_cast<const char*>(&numbers[i]), sizeof(double));
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    outFile.close();
    delete[] numbers;

    std::cout << "Файлы успешно объединены в " << resultFile << std::endl;
    std::cout << "Всего элементов: " << totalSize << std::endl;
}

// RECUR15
// Функция для проверки, является ли символ цифрой
bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

// Рекурсивная обработка умножений в терме
int parseTerm(const std::string& s, int& pos) {
    if (pos >= s.length() || !isDigit(s[pos])) {
        return 0;
    }

    // Первое число
    int result = s[pos] - '0';
    pos++;

    // Рекурсивно обрабатываем возможные умножения
    if (pos < s.length() && s[pos] == '*') {
        pos++; // пропускаем '*'
        result *= parseTerm(s, pos);
    }

    return result;
}

// Рекурсивная обработка сложений и вычитаний
int parseExpression(const std::string& s, int& pos) {
    if (pos >= s.length()) {
        return 0;
    }

    // Парсим первый терм
    int result = parseTerm(s, pos);

    // Рекурсивно обрабатываем оставшуюся часть выражения
    if (pos < s.length() && (s[pos] == '+' || s[pos] == '-')) {
        char op = s[pos];
        pos++; // пропускаем операцию

        int next = parseExpression(s, pos);

        if (op == '+') {
            result += next;
        } else {
            result -= next;
        }
    }

    return result;
}

int Recur15(const std::string& expression) {
    // Проверка на пустую строку
    if (expression.empty()) {
        std::cerr << "Ошибка: пустое выражение\n";
        return 0;
    }

    std::cout << "Выражение: " << expression << " = ";

    int pos = 0;
    int result = parseExpression(expression, pos);

    return result;
}

//ТЕСТОВЫЕ ФУНКЦИИ

// Функция для создания тестовых файлов со случайными значениями
void createTestFiles() {
    std::cout << "\n=== СОЗДАНИЕ ТЕСТОВЫХ ФАЙЛОВ ===\n";

    // Инициализация генератора случайных чисел
    srand(time(NULL));

    // 1. Создание файла для File9 (вещественные числа)
    std::ofstream file9("test9.bin", std::ios::binary);
    if (file9) {
        double numbers9[5]; // для хранения чисел
        std::cout << "test9.bin (для File9): ";
        for (int i = 0; i < 5; i++) {
            numbers9[i] = 1.0 + (rand() % 90) / 10.0;
            // Запись числа в файл
            file9.write(reinterpret_cast<const char*>(&numbers9[i]), sizeof(double));
            std::cout << numbers9[i] << " ";
        }
        file9.close();
        std::cout << " (создан)\n";
    }

    // 2. Создание файла для File32 (целые числа, четное количество)
    std::ofstream file32("test32.bin", std::ios::binary);
    if (file32) {
        int numbers32[10];
        std::cout << "test32.bin (для File32): ";
        for (int i = 0; i < 10; i++) {
            numbers32[i] = 1 + rand() % 100;
            file32.write(reinterpret_cast<const char*>(&numbers32[i]), sizeof(int));
            std::cout << numbers32[i] << " ";
        }
        file32.close();
        std::cout << " (создан)\n";
    }

    // 3. Создание файлов для File51 (три файла, упорядоченные по убыванию)

    // Файл A
    std::ofstream file51a("test51a.bin", std::ios::binary);
    if (file51a) {
        double numbersA[5];
        std::cout << "\ntest51a.bin (для File51): ";

        // Заполняем случайными числами
        for (int i = 0; i < 5; i++) {
            numbersA[i] = 1.0 + (rand() % 100) / 10.0;
        }
        // Сортировка по убыванию
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4 - i; j++) {
                if (numbersA[j] < numbersA[j + 1]) {
                    double temp = numbersA[j];
                    numbersA[j] = numbersA[j + 1];
                    numbersA[j + 1] = temp;
                }
            }
        }
        // Запись в файл
        for (int i = 0; i < 5; i++) {
            file51a.write(reinterpret_cast<const char*>(&numbersA[i]), sizeof(double));
            std::cout << numbersA[i] << " ";
        }
        file51a.close();
        std::cout << " (создан, упорядочен по убыванию)\n";
    }

    // Файл B по аналогии с А
    std::ofstream file51b("test51b.bin", std::ios::binary);
    if (file51b) {
        double numbersB[5];
        std::cout << "test51b.bin (для File51): ";
        for (int i = 0; i < 5; i++) {
            numbersB[i] = 1.0 + (rand() % 100) / 10.0;
        }
        // Сортировка по убыванию
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4 - i; j++) {
                if (numbersB[j] < numbersB[j + 1]) {
                    double temp = numbersB[j];
                    numbersB[j] = numbersB[j + 1];
                    numbersB[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < 5; i++) {
            file51b.write(reinterpret_cast<const char*>(&numbersB[i]), sizeof(double));
            std::cout << numbersB[i] << " ";
        }
        file51b.close();
        std::cout << " (создан, упорядочен по убыванию)\n";
    }

    // Файл C по аналогии с А
    std::ofstream file51c("test51c.bin", std::ios::binary);
    if (file51c) {
        double numbersC[5];
        std::cout << "test51c.bin (для File51): ";
        for (int i = 0; i < 5; i++) {
            numbersC[i] = 1.0 + (rand() % 100) / 10.0;
        }
        // Сортировка по убыванию
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4 - i; j++) {
                if (numbersC[j] < numbersC[j + 1]) {
                    double temp = numbersC[j];
                    numbersC[j] = numbersC[j + 1];
                    numbersC[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < 5; i++) {
            file51c.write(reinterpret_cast<const char*>(&numbersC[i]), sizeof(double));
            std::cout << numbersC[i] << " ";
        }
        file51c.close();
        std::cout << " (создан, упорядочен по убыванию)\n";
    }

    // 4. Дополнительные тестовые файлы
    std::ofstream file9single("test9_single.bin", std::ios::binary);
    if (file9single) {
        double single = 42.5; // С одним числом
        file9single.write(reinterpret_cast<const char*>(&single), sizeof(double));
        file9single.close();
        std::cout << "\ntest9_single.bin создан с одним элементом: 42.5\n";
    }

    std::ofstream file32even("test32_even.bin", std::ios::binary);
    if (file32even) {
        int numbers[8];
        std::cout << "test32_even.bin: ";
        for (int i = 0; i < 8; i++) { // С четными числами
            numbers[i] = (i + 1) * 5;
            file32even.write(reinterpret_cast<const char*>(&numbers[i]), sizeof(int));
            std::cout << numbers[i] << " ";
        }
        file32even.close();
        std::cout << " (создан)\n";
    }

    std::cout << "\nВсе тестовые файлы успешно созданы!\n";
}

// Функция для просмотра содержимого бинарных файлов
void viewBinaryFiles() {
    std::cout << "\n=== ПРОСМОТР БИНАРНЫХ ФАЙЛОВ ===\n";

    // Массив с именами файлов вещественных чисел
    const char* doubleFiles[] = {
            "test9.bin", "new9.bin", "test9_single.bin",
            "test51a.bin", "test51b.bin", "test51c.bin", "result51.bin"
    };
    int numDoubleFiles = 7;

    // Массив с именами файлов целых чисел
    const char* intFiles[] = {
            "test32.bin", "test32_even.bin"
    };
    int numIntFiles = 2;

    std::cout << "\n--- Файлы с вещественными числами (double) ---\n";
    for (int i = 0; i < numDoubleFiles; i++) {
        std::ifstream file(doubleFiles[i], std::ios::binary);
        if (file) {
            std::cout << doubleFiles[i] << ": ";
            double value;
            int count = 0;
            // Чтение чисел до конца файла
            while (file.read(reinterpret_cast<char*>(&value), sizeof(double))) {
                std::cout << value << " ";
                count++;
            }
            std::cout << " (всего: " << count << " элементов)\n";
            file.close();
        } else {
            std::cout << doubleFiles[i] << ": файл не найден\n";
        }
    }

    std::cout << "\n--- Файлы с целыми числами (int) ---\n";
    for (int i = 0; i < numIntFiles; i++) {
        std::ifstream file(intFiles[i], std::ios::binary);
        if (file) {
            std::cout << intFiles[i] << ": ";
            int value;
            int count = 0;
            while (file.read(reinterpret_cast<char*>(&value), sizeof(int))) {
                std::cout << value << " ";
                count++;
            }
            std::cout << " (всего: " << count << " элементов)\n";
            file.close();
        } else {
            std::cout << intFiles[i] << ": файл не найден\n";
        }
    }
}
