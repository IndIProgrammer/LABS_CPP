#include "head.h"

// Реализация функций безопасного ввода
int safeInputInt(const std::string& prompt, int minVal, int maxVal) {
    int value;
    bool valid = false;

    while (!valid) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (minVal != -1 && value < minVal) {
                std::cout << "Ошибка: значение должно быть не меньше " << minVal << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else if (maxVal != -1 && value > maxVal) {
                std::cout << "Ошибка: значение должно быть не больше " << maxVal << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else {
                valid = true;
            }
        }
        else {
            std::cout << "Ошибка: введите целое число!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}
std::string safeInputString(const std::string& prompt, bool checkName) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);

    while (value.empty() || (checkName && !isValidName(value))) {
        if (value.empty()) {
            std::cout << "Ошибка: строка не может быть пустой! Введите снова: ";
        } else if (checkName && !isValidName(value)) {
            std::cout << "Ошибка: имя не может содержать цифры! Введите снова: ";
        }
        std::getline(std::cin, value);
    }

    return value;
}

// Проверка, что имя не содержит цифр
bool isValidName(const std::string& name) {
    for (char c : name) {
        if (isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Реализация класса Person
// Конструктор по умолчанию
Person::Person() : name(""), height(0) {}

// Конструктор
Person::Person(std::string n, int h) : name(n), height(h) {}

// Функция вывода на экран
void Person::print() const {
    std::cout << toString() << std::endl;
}

// Преобразование в строку
std::string Person::toString() const {
    return name + ", рост: " + std::to_string(height);
}

// Функции заполнения
void Person::inputFromKeyboard() {
    name = safeInputString("Введите имя: ", true);  // Добавили true для проверки
    height = safeInputInt("Введите рост (в см): ", 50, 250);
}

void Person::inputRandom() {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    std::vector<std::string> names = {"Клеопатра", "Пушкин", "Владимир", "Александр", "Мария", "Иван", "Екатерина", "Дмитрий"};

    name = names[rand() % names.size()];
    height = 50 + rand() % 201; // от 50 до 250
}

void Person::inputFromFile(std::ifstream& file) {
    std::getline(file, name);
    file >> height;
    file.ignore();
}

// Реализация класса Gun
// Конструктор по умолчанию
Gun::Gun() : bullets(5) {}

// Конструктор
Gun::Gun(int b) : bullets(b) {}

// Функция которая имитирует выстрел
void Gun::shoot() {
    if (bullets > 0) {
        std::cout << "Бах!" << std::endl;
        bullets--;
    }
    else {
        std::cout << "Клац!" << std::endl;
    }
}

// Вывод на экран
void Gun::print() const {
    std::cout << "Пистолет: патронов - " << bullets << std::endl;
}

// Функции заполнения
void Gun::inputFromKeyboard() {
    bullets = safeInputInt("Введите количество патронов (0-100): ", 0, 100);
}

void Gun::inputRandom() {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }
    bullets = rand() % 16; // от 0 до 15
}

void Gun::inputFromFile(std::ifstream& file) {
    file >> bullets;
    file.ignore();
}

// Реализация класса Name
// Конструктор по умолчанию
Name::Name() : surname(""), firstName(""), patronymic("") {}

// Только имя
Name::Name(std::string fn) : surname(""), firstName(fn), patronymic("") {}

// Имя фамилия
Name::Name(std::string fn, std::string s) : surname(s), firstName(fn), patronymic("") {}

// Конструктор (полный)
Name::Name(std::string fn, std::string s, std::string p) : surname(s), firstName(fn), patronymic(p) {}

// Вывод
void Name::print() const {
    std::cout << toString() << std::endl;
}

// Преобразование в строку
std::string Name::toString() const {
    std::string result;

    if (!surname.empty()) {
        result += surname + " ";
    }
    if (!firstName.empty()) {
        result += firstName + " ";
    }
    if (!patronymic.empty()) {
        result += patronymic;
    }

    while (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

// Функции заполнения
void Name::inputFromKeyboard() {
    std::cout << "Введите параметры имени (оставьте пустым, если параметр не задан):" << std::endl;

    std::cout << "Фамилия: ";
    std::getline(std::cin, surname);
    // Проверяем фамилию, если не пустая
    if (!surname.empty() && !isValidName(surname)) {
        std::cout << "Ошибка: фамилия не может содержать цифры! Очищаю поле." << std::endl;
        surname = "";
    }

    std::cout << "Имя: ";
    std::getline(std::cin, firstName);
    if (!firstName.empty() && !isValidName(firstName)) {
        std::cout << "Ошибка: имя не может содержать цифры! Очищаю поле." << std::endl;
        firstName = "";
    }

    std::cout << "Отчество: ";
    std::getline(std::cin, patronymic);
    if (!patronymic.empty() && !isValidName(patronymic)) {
        std::cout << "Ошибка: отчество не может содержать цифры! Очищаю поле." << std::endl;
        patronymic = "";
    }
}

void Name::inputRandom() {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    std::vector<std::string> surnames = {"Иванов", "Петров", "Сидоров", "Кузнецов", "Смирнов"};
    std::vector<std::string> firstNames = {"Александр", "Дмитрий", "Сергей", "Анна", "Мария"};
    std::vector<std::string> patronymics = {"Иванович", "Петрович", "Сергеевич", "Александровна", "Дмитриевна"};

    if (rand() % 3 < 2) { // вероятность 2/3
        surname = surnames[rand() % surnames.size()];
    }
    firstName = firstNames[rand() % firstNames.size()];
    if (rand() % 3 < 1) { // вероятность 1/3
        patronymic = patronymics[rand() % patronymics.size()];
    }
}

void Name::inputFromFile(std::ifstream& file) {
    std::string line;
    std::getline(file, line);

    // Очищаем все поля
    surname = "";
    firstName = "";
    patronymic = "";

    // Если строка пустая, пропускаем
    if (line.empty()) return;

    // Разбиваем строку на слова
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string word;

    while (ss >> word) {
        parts.push_back(word);
    }

    // В зависимости от количества слов определяем части имени
    if (parts.size() == 1) {
        // Только имя: "Клеопатра"
        firstName = parts[0];
    }
    else if (parts.size() == 2) {
        // Имя + фамилия: "Владимир Маяковский"
        firstName = parts[0];
        surname = parts[1];
    }
    else if (parts.size() == 3) {
        // Полное ФИО: "Александр Сергеевич Пушкин"
        firstName = parts[0];
        patronymic = parts[1];
        surname = parts[2];
    }
}

// Реализация класса Department
// Конструктор по умолчанию
Department::Department() : name(""), boss(nullptr) {}

// Название отдела
Department::Department(std::string n) : name(n), boss(nullptr) {}

// Конструктор с названием и начальником
Department::Department(std::string n, Employee* b) : name(n), boss(b) {}

// Установить начальника отдела
void Department::setBoss(Employee* b) {
    boss = b;
    if (b != nullptr && b->getDepartment() != this) {
        b->setDepartment(this);
    }
}

// Добавить сотрудников
void Department::addEmployee(Employee* emp) {
    if (emp != nullptr) {
        employees.push_back(emp);
        emp->setDepartment(this);
    }
}

// Вывод
void Department::print() const {
    std::cout << toString() << std::endl;
}

// Преобразование в строку
std::string Department::toString() const {
    std::string result = "Отдел: " + name;
    if (boss != nullptr) {
        result += ", начальник: " + boss->getName();
    }
    result += ", сотрудников: " + std::to_string(employees.size());
    return result;
}

// Функции заполнения
void Department::inputFromKeyboard(std::vector<Employee*>& /*employees*/) {
    name = safeInputString("Введите название отдела: ");
}

void Department::inputRandom(std::vector<Employee*>& employees) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    std::vector<std::string> deptNames = {"IT", "HR", "Sales", "Marketing", "Finance"};
    name = deptNames[rand() % deptNames.size()];
}

void Department::inputFromFile(std::ifstream& file, std::vector<Employee*>& employees) {
    std::getline(file, name);
}

// Реализация класса Employee
// Конструктор по умолчанию
Employee::Employee() : name(""), department(nullptr) {}

// Только имя сотрудника
Employee::Employee(std::string n) : name(n), department(nullptr) {}

// Конструктор с именем и отделом
Employee::Employee(std::string n, Department* dept) : name(n), department(dept) {}

// Установить отдел
void Employee::setDepartment(Department* dept) {
    department = dept;
}

// Вывод
void Employee::print() const {
    std::cout << toString() << std::endl;
}

// Преобразование в строку
std::string Employee::toString() const {
    if (department == nullptr) {
        return name + " не работает ни в одном отделе";
    }

    if (department->getBoss() == this) {
        return name + " начальник отдела " + department->getName();
    }
    else {
        std::string bossName = department->getBoss() != nullptr ? department->getBoss()->getName() : "не назначен";
        return name + " работает в отделе " + department->getName() + ", начальник которого " + bossName;
    }
}

// Функции заполнения
void Employee::inputFromKeyboard(std::vector<Department*>& depts) {
    name = safeInputString("Введите имя сотрудника: ", true);
}

void Employee::inputRandom(std::vector<Department*>& depts) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    std::vector<std::string> empNames = {"Петров", "Козлов", "Сидоров", "Иванов", "Смирнов", "Кузнецов"};
    name = empNames[rand() % empNames.size()];
}

void Employee::inputFromFile(std::ifstream& file, std::vector<Department*>& depts) {
    std::getline(file, name);
}

// Реализация класса ExtendedName
// Конструктор по умолчанию
ExtendedName::ExtendedName() : firstName(""), surname(""), patronymic("") {}

// Только имя
ExtendedName::ExtendedName(std::string fn) : firstName(fn), surname(""), patronymic("") {}

// Имя Фамилия
ExtendedName::ExtendedName(std::string fn, std::string s) : firstName(fn), surname(s), patronymic("") {}

// Полный конструктор
ExtendedName::ExtendedName(std::string fn, std::string s, std::string p) : firstName(fn), surname(s), patronymic(p) {}

// Вывод
void ExtendedName::print() const {
    std::cout << toString() << std::endl;
}

// Преобразование в строку
std::string ExtendedName::toString() const {
    std::string result;

    if (!surname.empty()) {
        result += surname + " ";
    }
    if (!firstName.empty()) {
        result += firstName + " ";
    }
    if (!patronymic.empty()) {
        result += patronymic;
    }

    while (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

// Заполнение
void ExtendedName::inputFromKeyboard() {
    std::cout << "Введите параметры имени (оставьте пустым, если параметр не задан):" << std::endl;

    std::cout << "Имя: ";
    std::getline(std::cin, firstName);
    if (!firstName.empty() && !isValidName(firstName)) {
        std::cout << "Ошибка: имя не может содержать цифры! Очищаю поле." << std::endl;
        firstName = "";
    }

    std::cout << "Фамилия: ";
    std::getline(std::cin, surname);
    if (!surname.empty() && !isValidName(surname)) {
        std::cout << "Ошибка: фамилия не может содержать цифры! Очищаю поле." << std::endl;
        surname = "";
    }

    std::cout << "Отчество: ";
    std::getline(std::cin, patronymic);
    if (!patronymic.empty() && !isValidName(patronymic)) {
        std::cout << "Ошибка: отчество не может содержать цифры! Очищаю поле." << std::endl;
        patronymic = "";
    }
}

void ExtendedName::inputRandom() {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    std::vector<std::string> surnames = {"Иванов", "Петров", "Сидоров", "Кузнецов", "Смирнов"};
    std::vector<std::string> firstNames = {"Александр", "Дмитрий", "Сергей", "Анна", "Мария"};
    std::vector<std::string> patronymics = {"Иванович", "Петрович", "Сергеевич", "Александровна", "Дмитриевна"};

    firstName = firstNames[rand() % firstNames.size()];
    if (rand() % 3 < 2) { // вероятность 2/3
        surname = surnames[rand() % surnames.size()];
    }
    if (rand() % 3 < 1) { // вероятность 1/3
        patronymic = patronymics[rand() % patronymics.size()];
    }
}

void ExtendedName::inputFromFile(std::ifstream& file) {
    std::string line;
    std::getline(file, line);

    // Пропускаем пустые строки
    while (line.empty() && !file.eof()) {
        std::getline(file, line);
    }

    // Если достигли конца файла, выходим
    if (file.eof() && line.empty()) return;

    // Очищаем все поля
    firstName = "";
    surname = "";
    patronymic = "";

    // Разбиваем строку на слова
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string word;

    while (ss >> word) {
        parts.push_back(word);
    }

    // В зависимости от количества слов определяем части имени
    if (parts.size() == 1) {
        // Только имя: "Клеопатра"
        firstName = parts[0];
    }
    else if (parts.size() == 2) {
        // Имя + фамилия: "Владимир Маяковский"
        firstName = parts[0];
        surname = parts[1];
    }
    else if (parts.size() == 3) {
        // Полное ФИО: "Александр Сергеевич Пушкин"
        firstName = parts[0];
        patronymic = parts[1];
        surname = parts[2];
    }
}

// Реализация класса AdvancedDepartment
// Конструктор по умолчанию
AdvancedDepartment::AdvancedDepartment() : name(""), boss(nullptr) {}
// Только название
AdvancedDepartment::AdvancedDepartment(std::string n) : name(n), boss(nullptr) {}
// Название и начальник отдела
AdvancedDepartment::AdvancedDepartment(std::string n, AdvancedEmployee* b) : name(n), boss(b) {}

// Назначить начальника
void AdvancedDepartment::setBoss(AdvancedEmployee* b) {
    boss = b;
    if (b != nullptr && b->getDepartment() != this) {
        b->setDepartment(this);
    }
}

// Добавить сотрудника
void AdvancedDepartment::addEmployee(AdvancedEmployee* emp) {
    if (emp != nullptr) {
        employees.push_back(emp);
        emp->setDepartment(this);
    }
}

// Вывод
void AdvancedDepartment::print() const {
    std::cout << toString() << std::endl;
}

// Преобразование в строку
std::string AdvancedDepartment::toString() const {
    std::string result = "Отдел: " + name;
    if (boss != nullptr) {
        result += ", начальник: " + boss->getName();
    }
    result += ", сотрудников: " + std::to_string(employees.size());
    return result;
}

// Заполнение
void AdvancedDepartment::inputFromKeyboard(std::vector<AdvancedEmployee*>& employees) {
    name = safeInputString("Введите название отдела: ");
}

void AdvancedDepartment::inputRandom(std::vector<AdvancedEmployee*>& employees) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    std::vector<std::string> deptNames = {"IT", "HR", "Sales", "Marketing", "Finance"};
    name = deptNames[rand() % deptNames.size()];
}

void AdvancedDepartment::inputFromFile(std::ifstream& file, std::vector<AdvancedEmployee*>& employees) {
    std::getline(file, name);
}

// Реализация класса AdvancedEmployee
// Конструктор по умолчанию
AdvancedEmployee::AdvancedEmployee() : name(""), department(nullptr) {}
// Только имя
AdvancedEmployee::AdvancedEmployee(std::string n) : name(n), department(nullptr) {}
// Имя и отдел
AdvancedEmployee::AdvancedEmployee(std::string n, AdvancedDepartment* dept) : name(n), department(dept) {}

// Установка отдела
void AdvancedEmployee::setDepartment(AdvancedDepartment* dept) {
    department = dept;
}

// Вывод
void AdvancedEmployee::print() const {
    std::cout << toString() << std::endl;
}

// Преобразование в строку
std::string AdvancedEmployee::toString() const {
    if (department == nullptr) {
        return name + " не работает ни в одном отделе";
    }

    if (department->getBoss() == this) {
        return name + " начальник отдела " + department->getName();
    }
    else {
        std::string bossName = department->getBoss() != nullptr ? department->getBoss()->getName() : "не назначен";
        return name + " работает в отделе " + department->getName() + ", начальник которого " + bossName;
    }
}

// Заполнение
void AdvancedEmployee::inputFromKeyboard(std::vector<AdvancedDepartment*>& depts) {
    name = safeInputString("Введите имя сотрудника: ", true);
}

void AdvancedEmployee::inputRandom(std::vector<AdvancedDepartment*>& depts) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    std::vector<std::string> empNames = {"Петров", "Козлов", "Сидоров", "Иванов", "Смирнов", "Кузнецов"};
    name = empNames[rand() % empNames.size()];
}

void AdvancedEmployee::inputFromFile(std::ifstream& file, std::vector<AdvancedDepartment*>& depts) {
    std::getline(file, name);
}
