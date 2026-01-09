#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
#include "headler.h"
//задача 1 - ExamTaskC4

//проверка сравнением на соответствие условию задачи
bool compareRecords(const FitnessRecord& a, const FitnessRecord& b) {
    if (a.duration != b.duration) {
        return a.duration > b.duration;
    }
    if (a.year != b.year) {
        return a.year > b.year;
    }
    return a.month > b.month;
}

//проверка на правильность значений
bool isValidRecord(const FitnessRecord& record) {
    // Проверка года
    if (record.year < 2000 || record.year > 2010) {
        std::cout << "Ошибка: год должен быть в диапазоне 2000-2010. Введено: "
                  << record.year << std::endl;
        return false;
    }

    // Проверка месяца
    if (record.month < 1 || record.month > 12) {
        std::cout << "Ошибка: месяц должен быть в диапазоне 1-12. Введено: "
                  << record.month << std::endl;
        return false;
    }

    // Проверка кода клиента
    if (record.clientCode < 10 || record.clientCode > 99) {
        std::cout << "Ошибка: код клиента должен быть в диапазоне 10-99. Введено: "
                  << record.clientCode << std::endl;
        return false;
    }

    // Проверка продолжительности занятий
    if (record.duration < 1 || record.duration > 30) {
        std::cout << "Ошибка: продолжительность занятий должна быть в диапазоне 1-30. Введено: "
                  << record.duration << std::endl;
        return false;
    }

    return true;
}

//ввод чисел с последующей проверкой
FitnessRecord inputRecordWithValidation(int recordNumber) {
    FitnessRecord record;
    bool isValid = false;

    while (!isValid) {
        std::cout << "Запись #" << recordNumber << " (месяц год код_клиента продолжительность): ";

        // Проверка корректности ввода всех чисел
        if (!(std::cin >> record.month >> record.year
                       >> record.clientCode >> record.duration)) {
            std::cout << "Ошибка: введены некорректные данные. Пожалуйста, введите целые числа.\n";
            std::cin.clear(); // Сброс флагов ошибок
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            continue;
        }

        // Проверка диапазонов
        if (isValidRecord(record)) {
            isValid = true;
        } else {
            std::cout << "Пожалуйста, введите данные заново.\n";
        }
    }

    return record;
}

//user(less)interface for zadacha 1
void solveTask1() {
    using namespace std;
    cout << "\n=== Задача 1: Фитнес-центр ===\n";

    int N;
    cout << "Введите количество записей N: ";

    // Проверка корректности ввода N
    while (!(cin >> N) || N <= 0) {
        cout << "Ошибка: N должно быть положительным целым числом. Введите снова: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<FitnessRecord> records;
    records.reserve(N); // Резервируем память заранее

    cout << "Введите данные для каждой записи:\n";
    for (int i = 0; i < N; i++) {
        FitnessRecord record = inputRecordWithValidation(i + 1);
        records.push_back(record);
    }

    if (records.empty()) {
        cout << "Нет корректных записей для обработки.\n";
        return;
    }

    sort(records.begin(), records.end(), compareRecords);

    cout << "\nРезультат:\n";
    cout << "Максимальная продолжительность: " << records[0].duration << endl;
    cout << "Год: " << records[0].year << endl;
    cout << "Месяц: " << records[0].month << endl;

    // Дополнительно: вывод информации о клиенте с максимальной продолжительностью
    cout << "Код клиента: " << records[0].clientCode << endl;

    // Если есть несколько записей с одинаковой максимальной продолжительностью
    if (records.size() > 1 && records[0].duration == records[1].duration) {
        cout << "\nПримечание: есть несколько записей с максимальной продолжительностью.\n";
        cout << "Выбрана самая поздняя дата.\n";
    }
}

//задача 2 - номер 2

// Функция для безопасного ввода целого числа с проверкой диапазона
short inputShortWithValidation(const std::string& prompt, short minVal, short maxVal) {
    short value;
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> value)) {
            std::cout << "Ошибка: введите целое число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (value < minVal || value > maxVal) {
            std::cout << "Ошибка: значение должно быть от " << minVal
                      << " до " << maxVal << ". Попробуйте снова.\n";
            continue;
        }
        return value;
    }
}

// Функция для безопасного ввода дробного числа с проверкой диапазона
float inputFloatWithValidation(const std::string& prompt, float minVal, float maxVal) {
    float value;
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> value)) {
            std::cout << "Ошибка: введите число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (value < minVal || value > maxVal) {
            std::cout << "Ошибка: значение должно быть от " << minVal
                      << " до " << maxVal << ". Попробуйте снова.\n";
            continue;
        }
        return value;
    }
}

