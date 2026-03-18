#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "head.h"

// Вспомогательная функция для очистки буфера ввода
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// РЕАЛИЗАЦИЯ КЛАССА STACK

// Конструктор копирования
Stack::Stack(const Stack& other) : top(nullptr) {
    if (other.isEmpty()) return;

    // Создаем стек в обратном порядке, чтобы сохранить порядок
    Node* current = other.top;
    Stack temp;

    while (current != nullptr) {
        temp.push(current->Data);
        current = current->Next;
    }

    // Переворачиваем обратно
    while (!temp.isEmpty()) {
        this->push(temp.pop());
    }
}

// Деструктор
Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

// Добавление элемента в стек
void Stack::push(int value) {
    Node* newNode = new Node(value);
    newNode->Next = top;
    top = newNode;
}

// Извлечение элемента из стека
int Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Стек пуст");
    }

    Node* temp = top;
    int value = temp->Data;
    top = top->Next;
    delete temp;

    return value;
}

// Проверка на пустоту
bool Stack::isEmpty() const {
    return top == nullptr;
}

// Печать стека
void Stack::print() const {
    if (isEmpty()) {
        std::cout << "Стек пуст" << std::endl;
        return;
    }

    Node* current = top;
    std::cout << "Стек (голова -> хвост): ";
    while (current != nullptr) {
        std::cout << current->Data << " ";
        current = current->Next;
    }
    std::cout << std::endl;
}

// Поиск элемента по значению
bool Stack::findElement(int value) const {
    Node* current = top;
    int position = 1;

    while (current != nullptr) {
        if (current->Data == value) {
            return true;
        }
        current = current->Next;
        position++;
    }

    return false;
}

// Поиск с выводом информации
void Stack::searchAndDisplay(int value) const {
    Node* current = top;
    int position = 1;
    bool found = false;

    std::cout << "Результат поиска значения " << value << " в стеке:" << std::endl;

    while (current != nullptr) {
        if (current->Data == value) {
            std::cout << "  Найдено! Позиция: " << position
                      << " (считая от вершины), адрес: " << current << std::endl;
            found = true;
        }
        current = current->Next;
        position++;
    }

    if (!found) {
        std::cout << "  Значение " << value << " не найдено в стеке." << std::endl;
    }
}

// Заполнение из файла
void Stack::fillFromFile(const std::string& filename) {
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

    // Читаем числа и добавляем в стек
    int* values = new int[n];
    for (int i = 0; i < n; i++) {
        file >> values[i];
        if (file.fail()) {
            std::cerr << "Ошибка чтения элемента " << i+1 << " из файла!" << std::endl;
            delete[] values;
            file.close();
            return;
        }
    }

    // Добавляем в стек в обратном порядке
    for (int i = n - 1; i >= 0; i--) {
        push(values[i]);
    }

    delete[] values;
    file.close();
    std::cout << "Стек успешно заполнен из файла. Загружено " << n << " элементов." << std::endl;
}

// Заполнение случайными числами
void Stack::fillRandom(int count) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }

    for (int i = 0; i < count; i++) {
        push(rand() % 100); // Случайные числа от 0 до 99
    }

    std::cout << "Стек заполнен " << count << " случайными числами." << std::endl;
}

// Метод для Dynamic6: извлечь первые девять элементов
void Stack::popNineElements() {
    std::cout << "Извлеченные элементы: ";
    for (int i = 0; i < 9; i++) {
        if (!isEmpty()) {
            std::cout << pop() << " ";
        } else {
            std::cout << "\nОшибка: в стеке меньше 9 элементов!" << std::endl;
            return;
        }
    }
    std::cout << std::endl;

    std::cout << "Адрес новой вершины стека: " << getTop() << std::endl;
}

// Статический метод для валидации ввода
int Stack::getValidatedInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << "Ошибка: введите целое число!" << std::endl;
            clearInputBuffer();
        } else if (value < min || value > max) {
            std::cout << "Ошибка: число должно быть в диапазоне от " << min << " до " << max << "!" << std::endl;
        } else {
            clearInputBuffer();
            return value;
        }
    }
}

// РЕАЛИЗАЦИЯ КЛАССА QUEUE

// Конструктор копирования
Queue::Queue(const Queue& other) : head(nullptr), tail(nullptr) {
    Node* current = other.head;
    while (current != nullptr) {
        enqueue(current->Data);
        current = current->Next;
    }
}

// Деструктор
Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

