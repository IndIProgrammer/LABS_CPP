#include "head.h"

// РЕАЛИЗАЦИЯ ОСНОВНЫХ МЕТОДОВ КЛАССА LINKEDLISTTWO

// Конструктор копирования
LinkedListTwo::LinkedListTwo(const LinkedListTwo& other) : head(nullptr), tail(nullptr) {
    Node* current = other.head;
    while (current != nullptr) {
        append(current->Data);
        current = current->Next;
    }
}

// Деструктор
LinkedListTwo::~LinkedListTwo() {
    clear();
}

// Очистка списка
void LinkedListTwo::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->Next;
        delete temp;
    }
    tail = nullptr;
}

// Получение размера списка
int LinkedListTwo::getSize() const {
    int size = 0;
    Node* current = head;
    while (current != nullptr) {
        size++;
        current = current->Next;
    }
    return size;
}

// Добавление в конец списка
void LinkedListTwo::append(int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = tail = newNode;
        return;
    }

    tail->Next = newNode;
    newNode->Prev = tail;
    tail = newNode;
}

// Добавление в начало списка
void LinkedListTwo::prepend(int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = tail = newNode;
        return;
    }

    head->Prev = newNode;
    newNode->Next = head;
    head = newNode;
}

// Вставка после указанного узла
void LinkedListTwo::insertAfter(Node* node, int value) {
    if (node == nullptr) return;

    Node* newNode = new Node(value);
    newNode->Prev = node;
    newNode->Next = node->Next;

    if (node->Next != nullptr) {
        node->Next->Prev = newNode;
    } else {
        tail = newNode;
    }

    node->Next = newNode;
}

// Вставка перед указанным узлом
void LinkedListTwo::insertBefore(Node* node, int value) {
    if (node == nullptr) return;

    Node* newNode = new Node(value);
    newNode->Next = node;
    newNode->Prev = node->Prev;

    if (node->Prev != nullptr) {
        node->Prev->Next = newNode;
    } else {
        head = newNode;
    }

    node->Prev = newNode;
}

// Удаление узла
bool LinkedListTwo::remove(Node* node) {
    if (node == nullptr) return false;

    if (node->Prev != nullptr) {
        node->Prev->Next = node->Next;
    } else {
        head = node->Next;
    }

    if (node->Next != nullptr) {
        node->Next->Prev = node->Prev;
    } else {
        tail = node->Prev;
    }

    delete node;
    return true;
}

// Поиск узла по позиции (1-based)
Node* LinkedListTwo::findNodeByPosition(int position) {
    if (position <= 0 || head == nullptr) return nullptr;

    Node* current = head;
    int count = 1;

    while (current != nullptr && count < position) {
        current = current->Next;
        count++;
    }

    return current;
}

// Поиск узла по значению
Node* LinkedListTwo::findNodeByValue(int value) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->Data == value) {
            return current;
        }
        current = current->Next;
    }

    return nullptr;
}

// Поиск элемента по значению
bool LinkedListTwo::findElement(int value) const {
    return findNodeByValue(value) != nullptr;
}

// Печать списка
void LinkedListTwo::print() const {
    if (head == nullptr) {
        std::cout << "Список пуст" << std::endl;
        return;
    }

    Node* current = head;
    std::cout << "Список (прямой порядок): ";
    while (current != nullptr) {
        std::cout << current->Data << " ";
        current = current->Next;
    }
    std::cout << std::endl;
}

// Печать списка в обратном порядке
void LinkedListTwo::printReverse() const {
    if (tail == nullptr) {
        std::cout << "Список пуст" << std::endl;
        return;
    }

    Node* current = tail;
    std::cout << "Список (обратный порядок): ";
    while (current != nullptr) {
        std::cout << current->Data << " ";
        current = current->Prev;
    }
    std::cout << std::endl;
}

// Заполнение из файла
void LinkedListTwo::fillFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }

    int n;
    file >> n;

    if (file.fail() || n <= 0) {
        std::cerr << "Ошибка чтения количества элементов из файла!" << std::endl;
        file.close();
        return;
    }

    clear();

    for (int i = 0; i < n; i++) {
        int value;
        file >> value;
        if (file.fail()) {
            std::cerr << "Ошибка чтения элемента " << i+1 << " из файла!" << std::endl;
            file.close();
            return;
        }
        append(value);
    }

    file.close();
    std::cout << "Список успешно заполнен из файла. Загружено " << n << " элементов." << std::endl;
    print();
}

