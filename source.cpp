#include "head.h"

// Реализация класса Node
Node::Node(int val) : data(val), left(nullptr), right(nullptr) {}

// Реализация класса DoublyLinkedList
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
DoublyLinkedList::~DoublyLinkedList() { clear(); }

void DoublyLinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->right;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void DoublyLinkedList::pushBack(int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->right = newNode;
        newNode->left = tail;
        tail = newNode;
    }
    size++;
}

int DoublyLinkedList::getSize() const { return size; }
Node* DoublyLinkedList::getHead() const { return head; }
Node* DoublyLinkedList::getTail() const { return tail; }

void DoublyLinkedList::printList() const {
    std::cout << "Текущий список: ";
    Node* current = head;
    if (current == nullptr) {
        std::cout << "пуст" << std::endl;
        return;
    }
    while (current != nullptr) {
        std::cout << current->data;
        if (current->right != nullptr) std::cout << " <-> ";
        current = current->right;
    }
    std::cout << std::endl;
}

// Реализация класса BinaryTree
BinaryTree::BinaryTree() : root(nullptr) {}
BinaryTree::~BinaryTree() { clear(); }

// Безопасная очистка (защита от Stack Overflow при глубоких деревьях)
void BinaryTree::clearTree(Node* node) {
    if (node == nullptr) return;
    std::stack<Node*> nodes;
    nodes.push(node);
    while (!nodes.empty()) {
        Node* curr = nodes.top();
        nodes.pop();
        if (curr->left != nullptr) nodes.push(curr->left);
        if (curr->right != nullptr) nodes.push(curr->right);
        delete curr;
    }
}

void BinaryTree::clear() {
    clearTree(root);
    root = nullptr;
}

void BinaryTree::setRoot(Node* root) { this->root = root; }
Node* BinaryTree::getRoot() const { return root; }

// Классическая вставка BST (Задание 2)
void BinaryTree::insertBST(Node*& node, int value) {
    if (node == nullptr) {
        node = new Node(value);
        return;
    }
    if (value < node->data) {
        insertBST(node->left, value);
    } else {
        insertBST(node->right, value);
    }
}

// Построение честного BST дерева из элементов списка (без повреждения списка)
void BinaryTree::convertFromListToBST(DoublyLinkedList& originalList) {
    clear();
    Node* current = originalList.getHead();
    while (current != nullptr) {
        insertBST(root, current->data);
        current = current->right; // Движение по списку
    }
}

// Случайная несбалансированная вставка (Задания 6 и 9)
void BinaryTree::insertRandomUnbalanced(Node*& node, int value) {
    if (node == nullptr) {
        node = new Node(value);
        return;
    }
    if (rand() % 100 < 75) {
        insertRandomUnbalanced(node->right, value);
    } else {
        insertRandomUnbalanced(node->left, value);
    }
}

void BinaryTree::insertSingleUnbalanced(int value) {
    insertRandomUnbalanced(root, value);
}

void BinaryTree::generateRandomUnbalanced(int count) {
    clear();
    for (int i = 0; i < count; i++) {
        insertRandomUnbalanced(root, rand() % 201 - 100);
    }
}

bool BinaryTree::generateFromFileUnbalanced(const std::string& filename) {
    if (!Validator::fileExists(filename)) return false;
    clear();
    std::ifstream file(filename);
    int value;
    while (file >> value) {
        insertRandomUnbalanced(root, value);
    }
    file.close();
    return true;
}

// Вывод и высота
void BinaryTree::printTreeSideways(Node* node, int level) const {
    if (node == nullptr) return;
    printTreeSideways(node->right, level + 1);
    for (int i = 0; i < level * 4; i++) std::cout << " ";
    std::cout << node->data << std::endl;
    printTreeSideways(node->left, level + 1);
}

void BinaryTree::printTree() const {
    if (root == nullptr) {
        std::cout << "Дерево пустое" << std::endl;
        return;
    }
    std::cout << "Бинарное дерево (боковое представление):" << std::endl;
    printTreeSideways(root, 0);
}

