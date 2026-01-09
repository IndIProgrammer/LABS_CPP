#ifndef UNTITLED4_HEAD_H
#define UNTITLED4_HEAD_H
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>

// Определяем структуру для результата
struct FitnessResult {
    int duration;
    int year;
    int month;

    // Для удобства сравнения
    bool operator<(const FitnessResult& other) const {
        if (duration != other.duration) {
            return duration < other.duration;
        }
        return year < other.year;
    }
};
struct ClientRecord {
    int duration;      // продолжительность занятий
    int client_code;   // код клиента
    int year;          // год
    int month;         // номер месяца
};

// Функция для задачи 2: обработка данных о клиентах
std::vector<FitnessResult> process_fitness_client_data(
        int target_client_code,
        const std::vector<ClientRecord>& records);

void show_main_menu();
void run_task1();
void run_task2();
void run_task3();

// Чтение массива чисел из файла
std::vector<int> read_int_array_from_file(const std::string& filename);

// Чтение данных учеников (балл, фамилия) из файла
std::vector<std::pair<int, std::string>> read_student_data_from_file(const std::string& filename);

// Запись отсортированных данных учеников в файл
void write_student_data_to_file(const std::vector<std::pair<int, std::string>>& data,
                                const std::string& filename);

// Чтение данных о клиентах фитнес-центра
std::vector<ClientRecord> read_client_records_from_stream(std::istream& input);

// Функция для задачи 3: шейкер-сортировка для пар (балл, фамилия)
void shaker_sort_students(std::vector<std::pair<int, std::string>>& data);

// Функция для задачи 1: сортировка пузырьком с выводом промежуточных результатов
void bubble_sort_with_protocol_combined(std::vector<int>& arr, const std::string& filename);
#endif
