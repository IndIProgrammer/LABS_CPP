#include "head.h"

void showMainMenu() {
    std::cout << "ГЛАВНОЕ МЕНЮ" << std::endl;
    std::cout << "1. Задача 1: Человек" << std::endl;
    std::cout << "2. Задача 2: Пистолет" << std::endl;
    std::cout << "3. Задача 3: Имена (три параметра)" << std::endl;
    std::cout << "4. Задача 4: Сотрудники и отделы" << std::endl;
    std::cout << "5. Задача 5: Имена (расширенная версия)" << std::endl;
    std::cout << "6. Задача 6: Сотрудники и отделы (с получением списка)" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите задачу: ";
}

void showInputMethodMenu() {
    std::cout << "\nВыберите способ заполнения данных:" << std::endl;
    std::cout << "1. С клавиатуры" << std::endl;
    std::cout << "2. Рандомно" << std::endl;
    std::cout << "3. Из файла" << std::endl;
    std::cout << "Ваш выбор: ";
}

// Задача 1: Человек
void task1() {
    std::cout << "\nЗАДАЧА 1: Человек" << std::endl;

    std::vector<Person> persons;  // Вектор для хранения 3 объектов Person
    int choice;

    showInputMethodMenu();
    choice = safeInputInt("", 1, 3);

    if (choice == 1) {
        // С клавиатуры
        for (int i = 0; i < 3; i++) {
            std::cout << "\nВведите данные для человека " << (i + 1) << ":" << std::endl;
            Person p;
            p.inputFromKeyboard();
            persons.push_back(p);
        }
    }
    else if (choice == 2) {
        // Рандомно
        for (int i = 0; i < 3; i++) {
            Person p;
            p.inputRandom();
            persons.push_back(p);
        }
    }
    else if (choice == 3) {
        // Из файла
        std::string filename = "persons.txt";
        std::ifstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < 3 && !file.eof(); i++) {
                Person p;
                p.inputFromFile(file);
                persons.push_back(p);
            }
            file.close();
        }
        else {
            std::cout << "Ошибка: не удалось открыть файл " << filename << "! Использую значения по умолчанию." << std::endl;
            persons.push_back(Person("Клеопатра", 152));
            persons.push_back(Person("Пушкин", 167));
            persons.push_back(Person("Владимир", 189));
        }
    }

    std::cout << "\nРезультат:" << std::endl;
    // const auto& - константная ссылка, чтобы не копировать объекты
    for (const auto& p : persons) {
        p.print();
    }
}

// Задача 2: Пистолет
void task2() {
    std::cout << "\nЗАДАЧА 2: Пистолет" << std::endl;

    Gun gun;
    int choice;

    showInputMethodMenu();
    choice = safeInputInt("", 1, 3);

    if (choice == 1) {
        gun.inputFromKeyboard();
    }
    else if (choice == 2) {
        gun.inputRandom();
        std::cout << "Сгенерировано: ";
        gun.print();
    }
    else if (choice == 3) {
        std::string filename = "gun.txt";
        std::ifstream file(filename);
        if (file.is_open()) {
            gun.inputFromFile(file);
            file.close();
        }
        else {
            std::cout << "Ошибка: не удалось открыть файл " << filename << "! Использую значение по умолчанию (3 патрона)." << std::endl;
            gun = Gun(3);
        }
    }

    std::cout << "\nСоздан пистолет с " << gun.getBullets() << " патронами" << std::endl;
    std::cout << "\nВыполняем 5 выстрелов:" << std::endl;

    for (int i = 0; i < 5; i++) {
        std::cout << "Выстрел " << (i + 1) << ": ";
        gun.shoot();  // При вызове уменьшается количество патронов
    }
}

// Задача 3: Имена (три параметра)
void task3() {
    std::cout << "\nЗАДАЧА 3: Имена" << std::endl;

    std::vector<Name> names;
    int choice;

    showInputMethodMenu();
    choice = safeInputInt("", 1, 3);

    if (choice == 1) {
        // С клавиатуры
        for (int i = 0; i < 3; i++) {
            std::cout << "\nВведите данные для имени " << (i + 1) << ":" << std::endl;
            Name n;
            n.inputFromKeyboard();  // Ввод фамилии, имени, отчества (можно пустые строки)
            names.push_back(n);
        }
    }
    else if (choice == 2) {
        // Рандомно
        for (int i = 0; i < 3; i++) {
            Name n;
            n.inputRandom();
            names.push_back(n);
        }
    }
    else if (choice == 3) {
        // Из файла
        std::string filename = "names.txt";
        std::ifstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < 3 && !file.eof(); i++) {
                Name n;
                n.inputFromFile(file);
                names.push_back(n);
            }
            file.close();
        }
        else {
            std::cout << "Ошибка: не удалось открыть файл " << filename << "! Использую значения по умолчанию." << std::endl;
            names.push_back(Name("Клеопатра"));  // Только имя
            names.push_back(Name("Александр", "Пушкин", "Сергеевич"));  // Полное ФИО
            names.push_back(Name("Владимир", "Маяковский"));  // Имя + фамилия
        }
    }

    std::cout << "\nРезультат:" << std::endl;
    for (const auto& n : names) {
        n.print();
    }
}

