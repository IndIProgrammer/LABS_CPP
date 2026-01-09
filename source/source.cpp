#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <map>
#include "head.h"

//сортировка для задания sort4 с резделением |
void bubble_sort_with_protocol_combined(std::vector<int>& arr, const std::string& filename) {
    std::ofstream out_file(filename);
    if (!out_file) {
        std::cerr << "Ошибка открытия файла для записи протокола!" << std::endl;
        return;
    }

    int n = arr.size();
    int sorted_count = 0;

    // Выводим исходный массив
    out_file << "Начальный массив:" << std::endl;

    // Встроенная функция print_array_with_separator
    for (int i = 0; i < n; i++) {
        out_file << arr[i];
        if (i == n - sorted_count - 1 && sorted_count < n) {
            out_file << " |";
        }
        if (i < n - 1) {
            out_file << " ";
        }
    }
    out_file << std::endl;

    out_file << std::endl << "Протокол сортировки:" << std::endl;

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        sorted_count++;

        // Снова выводим массив с разделителем
        for (int k = 0; k < n; k++) {
            out_file << arr[k];
            if (k == n - sorted_count - 1 && sorted_count < n) {
                out_file << " |";
            }
            if (k < n - 1) {
                out_file << " ";
            }
        }
        out_file << std::endl;

        if (!swapped) {
            break;
        }
    }

    out_file << std::endl << "Отсортированный массив:" << std::endl;

    // Финальный вывод
    for (int i = 0; i < n; i++) {
        out_file << arr[i];
        if (i < n - 1) {
            out_file << " ";
        }
    }
    out_file << std::endl;

    out_file.close();
    std::cout << "Сортировка завершена. Протокол сохранен в файле: " << filename << std::endl;
}
//шейкер сортировка для five14
void shaker_sort_students(std::vector<std::pair<int, std::string>>& data) {
    int n = data.size();
    if (n <= 1) return;

    int left = 0;
    int right = n - 1;

    while (left <= right) {
        // Проход слева направо
        for (int i = left; i < right; i++) {
            // Сравниваем по баллу (убывание) и фамилии (возрастание)
            if ((data[i].first < data[i + 1].first) ||
                (data[i].first == data[i + 1].first && data[i].second > data[i + 1].second)) {
                std::swap(data[i], data[i + 1]);
            }
        }
        right--;

        // Проход справа налево
        for (int i = right; i > left; i--) {
            if ((data[i - 1].first < data[i].first) ||
                (data[i - 1].first == data[i].first && data[i - 1].second > data[i].second)) {
                std::swap(data[i - 1], data[i]);
            }
        }
        left++;
    }
}

std::vector<FitnessResult> process_fitness_client_data(
        int target_client_code,
        const std::vector<ClientRecord>& records) {

    std::map<int, std::pair<int, int>> year_min_duration;

    // Собираем данные
    for (const auto& record : records) {
        if (record.client_code == target_client_code && record.duration > 0) {
            auto it = year_min_duration.find(record.year);

            if (it == year_min_duration.end()) {
                year_min_duration[record.year] = std::make_pair(record.duration, record.month);
            } else {
                if (record.duration < it->second.first ||
                    (record.duration == it->second.first && record.month > it->second.second)) {
                    it->second.first = record.duration;
                    it->second.second = record.month;
                }
            }
        }
    }

    if (year_min_duration.empty()) {
        return {};
    }

    // Преобразуем в вектор структур
    std::vector<FitnessResult> result;
    for (const auto& entry : year_min_duration) {
        result.push_back({entry.second.first, entry.first, entry.second.second});
    }

    // СОРТИРОВКА ВЫБОРОМ
    int n = result.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            // Используем оператор < который мы определили
            if (result[j] < result[min_idx]) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            std::swap(result[i], result[min_idx]);
        }
    }

    return result;
}
//считать массив из файла
std::vector<int> read_int_array_from_file(const std::string& filename) {
    std::vector<int> arr;
    std::ifstream in_file(filename);

    if (!in_file) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return arr;
    }

    int n, value;
    in_file >> n;

    for (int i = 0; i < n; i++) {
        in_file >> value;
        arr.push_back(value);
    }

    in_file.close();
    return arr;
}