// Функция для ввода номера класса с проверкой
int inputClassNumber() {
    int classNum;
    while (true) {
        std::cout << "Класс (1-4): ";
        if (!(std::cin >> classNum)) {
            std::cout << "Ошибка: введите целое число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (classNum < 1 || classNum > 4) {
            std::cout << "Ошибка: класс должен быть от 1 до 4. Попробуйте снова.\n";
            continue;
        }
        return classNum;
    }
}

//ввод данных ученика
void inputStudent(Student& student) {
    using namespace std;
    cout << "\nВведите данные ученика:\n";
    cout << "Фамилия: ";
    cin >> student.lastName;
    cout << "Имя: ";
    cin >> student.firstName;

    student.classNum = inputClassNumber();

    switch(student.classNum) {
        case 1:
            student.data.readingSpeed = inputShortWithValidation(
                    "Скорость чтения (слов/мин, от 1 до 1000): ", 1, 1000);
            break;
        case 2:
        case 3:
            student.data.mathScore = inputShortWithValidation(
                    "Оценка по математике (от 1 до 10): ", 1, 10);
            break;
        case 4:
            student.data.examScore = inputFloatWithValidation(
                    "Баллы итоговой аттестации (от 1 до 100): ", 1.0f, 100.0f);
            break;
    }
}

//user(less)interface for zadacha 2 и колдунства
void solveTask2() {
    using namespace std;
    cout << "\n=== Задача 2: Ученики младшей школы ===\n";

    int N;
    while (true) {
        cout << "Введите количество учеников: ";
        if (!(cin >> N)) {
            cout << "Ошибка: введите целое число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (N <= 0) {
            cout << "Ошибка: количество учеников должно быть положительным.\n";
            continue;
        }
        break;
    }

    vector<Student> students;
    students.reserve(N);

    for (int i = 0; i < N; i++) {
        cout << "\n=== Ученик #" << i + 1 << " ===";
        Student student;
        inputStudent(student);
        students.push_back(student);
    }

    // Сохранение в файл
    ofstream outFile("students.txt");
    if (!outFile) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    // Заголовок таблицы
    outFile << left << setw(15) << "Фамилия"
            << setw(15) << "Имя"
            << setw(8) << "Класс"
            << "Дополнительная информация\n";
    outFile << string(60, '-') << "\n";

    for (const auto& student : students) {
        outFile << left << setw(15) << student.lastName
                << setw(15) << student.firstName
                << setw(8) << student.classNum;

        switch(student.classNum) {
            case 1:
                outFile << "Чтение: " << student.data.readingSpeed << " слов/мин";
                break;
            case 2:
            case 3:
                outFile << "Математика: " << student.data.mathScore << " баллов";
                break;
            case 4:
                outFile << "Аттестация: " << fixed << setprecision(1)
                        << student.data.examScore << " баллов";
                break;
        }
        outFile << "\n";
    }
    outFile.close();

    cout << "\nДанные успешно сохранены в файл students.txt\n";

    // Чтение и вывод содержимого файла
    cout << "\n" << string(60, '=') << "\n";
    cout << "СОДЕРЖИМОЕ ФАЙЛА students.txt:\n";
    cout << string(60, '=') << "\n";

    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "Ошибка открытия файла для чтения!\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        cout << line << "\n";
    }
    inFile.close();
}

//задача 3 - номер 1
const std::string FILENAME = "books.txt";
std::vector<Book> books;

// Функции для работы с файлом
void loadBooksFromFile() {
    std::ifstream file(FILENAME);
    if (!file) return;

    books.clear();
    std::string line;

    while (std::getline(file, line)) {
        Book book;
        book.title = line;

        if (std::getline(file, book.author)) {
            file >> book.year;
            file.ignore(); // Игнорируем символ новой строки
            books.push_back(book);
        }
    }
    file.close();
}

//сохранить данные в файл
void saveBooksToFile() {
    std::ofstream file(FILENAME);
    for (const auto& book : books) {
        file << book.title << "\n"
             << book.author << "\n"
             << book.year << "\n";
    }
    file.close();
}

// Основные функции для работы с книгами

//добавить книгу
void addBook(const Book& book) {
    books.push_back(book);
    std::cout << "Книга добавлена успешно!\n";
}