// Добавление элемента в очередь
void Queue::enqueue(int value) {
    Node* newNode = new Node(value);

    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->Next = newNode;
        tail = newNode;
    }
}

// Извлечение элемента из очереди
int Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Очередь пуста");
    }

    Node* temp = head;
    int value = temp->Data;
    head = head->Next;

    if (head == nullptr) {
        tail = nullptr;
    }

    delete temp;
    return value;
}

// Проверка на пустоту
bool Queue::isEmpty() const {
    return head == nullptr;
}

// Печать очереди
void Queue::print() const {
    if (isEmpty()) {
        std::cout << "Очередь пуста" << std::endl;
        return;
    }

    Node* current = head;
    std::cout << "Очередь (начало -> конец): ";
    while (current != nullptr) {
        std::cout << current->Data << " ";
        current = current->Next;
    }
    std::cout << std::endl;
}

// Поиск элемента по значению
bool Queue::findElement(int value) const {
    Node* current = head;
    int position = 1;

    while (current != nullptr) {
        if (current->Data == value) {
            return true;
        }
        current = current->Next;
        position++;
    }

    return false;
}

// Поиск с выводом информации
void Queue::searchAndDisplay(int value) const {
    Node* current = head;
    int position = 1;
    bool found = false;

    std::cout << "Результат поиска значения " << value << " в очереди:" << std::endl;

    while (current != nullptr) {
        if (current->Data == value) {
            std::cout << "  Найдено! Позиция: " << position
                      << " (от начала), адрес: " << current << std::endl;
            found = true;
        }
        current = current->Next;
        position++;
    }

    if (!found) {
        std::cout << "  Значение " << value << " не найдено в очереди." << std::endl;
    }
}

// Заполнение из файла
void Queue::fillFromFile(const std::string& filename) {
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

    for (int i = 0; i < n; i++) {
        int value;
        file >> value;
        if (file.fail()) {
            std::cerr << "Ошибка чтения элемента " << i+1 << " из файла!" << std::endl;
            file.close();
            return;
        }
        enqueue(value);
    }

    file.close();
    std::cout << "Очередь успешно заполнена из файла. Загружено " << n << " элементов." << std::endl;
}

// Заполнение случайными числами
void Queue::fillRandom(int count) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }

    for (int i = 0; i < count; i++) {
        enqueue(rand() % 100);
    }

    std::cout << "Очередь заполнена " << count << " случайными числами." << std::endl;
}

// Метод для Dynamic21: переместить все элементы первой очереди в конец второй
void Queue::moveAllTo(Queue& dest) {
    if (isEmpty()) return;

    // Соединяем конец второй очереди с началом первой
    if (dest.isEmpty()) {
        dest.head = this->head;
        dest.tail = this->tail;
    } else {
        dest.tail->Next = this->head;
        dest.tail = this->tail;
    }

    // Очищаем текущую очередь (без удаления памяти)
    this->head = nullptr;
    this->tail = nullptr;

    std::cout << "Элементы успешно перемещены." << std::endl;
}

// Статический метод для валидации ввода
int Queue::getValidatedInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << "Ошибка: введите целое число!" << std::endl;
            clearInputBuffer();
        } else if (value < min || value > max) {
            std::cout << "Ошибка: число должно быть в диапазоне от " << min << " до " << max << "!" << std::endl;
        } else {
            clearInputBuffer();
            return value;
        }
    }
}

// РЕАЛИЗАЦИЯ КЛАССА LINKEDLIST

// Конструктор копирования
LinkedList::LinkedList(const LinkedList& other) : head(nullptr) {
    Node* current = other.head;
    Node* last = nullptr;

    while (current != nullptr) {
        Node* newNode = new Node(current->Data);

        if (last == nullptr) {
            head = newNode;
        } else {
            last->Next = newNode;
        }

        last = newNode;
        current = current->Next;
    }
}

// Деструктор
LinkedList::~LinkedList() {
    clear();
}

// Очистка списка
void LinkedList::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->Next;
        delete temp;
    }
}

// Добавление в конец списка
void LinkedList::append(int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->Next != nullptr) {
        current = current->Next;
    }

    current->Next = newNode;
}

// Вставка после указанного узла
void LinkedList::insertAfter(Node* prev, int value) {
    if (prev == nullptr) return;

    Node* newNode = new Node(value);
    newNode->Next = prev->Next;
    prev->Next = newNode;
}