// Заполнение случайными числами
void LinkedListTwo::fillRandom(int count) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }

    clear();

    for (int i = 0; i < count; i++) {
        append(rand() % 100);
    }

    std::cout << "Список заполнен " << count << " случайными числами." << std::endl;
    print();
}

// Статический метод для валидации ввода
int LinkedListTwo::getValidatedInt(const std::string& prompt, int min, int max) {
    int value;
    std::string input;
    char leftover;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        // Проверка на пустой ввод
        if (input.empty()) {
            std::cout << "Ошибка: ввод не может быть пустым!" << std::endl;
            continue;
        }

        // Более строгая проверка на допустимые символы
        bool isValidFormat = true;
        bool hasDigit = false;

        for (size_t i = 0; i < input.length(); ++i) {
            char c = input[i];

            if (isdigit(c)) {
                hasDigit = true;
            } else if (c == '-') {
                // Минус может быть только первым символом
                if (i != 0) {
                    isValidFormat = false;
                    break;
                }
            } else {
                isValidFormat = false;
                break;
            }
        }

        if (!isValidFormat || !hasDigit) {
            std::cout << "Ошибка: введите целое число!" << std::endl;
            continue;
        }

        // Используем stringstream для безопасного преобразования
        std::stringstream ss(input);

        // Пытаемся извлечь число
        if (!(ss >> value)) {
            std::cout << "Ошибка: введите целое число!" << std::endl;
            continue;
        }

        // Проверяем, не осталось ли лишних символов
        if (ss >> leftover) {
            std::cout << "Ошибка: введите только число без лишних символов!" << std::endl;
            continue;
        }

        // Проверка диапазона
        if (value < min || value > max) {
            std::cout << "Ошибка: число должно быть в диапазоне от " << min << " до " << max << "!" << std::endl;
        } else {
            return value;
        }
    }
}

// Задача 4: Проверка симметричности строки с помощью циклического двунаправленного списка
bool LinkedListTwo::isStringSymmetric(const std::string& str) {
    if (str.empty()) return true;

    // Создаем список и заполняем его символами строки
    LinkedListTwo charList;
    for (char c : str) {
        charList.append(static_cast<int>(c));
    }

    if (charList.getHead() == nullptr || charList.getTail() == nullptr) {
        return false;
    }

    // Получаем указатели на начало и конец
    Node* left = charList.getHead();
    Node* right = charList.getTail();

    int length = str.length();
    for (int i = 0; i < length / 2; i++) {
        if (left->Data != right->Data) {
            return false;
        }
        left = left->Next;
        right = right->Prev;
    }

    return true;
}

// ListWork41: Вывод элементов между минимальным и максимальным
void LinkedListTwo::printBetweenMinAndMax() {
    if (head == nullptr) {
        std::cout << "Список пуст" << std::endl;
        return;
    }

    Node* current = head;
    Node* minNode = head;
    Node* maxNode = head;

    while (current != nullptr) {
        if (current->Data < minNode->Data) {
            minNode = current;
        }
        if (current->Data > maxNode->Data) {
            maxNode = current;
        }
        current = current->Next;
    }

    if (minNode == maxNode) {
        std::cout << "Минимальный и максимальный элементы совпадают: " << minNode->Data << std::endl;
        return;
    }

    std::cout << "Элементы между " << minNode->Data << " и " << maxNode->Data << ": ";

    // Определяем, какой элемент встречается раньше
    current = head;
    bool minFirst = true;
    while (current != nullptr) {
        if (current == minNode) {
            minFirst = true;
            break;
        }
        if (current == maxNode) {
            minFirst = false;
            break;
        }
        current = current->Next;
    }

    if (minFirst) {
        // Идем от min к max
        current = minNode->Next;
        while (current != nullptr && current != maxNode) {
            std::cout << current->Data << " ";
            current = current->Next;
        }
    } else {
        // Идем от max к min
        current = maxNode->Next;
        while (current != nullptr && current != minNode) {
            std::cout << current->Data << " ";
            current = current->Next;
        }
    }
    std::cout << std::endl;
}

// ListWork63: Вывод в обратном порядке в файл с удалением
void LinkedListTwo::saveReverseToFileAndClear(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось создать файл: " << filename << std::endl;
        return;
    }

    std::cout << "Вывод в обратном порядке с удалением:" << std::endl;

    while (tail != nullptr) {
        Node* current = tail;
        std::cout << current->Data << " ";
        file << current->Data;

        tail = tail->Prev;

        if (tail != nullptr) {
            tail->Next = nullptr;
            file << " ";
        } else {
            head = nullptr;
        }

        delete current;
    }

    std::cout << std::endl << "Данные сохранены в файл " << filename << std::endl;
    file.close();
}