//вывести список всех книг
//заголовок таблички
void displayAllBooks() {
    if (books.empty()) {
        std::cout << "Список книг пуст.\n";
        return;
    }

    std::cout << "\nСписок всех книг:\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << std::left << std::setw(5) << "№"
              << std::setw(25) << "Название"
              << std::setw(20) << "Автор"
              << std::setw(10) << "Год" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (size_t i = 0; i < books.size(); i++) {
        std::cout << std::setw(5) << i + 1
                  << std::setw(25) << books[i].title
                  << std::setw(20) << books[i].author
                  << std::setw(10) << books[i].year << "\n";
    }
}
//сами книги
void displayBook(const Book& book) {
    std::cout << "\nИнформация о книге:\n";
    std::cout << "Название: " << book.title << "\n";
    std::cout << "Автор: " << book.author << "\n";
    std::cout << "Год издания: " << book.year << "\n";
}

//поиск книги по автору
std::vector<Book> searchBooksByAuthor(const std::string& author) {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (book.author.find(author) != std::string::npos) {
            result.push_back(book);
        }
    }
    return result;
}
//поиск по названию
std::vector<Book> searchBooksByTitle(const std::string& titlePart) {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (book.title.find(titlePart) != std::string::npos) {
            result.push_back(book);
        }
    }
    return result;
}

//редактировать заголовок автора и год книги
bool editBook(int index, const Book& newBook) {
    if (index < 0 || index >= (int)books.size()) {
        return false;
    }
    books[index] = newBook;
    return true;
}

//удалить книгу
bool deleteBook(int index) {
    if (index < 0 || index >= (int)books.size()) {
        return false;
    }
    books.erase(books.begin() + index);
    return true;
}

// Меню управления книгами
void solveTask3() {
    using namespace std;
    cout << "\n=== Задача 3: Управление книгами ===\n";

    loadBooksFromFile();
    int choice;

    do {
        cout << "\n--- Меню управления книгами ---\n";
        cout << "1. Добавить новую книгу\n";
        cout << "2. Показать все книги\n";
        cout << "3. Найти книгу по автору\n";
        cout << "4. Найти книгу по названию\n";
        cout << "5. Редактировать книгу\n";
        cout << "6. Удалить книгу\n";
        cout << "0. Вернуться в главное меню\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                Book book;
                cout << "Введите название книги: ";
                getline(cin, book.title);
                cout << "Введите автора: ";
                getline(cin, book.author);
                cout << "Введите год издания: ";
                cin >> book.year;
                cin.ignore();
                addBook(book);
                saveBooksToFile();
                break;
            }
            case 2:
                displayAllBooks();
                break;
            case 3: {
                string author;
                cout << "Введите автора для поиска: ";
                getline(cin, author);
                auto results = searchBooksByAuthor(author);
                if (results.empty()) {
                    cout << "Книги не найдены.\n";
                } else {
                    cout << "\nНайдено " << results.size() << " книг:\n";
                    for (const auto& book : results) {
                        displayBook(book);
                    }
                }
                break;
            }
            case 4: {
                string title;
                cout << "Введите часть названия для поиска: ";
                getline(cin, title);
                auto results = searchBooksByTitle(title);
                if (results.empty()) {
                    cout << "Книги не найдены.\n";
                } else {
                    cout << "\nНайдено " << results.size() << " книг:\n";
                    for (const auto& book : results) {
                        displayBook(book);
                    }
                }
                break;
            }
            case 5: {
                displayAllBooks();
                if (!books.empty()) {
                    int index;
                    cout << "Введите номер книги для редактирования: ";
                    cin >> index;
                    cin.ignore();
                    if (index > 0 && index <= (int)books.size()) {
                        Book newBook;
                        cout << "Введите новое название: ";
                        getline(cin, newBook.title);
                        cout << "Введите нового автора: ";
                        getline(cin, newBook.author);
                        cout << "Введите новый год: ";
                        cin >> newBook.year;
                        cin.ignore();

                        if (editBook(index - 1, newBook)) {
                            cout << "Книга успешно отредактирована!\n";
                            saveBooksToFile();
                        } else {
                            cout << "Ошибка редактирования!\n";
                        }
                    } else {
                        cout << "Неверный номер книги!\n";
                    }
                }
                break;
            }
            case 6: {
                displayAllBooks();
                if (!books.empty()) {
                    int index;
                    cout << "Введите номер книги для удаления: ";
                    cin >> index;
                    cin.ignore();
                    if (index > 0 && index <= (int)books.size()) {
                        if (deleteBook(index - 1)) {
                            cout << "Книга успешно удалена!\n";
                            saveBooksToFile();
                        } else {
                            cout << "Ошибка удаления!\n";
                        }
                    } else {
                        cout << "Неверный номер книги!\n";
                    }
                }
                break;
            }
            case 0:
                saveBooksToFile();
                cout << "Возврат в главное меню...\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    } while (choice != 0);
}