// Вставка перед указанным узлом
void LinkedList::insertBefore(Node* next, int value) {
    if (next == nullptr) return;

    Node* newNode = new Node(value);

    // Если вставляем перед головой
    if (next == head) {
        newNode->Next = head;
        head = newNode;
        return;
    }

    // Ищем предыдущий узел
    Node* prev = head;
    while (prev != nullptr && prev->Next != next) {
        prev = prev->Next;
    }

    if (prev != nullptr) {
        newNode->Next = next;
        prev->Next = newNode;
    }
}

// Поиск узла по позиции (1-based)
Node* LinkedList::findNodeByPosition(int position) {
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
Node* LinkedList::findNodeByValue(int value) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->Data == value) {
            return current;
        }
        current = current->Next;
    }

    return nullptr;
}

// Получение последнего узла
Node* LinkedList::getLastNode() {
    if (head == nullptr) return nullptr;

    Node* current = head;
    while (current->Next != nullptr) {
        current = current->Next;
    }

    return current;
}

// Метод для ListWork4: получить пятый элемент
Node* LinkedList::getElementAtPosition(int pos) {
    return findNodeByPosition(pos);
}

// Метод для ListWork25: вставка m элемента перед каждым вторым элементом
LinkedList LinkedList::insertBeforeEverySecond(int m) const {
    LinkedList result;

    // Если исходный список пуст, возвращаем пустой список
    if (this->head == nullptr) {
        return result;
    }

    // Копируем все элементы из текущего списка в результат
    Node* current = this->head;
    Node* lastResult = nullptr;
    int count = 0;

    while (current != nullptr) {
        count++;

        // Вставляем M перед каждым вторым элементом
        if (count % 2 == 0) {
            // Сначала вставляем M
            Node* newNodeM = new Node(m);
            if (result.head == nullptr) {
                result.head = newNodeM;
                lastResult = newNodeM;
            } else {
                lastResult->Next = newNodeM;
                lastResult = newNodeM;
            }
        }

        // Затем вставляем текущий элемент
        Node* newNode = new Node(current->Data);
        if (result.head == nullptr) {
            result.head = newNode;
            lastResult = newNode;
        } else {
            lastResult->Next = newNode;
            lastResult = newNode;
        }

        current = current->Next;
    }

    return result;
}

// Метод для ListWork62: вставка с сохранением упорядоченности по убыванию
void LinkedList::insertSortedDescending(int value) {
    Node* newNode = new Node(value);

    // Если список пуст или новый элемент больше первого
    if (head == nullptr || value > head->Data) {
        newNode->Next = head;
        head = newNode;
        return;
    }

    // Ищем место для вставки
    Node* current = head;
    while (current->Next != nullptr && current->Next->Data > value) {
        current = current->Next;
    }

    // Вставляем после current
    newNode->Next = current->Next;
    current->Next = newNode;
}

// Поиск элемента по значению (возвращает true/false)
bool LinkedList::findElement(int value) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->Data == value) {
            return true;
        }
        current = current->Next;
    }

    return false;
}

// Поиск с выводом информации
void LinkedList::searchAndDisplay(int value) const {
    Node* current = head;
    int position = 1;
    bool found = false;

    std::cout << "Результат поиска значения " << value << " в списке:" << std::endl;

    while (current != nullptr) {
        if (current->Data == value) {
            std::cout << "  Найдено! Позиция: " << position
                      << ", адрес: " << current << std::endl;
            found = true;
        }
        current = current->Next;
        position++;
    }

    if (!found) {
        std::cout << "  Значение " << value << " не найдено в списке." << std::endl;
    }
}

// Печать списка
void LinkedList::print() const {
    if (head == nullptr) {
        std::cout << "Список пуст" << std::endl;
        return;
    }

    Node* current = head;
    std::cout << "Список: ";
    while (current != nullptr) {
        std::cout << current->Data << " ";
        current = current->Next;
    }
    std::cout << std::endl;
}

// Заполнение из файла
void LinkedList::fillFromFile(const std::string& filename) {
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

    clear(); // Очищаем текущий список

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
}

// Заполнение случайными числами
void LinkedList::fillRandom(int count) {
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
}

// Заполнение упорядоченного по убыванию списка из файла
void LinkedList::fillSortedDescendingFromFile(const std::string& filename) {
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
        insertSortedDescending(value);
    }

    file.close();
    std::cout << "Упорядоченный список успешно заполнен из файла. Загружено " << n << " элементов." << std::endl;
}