//чтение данных из фйала egeres.txt
std::vector<std::pair<int, std::string>> read_student_data_from_file(const std::string& filename) {
    std::vector<std::pair<int, std::string>> data;
    std::ifstream in_file(filename);

    if (!in_file) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(in_file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string surname;
        int score;

        ss >> surname >> score;
        data.emplace_back(score, surname);
    }

    in_file.close();
    return data;
}

//для записи данных в файл 2.txt
void write_student_data_to_file(const std::vector<std::pair<int, std::string>>& data, const std::string& filename) {
    std::ofstream out_file(filename);

    if (!out_file) {
        std::cerr << "Ошибка открытия файла для записи: " << filename << std::endl;
        return;
    }

    for (const auto& student : data) {
        out_file << std::left << std::setw(15) << student.second
                 << std::right << std::setw(3) << student.first << std::endl;
    }

    out_file.close();
    std::cout << "Данные сохранены в файле: " << filename << std::endl;
}

//для чтения данных о клиентах фитнес-центра при вводе
std::vector<ClientRecord> read_client_records_from_stream(std::istream& input) {
    std::vector<ClientRecord> records;
    int n;

    // Читаем количество записей
    input >> n;

    for (int i = 0; i < n; i++) {
        ClientRecord record;
        input >> record.duration >> record.client_code >> record.year >> record.month;

        // Проверка корректности данных
        if (record.duration >= 1 && record.duration <= 30 &&
            record.client_code >= 10 && record.client_code <= 99 &&
            record.year >= 2000 && record.year <= 2010 &&
            record.month >= 1 && record.month <= 12) {
            records.push_back(record);
        }
    }
    return records;
}