// Задача 4: Сотрудники и отделы
void task4() {
    std::cout << "\nЗАДАЧА 4: Сотрудники и отделы" << std::endl;

    // ВАЖНО: new создает объект в динамической памяти
    // Отдел существует независимо от функции и будет удален вручную
    Department* itDept = new Department("IT");  // Указатель на объект отдела
    std::vector<Employee*> employees;  // Вектор указателей на сотрудников
    std::vector<Department*> departments;  // Вектор указателей на отделы
    departments.push_back(itDept);  // Добавляем отдел в список доступных

    int choice;
    showInputMethodMenu();
    choice = safeInputInt("", 1, 3);

    if (choice == 1) {
        // С клавиатуры
        for (int i = 0; i < 3; i++) {
            std::cout << "\nВведите данные для сотрудника " << (i + 1) << ":" << std::endl;
            Employee* emp = new Employee();  // Динамическое создание сотрудника
            emp->inputFromKeyboard(departments);  // Ввод имени
            employees.push_back(emp);  // Сохраняем указатель
        }

        // Добавляем сотрудников в отдел
        for (auto emp : employees) {
            itDept->addEmployee(emp);
        }

        // Выбор начальника
        std::cout << "\nКого хотите назначить начальником?" << std::endl;
        for (size_t i = 0; i < employees.size(); i++) {
            std::cout << (i + 1) << ". " << employees[i]->getName() << std::endl;
        }

        int bossChoice = safeInputInt("Ваш выбор (1-3): ", 1, 3);
        itDept->setBoss(employees[bossChoice - 1]);
    }
    else if (choice == 2) {
        // Рандомно
        for (int i = 0; i < 3; i++) {
            Employee* emp = new Employee();
            emp->inputRandom(departments);
            employees.push_back(emp);
        }

        // Добавляем сотрудников в отдел
        for (auto emp : employees) {
            itDept->addEmployee(emp);
        }

        // Делаем случайного начальником
        itDept->setBoss(employees[rand() % 3]);
    }
    else if (choice == 3) {
        // Из файла
        std::string filename = "employees.txt";
        std::ifstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < 3 && !file.eof(); i++) {
                Employee* emp = new Employee();
                emp->inputFromFile(file, departments);
                employees.push_back(emp);
            }
            file.close();
        }
        else {
            std::cout << "Ошибка: не удалось открыть файл " << filename << "! Использую значения по умолчанию." << std::endl;
            employees.push_back(new Employee("Петров"));
            employees.push_back(new Employee("Козлов"));
            employees.push_back(new Employee("Сидоров"));
        }

        // Добавляем сотрудников в отдел
        for (auto emp : employees) {
            itDept->addEmployee(emp);
        }

        // Делаем Козлова начальником
        for (auto emp : employees) {
            if (emp->getName() == "Козлов") {
                itDept->setBoss(emp);
                break;
            }
        }
    }

    std::cout << "\nРезультат:" << std::endl;
    for (auto emp : employees) {
        emp->print();
    }

    // Очистка памяти
    for (auto emp : employees) {
        delete emp;
    }
    delete itDept;
}

// Задача 5: Имена (расширенная версия)
void task5() {
    std::cout << "\nЗАДАЧА 5: Имена (расширенная версия)" << std::endl;

    std::vector<ExtendedName> names;
    int choice;

    showInputMethodMenu();
    choice = safeInputInt("", 1, 3);

    if (choice == 1) {
        // С клавиатуры
        for (int i = 0; i < 4; i++) {
            std::cout << "\nВведите данные для имени " << (i + 1) << ":" << std::endl;
            ExtendedName n;
            n.inputFromKeyboard();
            names.push_back(n);
        }
    }
    else if (choice == 2) {
        // Рандомно
        for (int i = 0; i < 4; i++) {
            ExtendedName n;
            n.inputRandom();
            names.push_back(n);
        }
    }
    else if (choice == 3) {
        // Из файла
        std::string filename = "extended_names.txt";
        std::ifstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < 4 && !file.eof(); i++) {
                ExtendedName n;
                n.inputFromFile(file);
                names.push_back(n);
            }
            file.close();
        }
        else {
            std::cout << "Ошибка: не удалось открыть файл " << filename << "! Использую значения по умолчанию." << std::endl;
            names.push_back(ExtendedName("Клеопатра"));
            names.push_back(ExtendedName("Александр", "Пушкин", "Сергеевич"));
            names.push_back(ExtendedName("Владимир", "Маяковский"));
            names.push_back(ExtendedName("Христофор", "", "Бонифатьевич"));
        }
    }

    std::cout << "\nРезультат:" << std::endl;
    for (const auto& n : names) {
        n.print();
    }
}