int BinaryTree::calculateHeight(Node* node) const {
    if (node == nullptr) return 0;
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int BinaryTree::getHeight() const { return calculateHeight(root); }

// Реализация класса TreeIterator
TreeIterator::TreeIterator(Node* root) : root(root) { reset(); }
bool TreeIterator::hasNext() { return !nodeStack.empty(); }

int TreeIterator::next() {
    if (nodeStack.empty()) return -1;
    Node* node = nodeStack.top();
    nodeStack.pop();
    int value = node->data;
    if (node->left != nullptr) nodeStack.push(node->left);
    if (node->right != nullptr) nodeStack.push(node->right);
    return value;
}

void TreeIterator::reset() {
    while (!nodeStack.empty()) nodeStack.pop();
    if (root != nullptr) nodeStack.push(root);
}

// Реализация класса CameraPlacer
CameraPlacer::CameraPlacer() : cameras(0) {}

int CameraPlacer::minCameraCover(Node* node) {
    if (node == nullptr) return 2;
    int left = minCameraCover(node->left);
    int right = minCameraCover(node->right);
    if (left == 0 || right == 0) {
        cameras++;
        return 1;
    }
    if (left == 1 || right == 1) return 2;
    return 0;
}

int CameraPlacer::getMinCameras(Node* root) {
    cameras = 0;
    int state = minCameraCover(root);
    if (state == 0) cameras++;
    return cameras;
}

// Реализация класса Validator
void Validator::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Validator::getIntInput(int min, int max, const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= min && value <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else {
                std::cout << "Ошибка! Диапазон от " << min << " до " << max << std::endl;
                clearInputBuffer();
            }
        } else {
            std::cout << "Ошибка! Введите целое число" << std::endl;
            clearInputBuffer();
        }
    }
}

int Validator::getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cout << "Ошибка! Введите целое число" << std::endl;
            clearInputBuffer();
        }
    }
}

double Validator::getDoubleInput(double min, double max, const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= min && value <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else {
                std::cout << "Ошибка! Диапазон от " << min << " до " << max << std::endl;
                clearInputBuffer();
            }
        } else {
            std::cout << "Ошибка! Введите число" << std::endl;
            clearInputBuffer();
        }
    }
}

std::string Validator::getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::cin >> value;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

bool Validator::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

int Validator::getMenuChoice(int min, int max, const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= min && value <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else {
                std::cout << "Ошибка! Выберите пункт от " << min << " до " << max << std::endl;
            }
        } else {
            std::cout << "Ошибка! Введите число" << std::endl;
            clearInputBuffer();
        }
    }
}

// Реализация класса MenuManager
MenuManager::MenuManager() {}

void MenuManager::showMainMenu() {
    std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << std::endl;
    std::cout << "1. TreeFun2: Заполнить список и преобразовать в дерево поиска (BST)" << std::endl;
    std::cout << "2. TreeFun6: Итератор обхода КПЛ (на НЕСБАЛАНСИРОВАННОМ дереве)" << std::endl;
    std::cout << "3. TreeFun9: Размещение камер (на НЕСБАЛАНСИРОВАННОМ дереве)" << std::endl;
    std::cout << "0. Выход" << std::endl;
}

// Подменю для заполнения ИСХОДНОГО СПИСКА (Задание 2) — строгий порядок: рандом, Клава, файл
void MenuManager::fillListMenu(DoublyLinkedList& targetList) {
    std::cout << "\nВЫБОР СПОСОБА ЗАПОЛНЕНИЯ СПИСКА" << std::endl;
    std::cout << "1. Заполнить случайными числами" << std::endl;
    std::cout << "2. Ввести вручную с клавиатуры" << std::endl;
    std::cout << "3. Загрузить из файла input.txt" << std::endl;

    int choice = Validator::getMenuChoice(1, 3, "Выберите способ заполнения списка: ");
    targetList.clear();

    if (choice == 1) {
        int count = Validator::getIntInput(1, 50, "Введите количество элементов списка (1-50): ");
        for (int i = 0; i < count; i++) targetList.pushBack(rand() % 201 - 100);
        std::cout << "Список успешно заполнен случайными числами." << std::endl;
    } else if (choice == 2) {
        int count = Validator::getIntInput(1, 50, "Введите количество элементов списка (1-50): ");
        for (int i = 0; i < count; i++) {
            int val = Validator::getIntInput("Введите элемент списка " + std::to_string(i + 1) + ": ");
            targetList.pushBack(val);
        }
        std::cout << "Список успешно сформирован вручную." << std::endl;
    } else if (choice == 3) {
        if (!Validator::fileExists("input.txt")) {
            std::cout << "Ошибка! Файл input.txt не найден. Список оставлен пустым." << std::endl;
            return;
        }
        std::ifstream file("input.txt");
        int value;
        while (file >> value) targetList.pushBack(value);
        file.close();
        std::cout << "Список успешно загружен из файла input.txt." << std::endl;
    }
}

