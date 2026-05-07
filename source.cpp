#include "head.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <fstream>

// Конструкторов
BinaryTree::BinaryTree() : data(0), left(nullptr), right(nullptr), root(nullptr) {}

BinaryTree::BinaryTree(int val) : data(val), left(nullptr), right(nullptr), root(nullptr) {}

// Деструктор
BinaryTree::~BinaryTree() {
    clearTree(root);
}

// Удаление дерева
void BinaryTree::clearTree(BinaryTree*& node) {
    if (node) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
        node = nullptr;
    }
}

// Получить высоту дерева
int BinaryTree::getHeight(BinaryTree* node) {
    if (!node) return 0;
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

// Простая функция вывода дерева (используем геттеры)
void printTreeRecursive(BinaryTree* node, int level) {
    if (!node) return;

    printTreeRecursive(node->getRight(), level + 1);

    for (int i = 0; i < level; i++) {
        std::cout << "    ";
    }
    std::cout << node->getData() << std::endl;

    printTreeRecursive(node->getLeft(), level + 1);
}

void BinaryTree::printGraphicalTree() {
    if (!root) {
        std::cout << "Дерево пусто!" << std::endl;
        return;
    }

    std::cout << "\n=== ГРАФИЧЕСКОЕ ПРЕДСТАВЛЕНИЕ ДЕРЕВА ===" << std::endl;
    printTreeRecursive(root, 0);
    std::cout << "=========================================" << std::endl;
}

// Способ 1: Ручной ввод
void BinaryTree::inputManual() {
    clearTree(root);
    root = nullptr;

    std::cout << "\nРУЧНОЙ ВВОД ДЕРЕВА" << std::endl;

    int n = InputValidator::getNodeCount();

    std::cout << "Выберите тип распределения узлов:" << std::endl;
    std::cout << "1. Обычное (полное бинарное дерево)" << std::endl;
    std::cout << "2. Несбалансированное (нечетные влево, четные вправо)" << std::endl;
    int distType = InputValidator::getIntInRange("Выберите (1-2): ", 1, 2);

    std::cout << "Вводите значения через пробел в порядке уровней (для пустых узлов введите 0):" << std::endl;
    std::vector<int> values;
    for (int i = 0; i < n; i++) {
        int val = InputValidator::getNodeValue("");
        values.push_back(val);
    }

    if (values.empty() || values[0] == 0) {
        std::cout << "Корень не может быть пустым!" << std::endl;
        return;
    }

    // Создаем узлы для всех значений (включая нулевые)
    std::vector<BinaryTree*> nodes;
    for (size_t i = 0; i < values.size(); i++) {
        if (values[i] != 0) {
            nodes.push_back(new BinaryTree(values[i]));
        } else {
            nodes.push_back(nullptr);
        }
    }

    root = nodes[0];

    // Связываем узлы в зависимости от выбранного типа
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i] != nullptr) {
            int leftIdx = 2 * i + 1;
            int rightIdx = 2 * i + 2;

            if (distType == 1) {
                // Обычное связывание
                if (leftIdx < (int)nodes.size()) {
                    nodes[i]->setLeft(nodes[leftIdx]);
                }
                if (rightIdx < (int)nodes.size()) {
                    nodes[i]->setRight(nodes[rightIdx]);
                }
            } else {
                // Несбалансированное: нечетные индексы влево, четные вправо
                if (leftIdx < (int)nodes.size()) {
                    if (leftIdx % 2 != 0) { // нечетный индекс
                        nodes[i]->setLeft(nodes[leftIdx]);
                    } else { // четный индекс
                        nodes[i]->setRight(nodes[leftIdx]);
                    }
                }
                if (rightIdx < (int)nodes.size()) {
                    if (rightIdx % 2 != 0) { // нечетный индекс
                        nodes[i]->setLeft(nodes[rightIdx]);
                    } else { // четный индекс
                        nodes[i]->setRight(nodes[rightIdx]);
                    }
                }
            }
        }
    }

    std::cout << "Дерево успешно создано!" << std::endl;
    printGraphicalTree();
}