//user(less)interface
void show_main_menu() {
    std::cout << "\n========================================\n";
    std::cout << "     МЕНЮ РЕШЕНИЯ ЗАДАЧ\n";
    std::cout << "========================================\n";
    std::cout << "0. Выход\n";
    std::cout << "1. Задача 1 - Сортировка массива (Sort4)\n";
    std::cout << "2. Задача 2 - Фитнес-центр (ExamTaskC16)\n";
    std::cout << "3. Задача 3 - Сортировка учеников (Five14)\n";
    std::cout << "========================================\n";
    std::cout << "Выберите задачу (0-3): ";
}
void run_task1() {
    std::cout << "\n=== ЗАДАЧА 1: СОРТИРОВКА МАССИВА ===\n\n";

    std::string input_file, output_file;
    std::cout << "Введите имя файла с исходным массивом: ";
    std::cin >> input_file;
    std::cout << "Введите имя файла для протокола сортировки: ";
    std::cin >> output_file;

    // Чтение массива из файла
    std::vector<int> arr = read_int_array_from_file(input_file);

    if (arr.empty()) {
        std::cout << "Не удалось прочитать массив из файла или файл пуст.\n";
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }

    std::cout << "\nИсходный массив (" << arr.size() << " элементов):\n";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    // Выполнение сортировки
    bubble_sort_with_protocol_combined(arr, output_file);

    std::cout << "\nРезультат сортировки:\n";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
void run_task2() {
    std::cout << "\n=== ЗАДАЧА 2: ФИТНЕС-ЦЕНТР ===\n\n";

    int target_client_code;
    std::cout << "Введите код клиента (10-99): ";
    std::cin >> target_client_code;

    if (target_client_code < 10 || target_client_code > 99) {
        std::cout << "Неверный код клиента!\n";
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }

    std::cout << "\nВведите данные. Формат:\n";
    std::cout << "N (количество записей)\n";
    std::cout << "Далее N строк в формате: продолжительность код_клиента год месяц\n";
    std::cout << "Пример: 5 25 2005 3\n\n";

    int n;
    std::cout << "Количество записей: ";
    std::cin >> n;

    std::vector<ClientRecord> records;
    std::cout << "\nВведите " << n << " записей:\n";

    int valid_records = 0;
    int invalid_records = 0;

    for (int i = 0; i < n; i++) {
        ClientRecord record;
        std::cout << "Запись " << i + 1 << ": ";
        std::cin >> record.duration >> record.client_code >> record.year >> record.month;

        // ПРОВЕРКА КОРРЕКТНОСТИ ДАННЫХ
        bool is_valid = true;
        std::string error_message;

        if (record.duration < 1 || record.duration > 30) {
            is_valid = false;
            error_message = "Продолжительность должна быть от 1 до 30 часов";
        }
        else if (record.client_code < 10 || record.client_code > 99) {
            is_valid = false;
            error_message = "Код клиента должен быть от 10 до 99";
        }
        else if (record.year < 2000 || record.year > 2010) {
            is_valid = false;
            error_message = "Год должен быть от 2000 до 2010";
        }
        else if (record.month < 1 || record.month > 12) {
            is_valid = false;
            error_message = "Месяц должен быть от 1 до 12";
        }

        if (is_valid) {
            records.push_back(record);
            valid_records++;
        } else {
            invalid_records++;
            std::cout << "  [ОШИБКА: " << error_message << " - запись пропущена]\n";

            // Если остались записи для ввода, продолжаем
            if (i < n - 1) {
                std::cout << "  Продолжаем ввод...\n";
            }
        }
    }

    // Проверяем, есть ли вообще корректные записи
    if (records.empty()) {
        std::cout << "\nНет корректных записей для обработки.\n";
        if (invalid_records > 0) {
            std::cout << "Из " << n << " записей все (" << invalid_records << ") содержали ошибки.\n";
        }
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }

    // Выводим статистику
    std::cout << "\n========================================\n";
    std::cout << "СТАТИСТИКА ВВОДА:\n";
    std::cout << "Всего записей: " << n << "\n";
    std::cout << "Корректных: " << valid_records << "\n";
    if (invalid_records > 0) {
        std::cout << "С ошибками: " << invalid_records << " (пропущены)\n";
    }
    std::cout << "========================================\n";

    // Обработка данных
    auto result = process_fitness_client_data(target_client_code, records);

    std::cout << "\n=== РЕЗУЛЬТАТ ===\n";
    if (result.empty()) {
        std::cout << "Нет данных для клиента с кодом " << target_client_code << "\n";
        std::cout << "Возможно, у этого клиента нет записей с положительной продолжительностью.\n";
    } else {
        std::cout << "Для клиента " << target_client_code << " найдены данные за "
                  << result.size() << " год(а/ов):\n";
        std::cout << "Формат: продолжительность(часы) год месяц\n";
        std::cout << "----------------------------------------\n";

        // Выводим данные через доступ к полям структуры
        for (const auto& item : result) {
            // Используем поля структуры вместо std::get
            std::cout << item.duration << " " << item.year << " " << item.month << std::endl;
        }
    }
    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
void run_task3() {
    std::cout << "\n=== ЗАДАЧА 3: СОРТИРОВКА УЧЕНИКОВ ===\n\n";

    std::string input_file, output_file;
    std::cout << "Введите имя файла с данными учеников: ";
    std::cin >> input_file;
    std::cout << "Введите имя файла для сохранения результатов: ";
    std::cin >> output_file;

    // Чтение данных учеников
    auto student_data = read_student_data_from_file(input_file);

    if (student_data.empty()) {
        std::cout << "Не удалось прочитать данные из файла или файл пуст.\n";
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }

    std::cout << "\nЗагружено " << student_data.size() << " записей.\n";
    std::cout << "Исходные данные (первые 5 записей):\n";

    int count = std::min(5, (int)student_data.size());
    for (int i = 0; i < count; i++) {
        std::cout << student_data[i].second << " " << student_data[i].first << std::endl;
    }

    if (student_data.size() > 5) {
        std::cout << "... и еще " << student_data.size() - 5 << " записей\n";
    }

    // Выполнение сортировки
    std::cout << "\nВыполняется сортировка...\n";
    shaker_sort_students(student_data);

    // Запись результатов в файл
    write_student_data_to_file(student_data, output_file);

    std::cout << "\nОтсортированные данные (первые 5 записей):\n";
    for (int i = 0; i < count; i++) {
        std::cout << std::left << std::setw(15) << student_data[i].second
                  << std::right << std::setw(3) << student_data[i].first << std::endl;
    }

    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