// Задача 6: Сотрудники и отделы с возможностью получить список
void task6() {
    std::cout << "\nЗАДАЧА 6: Сотрудники и отделы (с получением списка)" << std::endl;

    AdvancedDepartment* itDept = new AdvancedDepartment("IT");
    std::vector<AdvancedEmployee*> employees;
    std::vector<AdvancedDepartment*> departments;
    departments.push_back(itDept);

    int choice;
    showInputMethodMenu();
    choice = safeInputInt("", 1, 3);

    if (choice == 1) {
        // С клавиатуры
        for (int i = 0; i < 3; i++) {
            std::cout << "\nВведите данные для сотрудника " << (i + 1) << ":" << std::endl;
            AdvancedEmployee* emp = new AdvancedEmployee();
            emp->inputFromKeyboard(departments);
            employees.push_back(emp);
        }

        // Добавляем сотрудников в отдел
        for (auto emp : employees) {
            itDept->addEmployee(emp);
        }

        // Выбор начальника
        std::cout << "\nКого хотите назначить начальником?" << std::endl;
        for (size_t i = 0; i < employees.size(); i++) {
            std::cout << (i + 1) << ". " << employees[i]->getName() << std::endl;
        }

        int bossChoice = safeInputInt("Ваш выбор (1-3): ", 1, 3);
        itDept->setBoss(employees[bossChoice - 1]);
    }
    else if (choice == 2) {
        // Рандомно
        for (int i = 0; i < 3; i++) {
            AdvancedEmployee* emp = new AdvancedEmployee();
            emp->inputRandom(departments);
            employees.push_back(emp);
        }

        // Добавляем сотрудников в отдел
        for (auto emp : employees) {
            itDept->addEmployee(emp);
        }

        // Делаем случайного начальником
        itDept->setBoss(employees[rand() % 3]);
    }
    else if (choice == 3) {
        // Из файла
        std::string filename = "advanced_employees.txt";
        std::ifstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < 3 && !file.eof(); i++) {
                AdvancedEmployee* emp = new AdvancedEmployee();
                emp->inputFromFile(file, departments);
                employees.push_back(emp);
            }
            file.close();
        }
        else {
            std::cout << "Ошибка: не удалось открыть файл " << filename << "! Использую значения по умолчанию." << std::endl;
            employees.push_back(new AdvancedEmployee("Петров"));
            employees.push_back(new AdvancedEmployee("Козлов"));
            employees.push_back(new AdvancedEmployee("Сидоров"));
        }

        // Добавляем сотрудников в отдел
        for (auto emp : employees) {
            itDept->addEmployee(emp);
        }

        // Делаем Козлова начальником
        for (auto emp : employees) {
            if (emp->getName() == "Козлов") {
                itDept->setBoss(emp);
                break;
            }
        }
    }

    std::cout << "\nРезультат:" << std::endl;
    for (auto emp : employees) {
        emp->print();
    }

    std::cout << "Демонстрация: имея ссылку на сотрудника, можно узнать список всех сотрудников отдела" << std::endl;

    // Выводим список всех сотрудников для выбора
    std::cout << "\nВыберите сотрудника, через которого хотите узнать коллег:" << std::endl;
    for (size_t i = 0; i < employees.size(); i++) {
        std::cout << (i + 1) << ". " << employees[i]->getName() << std::endl;
    }

    int empChoice = safeInputInt("Ваш выбор (1-" + std::to_string(employees.size()) + "): ", 1, employees.size());
    AdvancedEmployee* selectedEmp = employees[empChoice - 1];

    // Через выбранного сотрудника получаем список всего отдела
    if (selectedEmp->getDepartment() != nullptr) {
        std::vector<AdvancedEmployee*> deptEmps = selectedEmp->getDepartment()->getAllEmployees();

        std::cout << "\nСотрудник " << selectedEmp->getName() << " работает в отделе "
                  << selectedEmp->getDepartment()->getName() << ", где есть:" << std::endl;

        for (auto deptEmp : deptEmps) {
            std::cout << "  - " << deptEmp->getName();
            if (deptEmp == selectedEmp->getDepartment()->getBoss()) {
                std::cout << " (начальник)";
            }
            if (deptEmp == selectedEmp) {
                std::cout << " (это я)";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "Ошибка: выбранный сотрудник не привязан к отделу!" << std::endl;
    }

    // Очистка памяти
    for (auto emp : employees) {
        delete emp;
    }
    delete itDept;
}

int main() {
    // Для русского языка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    do {
        showMainMenu();
        choice = safeInputInt("", 0, 6);

        switch (choice) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 3:
                task3();
                break;
            case 4:
                task4();
                break;
            case 5:
                task5();
                break;
            case 6:
                task6();
                break;
            case 0:
                std::cout << "Выход из программы..." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }

    } while (choice != 0);

    return 0;
}