// Способ 2: Случайный ввод
void BinaryTree::inputRandom() {
    clearTree(root);
    root = nullptr;

    std::cout << "\nСЛУЧАЙНЫЙ ВВОД ДЕРЕВА" << std::endl;

    int n = InputValidator::getNodeCount();

    std::cout << "Выберите тип распределения узлов:" << std::endl;
    std::cout << "1. Обычное (полное бинарное дерево)" << std::endl;
    std::cout << "2. Несбалансированное (нечетные влево, четные вправо)" << std::endl;
    int distType = InputValidator::getIntInRange("Выберите (1-2): ", 1, 2);

    std::cout << "Хотите задать диапазон случайных чисел? (1 - да, 0 - нет): ";
    int choice = InputValidator::getIntInRange("", 0, 1);

    int minVal = 1, maxVal = 100;
    if (choice == 1) {
        InputValidator::getRange(minVal, maxVal);
    }

    srand(time(nullptr));

    // Создаем массив значений
    std::vector<int> values;
    for (int i = 0; i < n; i++) {
        values.push_back(minVal + rand() % (maxVal - minVal + 1));
    }

    std::cout << "Сгенерированные значения: ";
    for (int val : values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Создаем узлы для всех значений
    std::vector<BinaryTree*> nodes;
    for (int i = 0; i < n; i++) {
        nodes.push_back(new BinaryTree(values[i]));
    }

    root = nodes[0];

    // Связываем узлы в зависимости от выбранного типа
    for (int i = 0; i < n; i++) {
        int leftIdx = 2 * i + 1;
        int rightIdx = 2 * i + 2;

        if (distType == 1) {
            // Обычное связывание (полное бинарное дерево)
            if (leftIdx < n) {
                nodes[i]->setLeft(nodes[leftIdx]);
            }
            if (rightIdx < n) {
                nodes[i]->setRight(nodes[rightIdx]);
            }
        } else {
            // Несбалансированное: нечетные индексы влево, четные вправо
            if (leftIdx < n) {
                if (leftIdx % 2 != 0) { // нечетный индекс
                    nodes[i]->setLeft(nodes[leftIdx]);
                } else { // четный индекс
                    nodes[i]->setRight(nodes[leftIdx]);
                }
            }
            if (rightIdx < n) {
                if (rightIdx % 2 != 0) { // нечетный индекс
                    nodes[i]->setLeft(nodes[rightIdx]);
                } else { // четный индекс
                    nodes[i]->setRight(nodes[rightIdx]);
                }
            }
        }
    }

    std::cout << "Сгенерировано дерево с " << n << " узлами!" << std::endl;
    printGraphicalTree();
}

// Способ 3: Ввод из файла input.txt
void BinaryTree::inputFromFile() {
    clearTree(root);
    root = nullptr;

    std::cout << "\nВВОД ДЕРЕВА ИЗ ФАЙЛА input.txt" << std::endl;

    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл input.txt!" << std::endl;
        std::cout << "Убедитесь, что файл существует в текущей директории." << std::endl;
        return;
    }

    std::vector<int> values;
    int val;

    // Читаем все числа из файла
    while (file >> val) {
        values.push_back(val);
    }
    file.close();

    if (values.empty()) {
        std::cout << "Ошибка: Файл пуст!" << std::endl;
        return;
    }

    if (values[0] == 0) {
        std::cout << "Ошибка: Корень не может быть пустым (0)!" << std::endl;
        return;
    }

    std::cout << "Прочитаны значения из файла: ";
    for (int v : values) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "Выберите тип распределения узлов:" << std::endl;
    std::cout << "1. Обычное (полное бинарное дерево)" << std::endl;
    std::cout << "2. Несбалансированное (нечетные влево, четные вправо)" << std::endl;
    int distType = InputValidator::getIntInRange("Выберите (1-2): ", 1, 2);

    // Создаем узлы для всех значений (включая нулевые)
    std::vector<BinaryTree*> nodes;
    for (size_t i = 0; i < values.size(); i++) {
        if (values[i] != 0) {
            nodes.push_back(new BinaryTree(values[i]));
        } else {
            nodes.push_back(nullptr);
        }
    }

    root = nodes[0];

    // Связываем узлы в зависимости от выбранного типа
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i] != nullptr) {
            int leftIdx = 2 * i + 1;
            int rightIdx = 2 * i + 2;

            if (distType == 1) {
                // Обычное связывание
                if (leftIdx < (int)nodes.size()) {
                    nodes[i]->setLeft(nodes[leftIdx]);
                }
                if (rightIdx < (int)nodes.size()) {
                    nodes[i]->setRight(nodes[rightIdx]);
                }
            } else {
                // Несбалансированное: нечетные индексы влево, четные вправо
                if (leftIdx < (int)nodes.size()) {
                    if (leftIdx % 2 != 0) { // нечетный индекс
                        nodes[i]->setLeft(nodes[leftIdx]);
                    } else { // четный индекс
                        nodes[i]->setRight(nodes[leftIdx]);
                    }
                }
                if (rightIdx < (int)nodes.size()) {
                    if (rightIdx % 2 != 0) { // нечетный индекс
                        nodes[i]->setLeft(nodes[rightIdx]);
                    } else { // четный индекс
                        nodes[i]->setRight(nodes[rightIdx]);
                    }
                }
            }
        }
    }

    std::cout << "Дерево успешно создано из файла!" << std::endl;
    printGraphicalTree();
}

// TreeWork4: Вывести содержимое листьев слева направо
void BinaryTree::getLeavesLeftToRight(BinaryTree* node, std::vector<int>& leaves) {
    if (!node) return;

    if (!node->getLeft() && !node->getRight()) {
        leaves.push_back(node->getData());
        return;
    }

    getLeavesLeftToRight(node->getLeft(), leaves);
    getLeavesLeftToRight(node->getRight(), leaves);
}