// Статический метод для валидации ввода
int LinkedList::getValidatedInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << "Ошибка: введите целое число!" << std::endl;
            clearInputBuffer();
        } else if (value < min || value > max) {
            std::cout << "Ошибка: число должно быть в диапазоне от " << min << " до " << max << "!" << std::endl;
        } else {
            clearInputBuffer();
            return value;
        }
    }
}

// ============= ДЕМОНСТРАЦИОННЫЕ ФУНКЦИИ =============

void demonstrateDynamic6() {
    std::cout << "\n========== ЗАДАНИЕ Dynamic6 ==========" << std::endl;
    std::cout << "Стек (извлечение 9 элементов)" << std::endl;

    Stack stack;

    std::cout << "\nВыберите способ заполнения стека:" << std::endl;
    std::cout << "1 - Ввод с клавиатуры" << std::endl;
    std::cout << "2 - Заполнение из файла (input_dynamic6.txt)" << std::endl;
    std::cout << "3 - Случайные числа" << std::endl;

    int choice = Stack::getValidatedInt("Ваш выбор (1-3): ", 1, 3);

    if (choice == 1) {
        int n = Stack::getValidatedInt("Введите количество элементов (не менее 10): ", 10, 1000);

        std::cout << "Введите " << n << " чисел: ";
        int* values = new int[n];
        for (int i = 0; i < n; i++) {
            values[i] = Stack::getValidatedInt("", std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        }

        // Добавляем в стек в обратном порядке (последнее число - вершина)
        for (int i = n - 1; i >= 0; i--) {
            stack.push(values[i]);
        }

        delete[] values;
    }
    else if (choice == 2) {
        stack.fillFromFile("input_dynamic6.txt");
    }
    else if (choice == 3) {
        int n = Stack::getValidatedInt("Введите количество случайных элементов: ", 1, 1000);
        stack.fillRandom(n);
    }

    std::cout << "\nИсходный стек:" << std::endl;
    stack.print();
    std::cout << "Адрес вершины стека: " << stack.getTop() << std::endl;

    // Демонстрация поиска
    std::cout << "\n--- Поиск элемента ---" << std::endl;
    int searchValue = Stack::getValidatedInt("Введите значение для поиска в стеке: ");
    stack.searchAndDisplay(searchValue);

    // Проверка на минимальное количество элементов
    if (stack.isEmpty()) {
        std::cout << "Стек пуст! Операция невозможна." << std::endl;
        return;
    }

    // Извлекаем 9 элементов
    std::cout << "\n--- Извлечение 9 элементов ---" << std::endl;
    stack.popNineElements();

    std::cout << "\nСтек после извлечения:" << std::endl;
    stack.print();

    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.get();
}

void demonstrateDynamic21() {
    std::cout << "\n========== ЗАДАНИЕ Dynamic21 ==========" << std::endl;
    std::cout << "Очередь (перемещение элементов из первой очереди во вторую)" << std::endl;

    Queue queue1, queue2;

    std::cout << "\nСоздание первой очереди:" << std::endl;
    std::cout << "Выберите способ заполнения:" << std::endl;
    std::cout << "1 - Ввод с клавиатуры" << std::endl;
    std::cout << "2 - Заполнение из файла (input_queue1.txt)" << std::endl;
    std::cout << "3 - Случайные числа" << std::endl;

    int choice = Queue::getValidatedInt("Ваш выбор (1-3): ", 1, 3);

    if (choice == 1) {
        int n = Queue::getValidatedInt("Введите количество элементов: ", 1, 1000);

        std::cout << "Введите " << n << " чисел: ";
        for (int i = 0; i < n; i++) {
            int val = Queue::getValidatedInt("");
            queue1.enqueue(val);
        }
    }
    else if (choice == 2) {
        queue1.fillFromFile("input_queue1.txt");
    }
    else if (choice == 3) {
        int n = Queue::getValidatedInt("Введите количество случайных элементов: ", 1, 1000);
        queue1.fillRandom(n);
    }

    std::cout << "\nСоздание второй очереди:" << std::endl;
    std::cout << "1 - Ввод с клавиатуры" << std::endl;
    std::cout << "2 - Заполнение из файла (input_queue2.txt)" << std::endl;
    std::cout << "3 - Случайные числа" << std::endl;

    choice = Queue::getValidatedInt("Ваш выбор (1-3): ", 1, 3);

    if (choice == 1) {
        int n = Queue::getValidatedInt("Введите количество элементов: ", 0, 1000);

        if (n > 0) {
            std::cout << "Введите " << n << " чисел: ";
            for (int i = 0; i < n; i++) {
                int val = Queue::getValidatedInt("");
                queue2.enqueue(val);
            }
        }
    }
    else if (choice == 2) {
        queue2.fillFromFile("input_queue2.txt");
    }
    else if (choice == 3) {
        int n = Queue::getValidatedInt("Введите количество случайных элементов: ", 0, 1000);
        if (n > 0) {
            queue2.fillRandom(n);
        }
    }

    std::cout << "\nПервая очередь:" << std::endl;
    queue1.print();
    std::cout << "Адреса: начало = " << queue1.getHead() << ", конец = " << queue1.getTail() << std::endl;

    std::cout << "\nВторая очередь:" << std::endl;
    queue2.print();
    std::cout << "Адреса: начало = " << queue2.getHead() << ", конец = " << queue2.getTail() << std::endl;

    // Демонстрация поиска
    std::cout << "\n--- Поиск элемента в первой очереди ---" << std::endl;
    int searchValue = Queue::getValidatedInt("Введите значение для поиска: ");
    queue1.searchAndDisplay(searchValue);

    // Перемещаем все элементы из первой очереди во вторую
    std::cout << "\n--- Перемещение элементов ---" << std::endl;
    queue1.moveAllTo(queue2);

    std::cout << "\nПосле перемещения:" << std::endl;
    std::cout << "Первая очередь:" << std::endl;
    queue1.print();
    std::cout << "Адреса: начало = " << queue1.getHead() << ", конец = " << queue1.getTail() << std::endl;

    std::cout << "\nВторая очередь:" << std::endl;
    queue2.print();
    std::cout << "Адреса: начало = " << queue2.getHead() << ", конец = " << queue2.getTail() << std::endl;

    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.get();
}

void demonstrateListWork4() {
    std::cout << "\n========== ЗАДАНИЕ ListWork4 ==========" << std::endl;
    std::cout << "Односвязный список (поиск пятого элемента)" << std::endl;

    LinkedList list;

    std::cout << "\nВыберите способ заполнения списка:" << std::endl;
    std::cout << "1 - Ввод с клавиатуры" << std::endl;
    std::cout << "2 - Заполнение из файла (input_list.txt)" << std::endl;
    std::cout << "3 - Случайные числа" << std::endl;

    int choice = LinkedList::getValidatedInt("Ваш выбор (1-3): ", 1, 3);

    if (choice == 1) {
        int n = LinkedList::getValidatedInt("Введите количество элементов (не менее 5): ", 5, 1000);

        std::cout << "Введите " << n << " чисел: ";
        for (int i = 0; i < n; i++) {
            int val = LinkedList::getValidatedInt("");
            list.append(val);
        }
    }
    else if (choice == 2) {
        list.fillFromFile("input_list.txt");
    }
    else if (choice == 3) {
        int n = LinkedList::getValidatedInt("Введите количество случайных элементов: ", 5, 1000);
        list.fillRandom(n);
    }

    std::cout << "\nИсходный список:" << std::endl;
    list.print();
    std::cout << "Адрес головы списка P1: " << list.getHead() << std::endl;

    // Демонстрация поиска
    std::cout << "\n--- Поиск элемента по значению ---" << std::endl;
    int searchValue = LinkedList::getValidatedInt("Введите значение для поиска в списке: ");
    list.searchAndDisplay(searchValue);

    Node* p5 = list.getElementAtPosition(5);

    if (p5 != nullptr) {
        std::cout << "\n--- Результат ---" << std::endl;
        std::cout << "Пятый элемент: " << p5->Data << std::endl;
        std::cout << "Адрес пятого элемента P5: " << p5 << std::endl;
    } else {
        std::cout << "\nОшибка: в списке меньше 5 элементов!" << std::endl;
    }

    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.get();
}

// Вставка значения M перед каждым вторым элементом (исправлено)
void demonstrateListWork25() {
    std::cout << "\n========== ЗАДАНИЕ ListWork25 ==========" << std::endl;
    std::cout << "Односвязный список (вставка элемента M перед каждым вторым элементом)" << std::endl;

    LinkedList list;

    std::cout << "\nВыберите способ заполнения списка:" << std::endl;
    std::cout << "1 - Ввод с клавиатуры" << std::endl;
    std::cout << "2 - Заполнение из файла (input_list25.txt)" << std::endl;
    std::cout << "3 - Случайные числа" << std::endl;

    int choice = LinkedList::getValidatedInt("Ваш выбор (1-3): ", 1, 3);

    if (choice == 1) {
        int n = LinkedList::getValidatedInt("Введите количество элементов: ", 1, 1000);

        std::cout << "Введите " << n << " чисел: ";
        for (int i = 0; i < n; i++) {
            int val = LinkedList::getValidatedInt("");
            list.append(val);
        }
    }
    else if (choice == 2) {
        list.fillFromFile("input_list25.txt");
    }
    else if (choice == 3) {
        int n = LinkedList::getValidatedInt("Введите количество случайных элементов: ", 1, 1000);
        list.fillRandom(n);
    }

    int m = LinkedList::getValidatedInt("\nВведите значение M для вставки: ");

    std::cout << "\nИсходный список:" << std::endl;
    list.print();
    std::cout << "Адрес головы списка P1: " << list.getHead() << std::endl;

    // Демонстрация поиска перед операцией
    std::cout << "\n--- Поиск элемента в исходном списке ---" << std::endl;
    int searchValue = LinkedList::getValidatedInt("Введите значение для поиска: ");
    list.searchAndDisplay(searchValue);

    // Выполняем вставку перед каждым вторым элементом
    LinkedList result = list.insertBeforeEverySecond(m);

    std::cout << "\nРезультирующий список (после вставки M перед каждым вторым элементом):" << std::endl;
    result.print();

    Node* last = result.getLastNode();
    if (last != nullptr) {
        std::cout << "Адрес последнего элемента P2: " << last << std::endl;
    } else {
        std::cout << "Результирующий список пуст." << std::endl;
    }

    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.get();
}

// Создание упорядоченного по убыванию списка
void demonstrateListWork62() {
    std::cout << "\n========== ЗАДАНИЕ ListWork62 ==========" << std::endl;
    std::cout << "Упорядоченный по убыванию список" << std::endl;

    LinkedList list;

    std::cout << "\nВыберите способ заполнения:" << std::endl;
    std::cout << "1 - Ввод с клавиатуры (с сохранением упорядоченности)" << std::endl;
    std::cout << "2 - Заполнение из файла (input_list62.txt)" << std::endl;
    std::cout << "3 - Случайные числа" << std::endl;

    int choice = LinkedList::getValidatedInt("Ваш выбор (1-3): ", 1, 3);

    if (choice == 1) {
        int n = LinkedList::getValidatedInt("Введите количество элементов: ", 1, 1000);

        std::cout << "Введите " << n << " чисел (будут вставлены с сохранением упорядоченности по убыванию):" << std::endl;
        for (int i = 0; i < n; i++) {
            int val = LinkedList::getValidatedInt("");
            list.insertSortedDescending(val);
            std::cout << "  После вставки " << val << ": ";
            list.print();
        }
    }
    else if (choice == 2) {
        list.fillSortedDescendingFromFile("input_list62.txt");
    }
    else if (choice == 3) {
        int n = LinkedList::getValidatedInt("Введите количество случайных элементов: ", 1, 1000);

        static bool seeded = false;
        if (!seeded) {
            srand(time(nullptr));
            seeded = true;
        }

        list.clear();
        std::cout << "Генерация " << n << " случайных чисел и вставка с упорядочиванием:" << std::endl;

        for (int i = 0; i < n; i++) {
            int val = rand() % 100;
            list.insertSortedDescending(val);
            std::cout << "  Вставлено " << val << ": ";
            list.print();
        }
    }

    std::cout << "\nИтоговый упорядоченный по убыванию список:" << std::endl;
    list.print();
    std::cout << "Адрес головы списка: " << list.getHead() << std::endl;

    // Проверка упорядоченности
    Node* current = list.getHead();
    bool isSorted = true;
    int prevValue = (current != nullptr) ? current->Data : 0;
    current = (current != nullptr) ? current->Next : nullptr;

    while (current != nullptr) {
        if (prevValue < current->Data) {
            isSorted = false;
            break;
        }
        prevValue = current->Data;
        current = current->Next;
    }

    std::cout << "Список " << (isSorted ? "упорядочен" : "не упорядочен") << " по убыванию." << std::endl;

    // Демонстрация поиска
    std::cout << "\n--- Поиск элемента в упорядоченном списке ---" << std::endl;
    int searchValue = LinkedList::getValidatedInt("Введите значение для поиска: ");
    list.searchAndDisplay(searchValue);

    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.get();
}