// Задача 46: Преобразование в циклический список с барьерным элементом
Node* LinkedListTwo::transformToCircularWithBarrier() {
    // Создаем барьерный элемент со значением 0
    Node* barrier = new Node(0);

    if (head == nullptr) {
        // Если список пуст, барьерный элемент указывает сам на себя
        barrier->Next = barrier;
        barrier->Prev = barrier;
    } else {
        // Связываем барьерный элемент с первым и последним элементами списка
        barrier->Next = head;
        barrier->Prev = tail;

        // Связываем первый и последний элементы с барьерным
        head->Prev = barrier;
        tail->Next = barrier;
    }

    std::cout << "Список преобразован в циклический с барьерным элементом (значение 0)" << std::endl;
    std::cout << "Указатель на барьерный элемент: " << barrier << std::endl;
    std::cout << "Список: ";
    for (Node* current = barrier; ; ) {
        std::cout << current->Data << " ";
        current = current->Next;
        if (current == barrier)
            break;
    }
    std::cout << std::endl;

    return barrier;
}

// Задача 69: Вывод в файл с шагом k и удалением
void LinkedListTwo::saveWithStepToFileAndRemove(const std::string& filename, int k) {
    if (head == nullptr) {
        std::cerr << "Список пуст!" << std::endl;
        return;
    }

    // Получаем размер до преобразования
    int totalElements = getSize();

    // Вектор указателей на узлы
    std::vector<Node*> nodes;
    nodes.reserve(totalElements);

    // Заполняем вектор указателями
    Node* current = head;
    for (int i = 0; i < totalElements; i++) {
        nodes.push_back(current);
        current = current->Next;
    }

    // Преобразуем в циклический список с барьером
    Node* barrier = transformToCircularWithBarrier();

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось создать файл: " << filename << std::endl;
        delete barrier;
        return;
    }

    std::cout << "Вывод элементов с шагом " << k << " и удалением:" << std::endl;

    // Вектор для отслеживания удаленных элементов
    std::vector<bool> removed(totalElements, false);

    int currentIndex = 0;
    int elementsProcessed = 0;

    while (elementsProcessed < totalElements) {
        // Пропускаем уже удаленные элементы
        while (removed[currentIndex]) {
            currentIndex = (currentIndex + 1) % totalElements;
        }

        Node* toDelete = nodes[currentIndex];

        // Выводим текущий элемент
        std::cout << toDelete->Data << " ";
        file << toDelete->Data;

        // Помечаем как удаленный
        removed[currentIndex] = true;
        elementsProcessed++;

        // Если это не последний элемент, добавляем пробел
        if (elementsProcessed < totalElements) {
            file << " ";
        }

        // Перемещаемся на k шагов вперед (только по неудаленным элементам)
        if (elementsProcessed < totalElements) {
            int steps = k;
            while (steps > 0) {
                currentIndex = (currentIndex + 1) % totalElements;
                if (!removed[currentIndex]) {
                    steps--;
                }
            }
        }
    }

    std::cout << std::endl << "Данные сохранены в файл " << filename << std::endl;
    file.close();

    // Теперь физически удаляем все узлы
    for (Node* node : nodes) {
        delete node;
    }

    // Удаляем барьерный элемент
    delete barrier;

    // Обнуляем указатели списка
    head = nullptr;
    tail = nullptr;
}

// Заполнение с клавиатуры
void LinkedListTwo::fillFromKeyboard() {
    clear(); // Очищаем текущий список

    std::cout << "Введите целые числа (для окончания ввода введите 0):" << std::endl;

    int value;
    int count = 0;

    while (true) {
        std::cout << "Число " << (count + 1) << ": ";
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::string temp;
            std::cin >> temp;

            if (temp == "q" || temp == "stop" || temp == "выход") {
                break;
            }

            std::cout << "Ошибка: введите целое число" << std::endl;
            continue;
        }

        append(value);
        count++;
    }

    if (count > 0) {
        std::cout << "Список успешно заполнен с клавиатуры." << std::endl;
    } else {
        std::cout << "Вы не ввели ни одного числа. Список пуст." << std::endl;
    }
    print();
}