void BinaryTree::printLeavesLeftToRight() {
    if (!root) {
        std::cout << "Дерево пусто!" << std::endl;
        return;
    }

    std::vector<int> leaves;
    getLeavesLeftToRight(root, leaves);

    std::cout << "\nTreeWork4: Листья дерева (слева направо)" << std::endl;
    if (leaves.empty()) {
        std::cout << "Нет листьев (дерево пусто)" << std::endl;
    } else {
        std::cout << "Листья: ";
        for (size_t i = 0; i < leaves.size(); i++) {
            std::cout << leaves[i];
            if (i < leaves.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

// TreeWork13: Вывести количество листьев
int BinaryTree::countLeavesHelper(BinaryTree* node) {
    if (!node) return 0;

    if (!node->getLeft() && !node->getRight()) return 1;

    return countLeavesHelper(node->getLeft()) + countLeavesHelper(node->getRight());
}

int BinaryTree::countLeaves() {
    int count = countLeavesHelper(root);
    std::cout << "\nTreeWork13: Количество листьев" << std::endl;
    std::cout << "Количество листьев: " << count << std::endl;
    return count;
}

// TreeWork20: Проверка AVL-сбалансированности
bool BinaryTree::isAVLHelper(BinaryTree* node, int& height) {
    if (!node) {
        height = 0;
        return true;
    }

    int leftHeight = 0, rightHeight = 0;

    bool leftIsAVL = isAVLHelper(node->getLeft(), leftHeight);
    bool rightIsAVL = isAVLHelper(node->getRight(), rightHeight);

    height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    int diff = leftHeight - rightHeight;
    if (diff < 0) diff = -diff;
    bool currentIsBalanced = diff <= 1;

    return leftIsAVL && rightIsAVL && currentIsBalanced;
}

bool BinaryTree::isAVLBalanced() {
    if (!root) {
        std::cout << "\nTreeWork20: Проверка AVL-сбалансированности" << std::endl;
        std::cout << "Результат: False (дерево пусто)" << std::endl;
        return false;
    }

    int height = 0;
    bool result = isAVLHelper(root, height);

    std::cout << "\nTreeWork20: Проверка AVL-сбалансированности" << std::endl;
    std::cout << "Результат: " << (result ? "True" : "False") << std::endl;
    std::cout << "Высота дерева: " << height << std::endl;

    if (!result) {
        std::cout << "Дерево НЕ является AVL-сбалансированным!" << std::endl;
    } else {
        std::cout << "Дерево является AVL-сбалансированным!" << std::endl;
    }

    return result;
}

// Функции меню
void showMainMenu() {
    std::cout << "\nГЛАВНОЕ МЕНЮ" << std::endl;
    std::cout << "1. Ввод нового дерева" << std::endl;
    std::cout << "2. TreeWork4 - Вывести листья" << std::endl;
    std::cout << "3. TreeWork13 - Кол-во листьев" << std::endl;
    std::cout << "4. TreeWork20 - AVL-баланс" << std::endl;
    std::cout << "5. Вывести дерево" << std::endl;
    std::cout << "0. Выход" << std::endl;
}

void inputTree(BinaryTree& tree) {
    std::cout << "\nВЫБОР СПОСОБА ЗАПОЛНЕНИЯ ДЕРЕВА" << std::endl;
    std::cout << "1. Ручной ввод" << std::endl;
    std::cout << "2. Случайный ввод" << std::endl;
    std::cout << "3. Ввод из файла (input.txt)" << std::endl;

    int choice = InputValidator::getInputMethod();

    switch(choice) {
        case 1:
            tree.inputManual();
            break;
        case 2:
            tree.inputRandom();
            break;
        case 3:
            tree.inputFromFile();
            break;
    }
}

void handleMenuChoice(int choice, BinaryTree& tree) {
    switch(choice) {
        case 1:
            inputTree(tree);
            break;
        case 2:
            if (InputValidator::isTreeNotEmpty(tree.getRoot())) {
                std::cout << "\nДО ПРЕОБРАЗОВАНИЯ:" << std::endl;
                tree.printGraphicalTree();
                tree.printLeavesLeftToRight();
            }
            break;
        case 3:
            if (InputValidator::isTreeNotEmpty(tree.getRoot())) {
                std::cout << "\nДО ПРЕОБРАЗОВАНИЯ:" << std::endl;
                tree.printGraphicalTree();
                tree.countLeaves();
            }
            break;
        case 4:
            if (InputValidator::isTreeNotEmpty(tree.getRoot())) {
                std::cout << "\nДО ПРЕОБРАЗОВАНИЯ:" << std::endl;
                tree.printGraphicalTree();
                tree.isAVLBalanced();
            }
            break;
        case 5:
            if (InputValidator::isTreeNotEmpty(tree.getRoot())) {
                tree.printGraphicalTree();
            }
            break;
        case 0:
            std::cout << "Программа завершена." << std::endl;
            break;
        default:
            std::cout << "Ошибка: Неверный выбор! (0-5)" << std::endl;
    }
}
