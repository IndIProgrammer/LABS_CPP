#include "head.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

void backtrack(int index,
               std::vector<int>& current,
               int currentWeight,
               int currentTax,
               const std::vector<int>& weights,
               const std::vector<int>& taxes,
               int Z, int N,
               std::vector<int>& bestCombination,
               int& bestWeight,
               int& minTax,
               bool& foundSolution) {

    // Если вес превысил Z и (это первое решение или налог меньше текущего минимума)
    if (currentWeight > Z && (!foundSolution || currentTax < minTax)) {
        minTax = currentTax;
        bestWeight = currentWeight;
        bestCombination = current;
        foundSolution = true;
    }

    if (index == N) return;

    // Взять текущий артефакт
    current.push_back(index);
    backtrack(index + 1, current,
              currentWeight + weights[index],
              currentTax + taxes[index],
              weights, taxes, Z, N,
              bestCombination, bestWeight, minTax, foundSolution);
    current.pop_back();

    // Не брать текущий артефакт
    backtrack(index + 1, current,
              currentWeight, currentTax,
              weights, taxes, Z, N,
              bestCombination, bestWeight, minTax, foundSolution);
}

void BackRec10() {
    std::ifstream in("input_backrec10.txt");
    if (!in.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл input_backrec10.txt\n";
        std::cout << "Убедитесь, что файл существует в той же папке.\n";
        return;
    }

    std::ofstream out("output_backrec10.txt");

    int N, Z;
    in >> N >> Z;

    std::cout << "Прочитано из файла: N=" << N << ", Z=" << Z << std::endl;

    std::vector<int> weights(N);
    std::vector<int> taxes(N);

    for (int i = 0; i < N; i++) in >> weights[i];
    for (int i = 0; i < N; i++) in >> taxes[i];

    // Выводим прочитанные данные
    std::cout << "Веса артефактов: ";
    for (int w : weights) std::cout << w << " ";
    std::cout << "\nНалоги артефактов: ";
    for (int t : taxes) std::cout << t << " ";
    std::cout << std::endl;

    // Локальные переменные для хранения лучшего решения
    std::vector<int> bestCombination;
    int bestWeight = 0;
    int minTax = 0;
    bool foundSolution = false;

    std::vector<int> current;

    std::cout << "Выполняется поиск решения...\n";
    backtrack(0, current, 0, 0,
              weights, taxes, Z, N,
              bestCombination, bestWeight, minTax, foundSolution);

    if (foundSolution) {
        out << "Номера артефактов: ";
        for (int idx : bestCombination) {
            out << idx + 1 << " ";
        }
        out << std::endl;
        out << "Суммарный вес: " << bestWeight << std::endl;
        out << "Суммарное налоговое бремя: " << minTax << std::endl;

        // Выводим результат в консоль
        std::cout << "\nРешение найдено!\n";
        std::cout << "Выбранные артефакты (номера): ";
        for (int idx : bestCombination) {
            std::cout << idx + 1 << " ";
        }
        std::cout << "\nСуммарный вес: " << bestWeight << " кг\n";
        std::cout << "Суммарный налог: " << minTax << std::endl;
        std::cout << "Полный результат записан в output_backrec10.txt\n";
    } else {
        out << "Решение не найдено (нет комбинации с весом > " << Z << ")" << std::endl;
        std::cout << "\nРешение не найдено. Нет комбинации с весом > " << Z << std::endl;
    }

    in.close();
    out.close();
}