// Подменю для заполнения НЕСБАЛАНСИРОВАННЫХ ДЕРЕВЬЕВ (Задачи 6 и 9) — строгий порядок: рандом, клава, файл
void MenuManager::fillUnbalancedTreeMenu(BinaryTree& tree, int defaultCount) {
    std::cout << "\nВЫБОР СПОСОБА ЗАПОЛНЕНИЯ ДЕРЕВА" << std::endl;
    std::cout << "1. Заполнить случайными числами" << std::endl;
    std::cout << "2. Ввести вручную с клавиатуры" << std::endl;
    std::cout << "3. Загрузить из файла input.txt" << std::endl;

    int choice = Validator::getMenuChoice(1, 3, "Выберите способ: ");

    if (choice == 1) {
        int count = Validator::getIntInput(1, 50, "Введите количество элементов (1-50): ");
        tree.generateRandomUnbalanced(count);
        std::cout << "Дерево заполнено случайными числами с сохранением дисбаланса." << std::endl;
    } else if (choice == 2) {
        tree.clear();
        int count = Validator::getIntInput(1, 50, "Введите количество элементов дерева (1-50): ");
        for (int i = 0; i < count; i++) {
            int val = Validator::getIntInput("Введите узел " + std::to_string(i + 1) + ": ");
            tree.insertSingleUnbalanced(val);
        }
        std::cout << "Дерево успешно сформировано вручную (с сохранением дисбаланса)." << std::endl;
    } else if (choice == 3) {
        if (tree.generateFromFileUnbalanced("input.txt")) {
            std::cout << "Дерево успешно загружено из файла input.txt." << std::endl;
        } else {
            std::cout << "Ошибка! Файл input.txt не найден. Сгенерирован дефолтный рандом." << std::endl;
            tree.generateRandomUnbalanced(defaultCount);
        }
    }
}

void MenuManager::task2Menu() {
    std::cout << "\nTREEFUN2: ПРЕОБРАЗОВАНИЕ СПИСКА В ДЕРЕВО ПОИСКА (BST)" << std::endl;

    DoublyLinkedList temporalList;
    fillListMenu(temporalList);
    temporalList.printList();

    // Строим дерево поиска последовательным чтением элементов из созданного списка
    treeTask2.convertFromListToBST(temporalList);

    std::cout << "\nРезультат построения бинарного дерева поиска (BST) из списка:" << std::endl;
    treeTask2.printTree();
    std::cout << "Высота построенного дерева BST: " << treeTask2.getHeight() << std::endl;
}

void MenuManager::task6Menu() {
    std::cout << "\nTREEFUN6: ИТЕРАТОР ОБХОДА КОРЕНЬ-ПРАВО-ЛЕВО (не BST) " << std::endl;
    fillUnbalancedTreeMenu(treeTask6, 6);

    std::cout << "\nТекущее дерево:" << std::endl;
    treeTask6.printTree();
    std::cout << "Высота дерева: " << treeTask6.getHeight() << std::endl;

    std::cout << "\nОбход в порядке 'корень-право-лево': ";
    TreeIterator iterator(treeTask6.getRoot());
    while (iterator.hasNext()) {
        std::cout << iterator.next() << " ";
    }
    std::cout << std::endl;
}

void MenuManager::task9Menu() {
    std::cout << "\nTREEFUN9: РАЗМЕЩЕНИЕ КАМЕР НАБЛЮДЕНИЯ (не BST)" << std::endl;
    fillUnbalancedTreeMenu(treeTask9, 8);

    std::cout << "\nТекущее дерево:" << std::endl;
    treeTask9.printTree();
    std::cout << "Высота дерева: " << treeTask9.getHeight() << std::endl;

    CameraPlacer placer;
    int minCameras = placer.getMinCameras(treeTask9.getRoot());
    std::cout << "\nМинимальное количество камер для наблюдения: " << minCameras << std::endl;
    std::cout << "(Каждая камера обозревает узел, его предка и потомков)" << std::endl;
}

void MenuManager::run() {
    int choice;
    do {
        showMainMenu();
        choice = Validator::getMenuChoice(0, 3, "Выберите пункт меню: ");

        switch (choice) {
            case 1: task2Menu(); break;
            case 2: task6Menu(); break;
            case 3: task9Menu(); break;
            case 0: std::cout << "Выход из программы..." << std::endl; break;
        }
    } while (choice != 0);
}