void HomeDyn4() {
    std::cout << "HomeDyn4: Хромой король\n";

    std::ifstream in("input_homedyn4.txt");
    if (!in.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл input_homedyn4.txt\n";
        std::cout << "Убедитесь, что файл существует в той же папке.\n";
        return;
    }

    std::ofstream out("output_homedyn4.txt");

    int N;
    in >> N;

    std::cout << "Размер доски: " << N << "x" << N << std::endl;

    // Создаем доску
    std::vector<std::vector<int>> board(N, std::vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            in >> board[i][j];
        }
    }

    std::cout << "Данные успешно загружены из файла.\n";

    // DP таблица для минимальных неприятностей
    std::vector<std::vector<int>> dp(N, std::vector<int>(N, 0));
    std::vector<std::vector<char>> dir(N, std::vector<char>(N, ' '));

    // Инициализируем начальную позицию (правый верхний угол)
    dp[0][N-1] = board[0][N-1];

    // Заполняем первую строку (движение только влево)
    for (int j = N-2; j >= 0; j--) {
        dp[0][j] = dp[0][j+1] + board[0][j];
        dir[0][j] = 'L';
    }

    // Заполняем последний столбец (движение только вниз)
    for (int i = 1; i < N; i++) {
        dp[i][N-1] = dp[i-1][N-1] + board[i][N-1];
        dir[i][N-1] = 'D';
    }

    // Заполняем остальную таблицу
    for (int i = 1; i < N; i++) {
        for (int j = N-2; j >= 0; j--) {
            int fromTop = dp[i-1][j];
            int fromLeft = dp[i][j+1];

            if (fromTop < fromLeft) {
                dp[i][j] = fromTop + board[i][j];
                dir[i][j] = 'D';
            } else {
                dp[i][j] = fromLeft + board[i][j];
                dir[i][j] = 'L';
            }
        }
    }

    std::cout << "Вычисление завершено.\n";

    // Восстанавливаем путь
    std::string path;
    int i = N-1, j = 0;

    while (i > 0 || j < N-1) {
        if (dir[i][j] == 'D') {
            path = 'D' + path;
            i--;
        } else {
            path = 'L' + path;
            j++;
        }
    }

    int minSum = dp[N-1][0];

    // Записываем в файл
    out << minSum << std::endl;
    out << path << std::endl;

    std::cout << "РЕЗУЛЬТАТЫ:\n";
    std::cout << "Минимальная сумма неприятностей: " << minSum << std::endl;
    std::cout << "Путь короля: " << path << std::endl;
    std::cout << "\nПояснение:\n";
    std::cout << "  L - движение влево\n";
    std::cout << "  D - движение вниз\n";
    std::cout << "Путь начинается с правого верхнего угла (0," << N-1 << ")\n";
    std::cout << "и заканчивается в левом нижнем (" << N-1 << ",0)\n";
    std::cout << "Результат записан в output_homedyn4.txt\n";
    in.close();
    out.close();
}


// Вспомогательная функция для расчета количества чисел
double calculateNumbersWithMoreThanThreeZeros(int K, int N) {
    if (N <= 3) {
        return 0.0;
    }

    // dp[pos][zeros] - количество чисел длины pos с zeros нулями подряд в конце
    std::vector<std::vector<double>> dp(N + 1, std::vector<double>(4, 0.0));

    // Инициализация для длины 1
    dp[1][0] = K - 1; // любая ненулевая цифра
    dp[1][1] = 1.0;   // одна цифра 0

    // Заполнение таблицы
    for (int pos = 2; pos <= N; pos++) {
        // Заканчивается на 1, 2, 3 нуля подряд
        for (int zeros = 1; zeros <= 3; zeros++) {
            dp[pos][zeros] = dp[pos - 1][zeros - 1];
        }

        // Заканчивается не на нуль
        double sum = 0.0;
        for (int zeros = 0; zeros <= 3; zeros++) {
            sum += dp[pos - 1][zeros];
        }
        dp[pos][0] = (K - 1) * sum;
    }

    // Общее количество всех K-ичных чисел длины N
    double totalNumbers = 1.0;
    for (int i = 0; i < N; i++) {
        totalNumbers *= K;
    }

    // Числа с не более чем 3 нулями подряд
    double goodNumbers = 0.0;
    for (int zeros = 0; zeros <= 3; zeros++) {
        goodNumbers += dp[N][zeros];
    }

    // Числа с более чем 3 нулями подряд
    return totalNumbers - goodNumbers;
}

void HomeDyn16() {
    int K, N;

    // Ввод данных с проверкой
    bool validInput = false;
    while (!validInput) {
        std::cout << "Введите основание системы счисления K (2 <= K <= 10): ";
        std::cin >> K;

        if (K < 2 || K > 10) {
            std::cout << "Ошибка: K должно быть от 2 до 10 включительно.\n";
            continue;
        }

        std::cout << "Введите количество разрядов N (1 < N < 20, N+K < 26): ";
        std::cin >> N;

        if (N <= 1 || N >= 20) {
            std::cout << "Ошибка: N должно быть больше 1 и меньше 20.\n";
            continue;
        }

        if (N + K >= 26) {
            std::cout << "Ошибка: сумма N+K должна быть меньше 26.\n";
            continue;
        }

        validInput = true;
    }

    // Вычисление результата
    double result = calculateNumbersWithMoreThanThreeZeros(K, N);

    std::cout << "РЕЗУЛЬТАТЫ:\n";
    std::cout << "Основание системы счисления (K): " << K << std::endl;
    std::cout << "Количество разрядов (N): " << N << std::endl;
    std::cout << "Всего " << K << "-ичных чисел длины " << N << ": "
              << std::fixed << std::setprecision(0) << pow(K, N) << std::endl;
    std::cout << "Чисел с более чем 3 нулями подряд: "
              << std::fixed << std::setprecision(0) << result << std::endl;
}
