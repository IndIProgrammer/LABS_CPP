#include "head.h"

// РЕАЛИЗАЦИЯ КЛАССА ПРОВЕРОК

// Ввод целого числа в заданном диапазоне
int Validator::getIntInput(int min, int max, const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Ввод целого числа без ограничений
int Validator::getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите целое число: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Ввод вещественного числа в заданном диапазоне
double Validator::getDoubleInput(double min, double max, const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Ввод строки
std::string Validator::getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// Проверка существования файла
bool Validator::fileExists(const std::string& filename) {
    std::ifstream file(filename.c_str());
    return file.good();
}

// Проверка, является ли строка числом
bool Validator::isNumber(const std::string& str) {
    if (str.empty()) return false;
    for (size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

// Проверка, является ли символ допустимым оператором (+, -, *, /, %, ^)
bool Validator::isValidOperator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '%' || op == '^';
}

// РЕАЛИЗАЦИЯ КЛАССА УЗЛА

// Конструктор для числового узла
TreeNode::TreeNode(int val) : value(val), op(' '), left(nullptr), right(nullptr) {}

// Конструктор для узла-оператора
TreeNode::TreeNode(char operation) : value(0), op(operation), left(nullptr), right(nullptr) {}

// Деструктор
TreeNode::~TreeNode() {
    delete left;
    delete right;
}

// Проверка, является ли узел оператором
bool TreeNode::isOperator() const {
    return op != ' ';
}

// Проверка, является ли узел переменной x (кодируется значением -999)
bool TreeNode::isVariable() const {
    return value == -999;
}

// Преобразование узла в строку (число, оператор или "x")
std::string TreeNode::toString() const {
    if (isOperator()) {
        return std::string(1, op);
    } else if (value == -999) {
        return "x";
    } else {
        return std::to_string(value);
    }
}

// РЕАЛИЗАЦИЯ КЛАССА ДЕРЕВА ВЫРАЖЕНИЙ

// Конструктор по умолчанию
ExpressionTree::ExpressionTree() : root(nullptr) {}

// ДЕСТРУКТОР
ExpressionTree::~ExpressionTree() {
    clear();
}

// Полная очистка дерева
void ExpressionTree::clear() {
    if (root) {
        deleteTree(root);
        root = nullptr;
    }
}

// Итеративное удаление всех узлов поддерева
void ExpressionTree::deleteTree(TreeNode* node) {
    if (!node) return;

    std::vector<TreeNode*> stack;
    std::vector<TreeNode*> toDelete;
    stack.push_back(node);

    while (!stack.empty()) {
        TreeNode* current = stack.back();
        stack.pop_back();
        toDelete.push_back(current);

        if (current->left) stack.push_back(current->left);
        if (current->right) stack.push_back(current->right);
    }

    for (size_t i = 0; i < toDelete.size(); i++) {
        toDelete[i]->left = nullptr;
        toDelete[i]->right = nullptr;
        delete toDelete[i];
    }
}

// Рекурсивное копирование поддерева
TreeNode* ExpressionTree::copyTree(TreeNode* node) {
    if (!node) return nullptr;
    TreeNode* newNode = node->isOperator() ? new TreeNode(node->op) : new TreeNode(node->value);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

// ПОЛУЧАЕТ КОД ОПЕРАТОРА
int ExpressionTree::getOperatorCode(char op) {
    switch (op) {
        case '+': return -1;
        case '-': return -2;
        case '*': return -3;
        case '/': return -4;
        case '%': return -5;
        case '^': return -6;
        default: return 0;
    }
}

// ВОЗВРАЩАЕТ ОПЕРАТОР ВЗАВИСИММОСТИ ОТ ПОЛУЧЕННОГО КОДА
char ExpressionTree::getOperatorFromCode(int code) {
    switch (code) {
        case -1: return '+';
        case -2: return '-';
        case -3: return '*';
        case -4: return '/';
        case -5: return '%';
        case -6: return '^';
        default: return ' ';
    }
}

// ПОСТРОЕНИЕ ДЕРЕВА ИЗ ОБРАТНОЙ ПОЛЬСКОЙ ЗАПИСИ
TreeNode* ExpressionTree::buildFromRPN(const std::string& expression) {
    std::vector<TreeNode*> stack;
    std::string token;
    std::istringstream ss(expression); // Исправлено: istringstream

    while (ss >> token) {
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
            stack.push_back(new TreeNode(std::stoi(token)));
        } else if (token.length() == 1 && Validator::isValidOperator(token[0])) {
            if (stack.size() < 2) {
                std::cout << "Ошибка: неверное выражение RPN (недостаточно операндов)\n";
                for (size_t j = 0; j < stack.size(); j++) delete stack[j];
                return nullptr;
            }
            TreeNode* right = stack.back(); stack.pop_back();
            TreeNode* left = stack.back(); stack.pop_back();
            TreeNode* node = new TreeNode(token[0]);
            node->left = left;
            node->right = right;
            stack.push_back(node);
        }
    }

    if (stack.size() != 1) {
        if (!stack.empty()) {
            std::cout << "Ошибка: неверное выражение RPN (лишние операнды)\n";
            for (size_t j = 0; j < stack.size(); j++) delete stack[j];
        }
        return nullptr;
    }

    return stack.back();
}

// Вычисление значения дерева (без переменной x)
int ExpressionTree::calculate(TreeNode* node) {
    if (!node) return 0;

    std::vector<TreeNode*> stack;
    std::vector<TreeNode*> postorder;
    stack.push_back(node);

    // ОБРАТНЫЙ ОБХОД
    while (!stack.empty()) {
        TreeNode* current = stack.back();
        stack.pop_back();
        postorder.push_back(current);
        if (current->left) stack.push_back(current->left);
        if (current->right) stack.push_back(current->right);
        // ЭЛЕМЕНТЫ ЛЕЖАТ В ПОРЯДКЕ К - Л - П
    }

    std::map<TreeNode*, int> computed; // УЗЕЛ - ВЫЧИСЛЕННОЕ ЗНАЧЕНИЕ

    // ИДЁМ С КОНЦА ВЕКТОРА
    for (int i = postorder.size() - 1; i >= 0; i--) {
        TreeNode* current = postorder[i];

        if (!current->isOperator()) {
            computed[current] = current->value;

        } else {
            int leftVal = computed[current->left];
            int rightVal = computed[current->right];

            switch (current->op) {
                case '+': computed[current] = leftVal + rightVal; break;
                case '-': computed[current] = leftVal - rightVal; break;
                case '*': computed[current] = leftVal * rightVal; break;
                case '/':
                    if (rightVal == 0) {
                        std::cout << "Ошибка: деление на ноль\n";
                        computed[current] = 0;
                    } else {
                        computed[current] = leftVal / rightVal;
                    }
                    break;
                case '%':
                    if (rightVal == 0) {
                        std::cout << "Ошибка: остаток от деления на ноль\n";
                        computed[current] = 0;
                    } else {
                        computed[current] = leftVal % rightVal;
                    }
                    break;
                case '^': computed[current] = (int)pow(leftVal, rightVal); break;
                default:
                    std::cout << "Ошибка: неизвестная операция\n";
                    computed[current] = 0;
            }
        }
    }

    return computed[node];
}

// Замена поддеревьев с / и % на вычисленное значение (освобождает память удалённых узлов)
TreeNode* ExpressionTree::evaluateDivision(TreeNode* node) {
    if (!node) return nullptr;

    std::vector<TreeNode*> stack;
    std::vector<TreeNode*> postorder;
    stack.push_back(node);

    while (!stack.empty()) {
        TreeNode* current = stack.back();
        stack.pop_back();
        postorder.push_back(current);
        if (current->left) stack.push_back(current->left);
        if (current->right) stack.push_back(current->right);
    }

    std::map<TreeNode*, TreeNode*> replaced;

    for (int i = postorder.size() - 1; i >= 0; i--) {
        TreeNode* current = postorder[i];

        TreeNode* newLeft = current->left ? replaced[current->left] : nullptr;
        TreeNode* newRight = current->right ? replaced[current->right] : nullptr;

        if (current->isOperator() && (current->op == '/' || current->op == '%')) {
            if (!newLeft || !newRight) {
                std::cout << "Ошибка: неполное дерево для операции " << current->op << "\n";
                replaced[current] = current;
                continue;
            }

            int leftVal = calculate(newLeft);
            int rightVal = calculate(newRight);

            int result;
            if (current->op == '/') {
                if (rightVal == 0) {
                    std::cout << "Ошибка: деление на ноль\n";
                    result = 0;
                } else {
                    result = leftVal / rightVal;
                }
            } else {
                if (rightVal == 0) {
                    std::cout << "Ошибка: остаток от деления на ноль\n";
                    result = 0;
                } else {
                    result = leftVal % rightVal;
                }
            }

            delete newLeft;
            delete newRight;

            TreeNode* newLeaf = new TreeNode(result);
            replaced[current] = newLeaf;

        } else {
            current->left = newLeft;
            current->right = newRight;
            replaced[current] = current;
        }
    }

    return replaced[node];
}

// ФУНКЦИИ ДЛЯ ЗАДАНИЯ 4

// ЗАПОЛНЕНИЕ ДЕРЕВА
void ExpressionTree::loadRandomForTask4() {
    clear();

    char ops[] = {'+', '-', '*', '/'};
    int num1 = rand() % 20 + 1;
    int num2 = rand() % 20 + 1;
    char op = ops[rand() % 4];

    root = new TreeNode(op);
    root->left = new TreeNode(num1);
    root->right = new TreeNode(num2);

    std::cout << "Создано случайное выражение: " << num1 << " " << num2 << " " << op << std::endl;
}

void ExpressionTree::loadFromFileForTask4(const std::string& fn) {
    clear(); // Сначала очищаем старое дерево
    std::ifstream file(fn.c_str());
    if (!file.is_open()) {
        std::cout << "Ошибка: файл " << fn << " не найден\n";
        return;
    }
    std::string expression;
    std::getline(file, expression);
    if (!expression.empty()) {
        root = buildFromRPN(expression);
    } else {
        std::cout << "Ошибка: файл пуст\n";
    }
}

void ExpressionTree::loadFromKeyboardForTask4() {
    clear();
    std::cout << "Введите выражение в обратной польской записи (например: 2 3 +): ";
    std::string expression;
    std::getline(std::cin, expression);

    if (expression.empty()) {
        std::cout << "Ошибка: пустое выражение\n";
        return;
    }

    root = buildFromRPN(expression);
}

// Замена всех / и % в дереве на вычисленные значения (для задания 4)
void ExpressionTree::transformDivision() {
    root = evaluateDivision(root);
}

// СОХРАНЕНИЕ В ФАЙЛ
void ExpressionTree::saveTreeToFileForTask4(const std::string& fn) {
    std::ofstream file(fn.c_str());
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось создать файл " << fn << std::endl;
        return;
    }

    std::vector<TreeNode*> stack;
    stack.push_back(root);

    while (!stack.empty()) {
        TreeNode* node = stack.back();
        stack.pop_back();

        if (node->isOperator()) {
            file << getOperatorCode(node->op) << " ";
        } else {
            file << node->value << " ";
        }
        if (node->right) stack.push_back(node->right);
        if (node->left) stack.push_back(node->left);
    }

    file.close();
}

// ФУНКЦИИ ДЛЯ ЗАДАНИЯ 26
int ExpressionTree::getPriority(char op) {
    switch (op) {
        case '^': return 3;
        case '*': case '/': case '%': return 2;
        case '+': case '-': return 1;
        default: return 0;
    }
}

// ПРЕОБРАЗОВАИЕ ИЗ ИНФИКСНОЙ ЗАПИСИ В ОПЗ
std::vector<std::string> ExpressionTree::infixToRPN(const std::string& expression) {
    std::vector<std::string> output;
    std::vector<char> operators;
    std::string number;

    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];

        // МНОГОЗНАЧНОЕ ЧИСЛО
        if (isdigit(c)) {
            number += c;

            // ДЛЯ 2х
        } else if (c == 'x') {
            if (!number.empty()) {
                output.push_back(number);
                number.clear();
            }
            output.push_back("x");

            // ДОБАВЛЕНИЕ ОПЕРАТОРА
        } else if (Validator::isValidOperator(c)) {
            if (!number.empty()) {
                output.push_back(number);
                number.clear();
            }
            // ПРОВЕРКА НА ПРИОРИТЕТЫ
            while (!operators.empty() && operators.back() != '(' &&
                   ((getPriority(operators.back()) > getPriority(c)) ||
                    (getPriority(operators.back()) == getPriority(c) && c != '^'))) {
                output.push_back(std::string(1, operators.back()));
                operators.pop_back();
            }
            operators.push_back(c);
        } else if (c == '(') {
            if (!number.empty()) {
                output.push_back(number);
                number.clear();
            }
            operators.push_back(c);
        } else if (c == ')') {
            if (!number.empty()) {
                output.push_back(number);
                number.clear();
            }
            while (!operators.empty() && operators.back() != '(') {
                output.push_back(std::string(1, operators.back()));
                operators.pop_back();
            }
            if (!operators.empty()) operators.pop_back();
        }
    }

    if (!number.empty()) {
        output.push_back(number);
    }

    // ВЫВОДИМ ОСТАВШИЕСЯ ОПЕРАТОРЫ
    while (!operators.empty()) {
        output.push_back(std::string(1, operators.back()));
        operators.pop_back();
    }

    return output;
}

// ПОСТРОЕНИЕ ДЕРЕВА ИЗ ОПЗ ДЛЯ 26 ЗАДАНИЯ
TreeNode* ExpressionTree::buildFromRPNForTask26(const std::vector<std::string>& rpn) {
    std::vector<TreeNode*> stack;

    for (size_t i = 0; i < rpn.size(); i++) {
        const std::string& token = rpn[i];

        if (token == "x") {
            stack.push_back(new TreeNode(-999));
        } else if (Validator::isNumber(token)) {
            stack.push_back(new TreeNode(std::stoi(token)));
        } else if (token.length() == 1 && Validator::isValidOperator(token[0])) {
            if (stack.size() < 2) {
                std::cout << "Ошибка: недостаточно операндов для оператора " << token << "\n";
                for (size_t j = 0; j < stack.size(); j++) delete stack[j];
                return nullptr; // Возвращаем пустоту вместо defaultRoot
            }
            TreeNode* right = stack.back(); stack.pop_back();
            TreeNode* left = stack.back(); stack.pop_back();
            TreeNode* node = new TreeNode(token[0]);
            node->left = left;
            node->right = right;
            stack.push_back(node);
        }
    }

    if (stack.size() != 1) {
        if (!stack.empty()) {
            std::cout << "Ошибка: неверное выражение (лишние операнды)\n";
            for (size_t j = 0; j < stack.size(); j++) delete stack[j];
        }
        return nullptr;
    }

    return stack.back();
}

// ВЫЧИСЛЕНИЕ ЗНАЧЕНИЯ С ПОДСТАНОВКОЙ X
int ExpressionTree::evaluate(TreeNode* node, int x) {
    if (!node) return 0;

    std::vector<TreeNode*> stack;
    std::vector<TreeNode*> postorder;
    stack.push_back(node);

    while (!stack.empty()) {
        TreeNode* current = stack.back();
        stack.pop_back();
        postorder.push_back(current);
        if (current->left) stack.push_back(current->left);
        if (current->right) stack.push_back(current->right);
    }

    std::map<TreeNode*, int> computed;

    for (int i = postorder.size() - 1; i >= 0; i--) {
        TreeNode* current = postorder[i];

        if (!current->isOperator()) {
            computed[current] = (current->value == -999) ? x : current->value; // ПОДСТАНОВКА X
        } else {
            int leftVal = computed[current->left];
            int rightVal = computed[current->right];

            switch (current->op) {
                case '+': computed[current] = leftVal + rightVal; break;
                case '-': computed[current] = leftVal - rightVal; break;
                case '*': computed[current] = leftVal * rightVal; break;
                case '/':
                    if (rightVal == 0) {
                        std::cout << "Ошибка: деление на ноль\n";
                        computed[current] = 0;
                    } else {
                        computed[current] = leftVal / rightVal;
                    }
                    break;
                case '%':
                    if (rightVal == 0) {
                        std::cout << "Ошибка: остаток от деления на ноль\n";
                        computed[current] = 0;
                    } else {
                        computed[current] = leftVal % rightVal;
                    }
                    break;
                case '^': computed[current] = (int)pow(leftVal, rightVal); break;
                default:
                    std::cout << "Ошибка: неизвестная операция\n";
                    computed[current] = 0;
            }
        }
    }

    return computed[node];
}

// ЗАМЕНА ПЕРЕМЕННОЙ X НА ЗНАЧЕНИЕ
TreeNode* ExpressionTree::replaceXWithValue(TreeNode* node, int x) {
    if (!node) return nullptr;

    std::vector<TreeNode*> stack;
    stack.push_back(node);

    // ПРОХОДИМ ВСЕ УЗЛЫ И ИЩЕМ "X"
    while (!stack.empty()) {
        TreeNode* current = stack.back();
        stack.pop_back();

        if (!current->isOperator()) {
            if (current->value == -999) {
                current->value = x; // ЗАМЕНА X НА ЧИСЛО
            }
        } else {
            if (current->right) stack.push_back(current->right);
            if (current->left) stack.push_back(current->left);
        }
    }

    return node;
}

// ЗАПОЛНЕНИЕ ДЕРЕВА
void ExpressionTree::loadRandomForTask26() {
    clear();

    char ops[] = {'+', '-', '*', '/'};
    int num = rand() % 20 + 1;
    char op1 = ops[rand() % 4];
    char op2 = ops[rand() % 4];

    root = new TreeNode(op2);
    root->left = new TreeNode(op1);
    root->left->left = new TreeNode(-999); // X
    root->left->right = new TreeNode(num);
    root->right = new TreeNode(rand() % 10 + 1);

    std::cout << "Создано случайное выражение с переменной x\n";
}

void ExpressionTree::loadFromFileForTask26(const std::string& fn1) {
    clear(); // Гарантируем чистоту
    std::ifstream file(fn1.c_str());
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << fn1 << std::endl;
        return;
    }
    std::string expression;
    if (std::getline(file, expression) && !expression.empty()) {
        std::vector<std::string> rpn = infixToRPN(expression);
        root = buildFromRPNForTask26(rpn);
    } else {
        std::cout << "Ошибка: файл пуст\n";
    }
    file.close();
}

void ExpressionTree::loadFromKeyboardForTask26() {
    clear();
    std::cout << "Введите выражение в инфиксной форме (с переменной x): ";
    std::string expression;
    std::getline(std::cin, expression);

    if (expression.empty()) {
        std::cout << "Ошибка: введена пустая строка\n";
        return;
    }

    std::vector<std::string> rpn = infixToRPN(expression);
    root = buildFromRPNForTask26(rpn);

    if (!root) {
        std::cout << "Ошибка построения дерева из введенного выражения.\n";
    }
}

// ВЫЧИСЛЕНИЕ С "X"
int ExpressionTree::evaluateAndTransform(int x) {
    if (!root) return 0;
    int result = evaluate(root, x);
    root = replaceXWithValue(root, x);
    return result;
}

// СОХРАНЕНИЕ РЕЗУЛЬТАТА В ФАЙЛ
void ExpressionTree::saveResultToFile(const std::string& fn2) {
    std::ofstream out(fn2.c_str());
    if (!out.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << fn2 << std::endl;
        return;
    }
    out.close();
}

// ВЫВОД ДЕРЕВА БОКОМ
void ExpressionTree::printTreeSideways(TreeNode* node, int level, std::ofstream& out) {
    if (!node) return;

    std::vector<std::pair<TreeNode*, int> > stack;
    TreeNode* current = node;
    int currLevel = level;

    while (current || !stack.empty()) {
        while (current) {
            stack.push_back(std::make_pair(current, currLevel));
            current = current->right;
            currLevel++;
        }

        if (!stack.empty()) {
            current = stack.back().first;
            currLevel = stack.back().second;
            stack.pop_back();

            for (int i = 0; i < currLevel * 4; i++) {
                out << " ";
            }
            out << current->toString() << std::endl;

            current = current->left;
            currLevel++;
        }
    }
}

void ExpressionTree::printTreeToFile(const std::string& fn2) {
    std::ofstream out(fn2.c_str(), std::ios::app);
    if (!out.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << fn2 << std::endl;
        return;
    }

    out << "\nДерево после преобразования:\n";
    printTreeSideways(root, 0, out);
    out.close();
}

// ОБЩИЕ МЕТОДЫ ЗАПОЛНЕНИЯ
void ExpressionTree::fillRandom() {
    clear();

    char ops[] = {'+', '-', '*'};
    int num1 = rand() % 20 + 1;
    int num2 = rand() % 20 + 1;
    char op = ops[rand() % 3];

    root = new TreeNode(op);
    root->left = new TreeNode(num1);
    root->right = new TreeNode(num2);

    std::cout << "Создано выражение: " << num1 << " " << op << " " << num2 << std::endl;
}

void ExpressionTree::fillFromKeyboard() {
    clear();
    std::cout << "Введите выражение в инфиксной форме: ";
    std::string expression;
    std::getline(std::cin, expression);

    if (expression.empty()) {
        std::cout << "Ошибка: пустое выражение!\n";
        return;
    }

    std::vector<std::string> rpn = infixToRPN(expression);
    root = buildFromRPNForTask26(rpn);
}

void ExpressionTree::fillFromFile(const std::string& inputFile) {
    std::ifstream file(inputFile.c_str());
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << inputFile << std::endl;
        clear();
        return;
    }

    std::string expression;
    if (!std::getline(file, expression) || expression.empty()) {
        std::cout << "Ошибка: файл пуст или не читается\n";
        file.close();
        clear();
        return;
    }
    file.close();

    clear();
    std::vector<std::string> rpn = infixToRPN(expression);
    root = buildFromRPNForTask26(rpn);
}

// ГРАФИЧЕСКИЙ ВЫВОД ДЕРЕВА

// Вывод дерева боком
void ExpressionTree::printGraphical(TreeNode* node, int space, std::ostream& out) {
    if (!node) return;

    std::vector<std::pair<TreeNode*, int> > rightStack;
    TreeNode* current = node;
    int currSpace = space + 4;

    while (current || !rightStack.empty()) {
        while (current) {
            rightStack.push_back(std::make_pair(current, currSpace));
            current = current->right;
            currSpace += 4;
        }

        if (!rightStack.empty()) {
            current = rightStack.back().first;
            currSpace = rightStack.back().second;
            rightStack.pop_back();

            out << std::endl;
            for (int i = 4; i < currSpace; i++) {
                out << " ";
            }
            out << current->toString();

            current = current->left;
            currSpace += 4;
        }
    }
}

// В консоль
void ExpressionTree::printGraphical() {
    printGraphical(root, 0, std::cout);
    std::cout << std::endl;
}

// В файл
void ExpressionTree::printGraphicalToFile(const std::string& filename) {
    std::ofstream file(filename.c_str());
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось создать файл " << filename << std::endl;
        return;
    }

    file << "Дерево:\n";
    printGraphical(root, 0, file);
    file << std::endl;
    file.close();
}

// РЕАЛИЗАЦИЯ КЛАССА МЕНЮ

// Конструктор
MenuManager::MenuManager(ExpressionTree& t) : tree(t) {}

void MenuManager::run() {
    int choice;
    do {
        showMainMenu();
        choice = Validator::getIntInput(0, 4, "");

        switch (choice) {
            case 1:
                fillMenu();
                break;
            case 2:
                std::cout << "\nДЕРЕВО\n";
                if (!tree.isEmpty()) {
                    tree.printGraphical();
                } else {
                    std::cout << "Дерево пусто! Сначала заполните дерево (пункт 1).\n";
                }
                break;
            case 3:
                task4Menu();
                break;
            case 4:
                task26Menu();
                break;
            case 0:
                std::cout << "Завершение программы . . .\n";
                break;
        }
    } while (choice != 0);
}

void MenuManager::showMainMenu() {
    std::cout << "\nГЛАВНОЕ МЕНЮ\n";
    std::cout << "1. Заполнить дерево\n";
    std::cout << "2. Показать дерево\n";
    std::cout << "3. Задача 4 (Обратная польская запись)\n";
    std::cout << "4. Задача 26 (Инфиксная запись с переменной x)\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите пункт: ";
}

void MenuManager::fillMenu() {
    std::cout << "\nЗАПОЛНЕНИЕ ДЕРЕВА\n";
    std::cout << "1. Случайно\n";
    std::cout << "2. С клавиатуры\n";
    std::cout << "3. Из файла (input.txt)\n";
    std::cout << "0. Назад\n";
    std::cout << "Выберите способ: ";

    int choice = Validator::getIntInput(0, 3, "");

    switch (choice) {
        case 1:
            tree.fillRandom();
            break;
        case 2:
            tree.fillFromKeyboard();
            break;
        case 3:
            if (Validator::fileExists("input.txt")) {
                tree.fillFromFile("input.txt");
                std::cout << "Дерево заполнено из файла!\n";
            } else {
                std::cout << "Файл input.txt не найден!\n";
            }
            break;
        case 0:
            return;
    }
}

void MenuManager::task4Menu() {
    std::cout << "\nЗАДАЧА 4\n";
    std::cout << "1. Случайное выражение\n";
    std::cout << "2. С клавиатуры\n";
    std::cout << "3. Из файла (InputFor4.txt)\n";
    std::cout << "0. Назад\n";
    std::cout << "Выберите пункт: ";

    int choice = Validator::getIntInput(0, 3, "");

    switch (choice) {
        case 1:
            tree.loadRandomForTask4();
            break;
        case 2:
            tree.loadFromKeyboardForTask4();
            break;
        case 3:
            if (Validator::fileExists("InputFor4.txt")) {
                tree.loadFromFileForTask4("InputFor4.txt");
                if (!tree.isEmpty()) {
                    std::cout << "Выражение успешно загружено из файла\n";
                }
            } else {
                std::cout << "Ошибка: Файл InputFor4.txt не найден!\n";
            }
            break;
        case 0:
            return;
    }
    if (tree.isEmpty()) {
        std::cout << "Дерево пусто. Операция прервана.\n";
        return;
    }

    tree.printGraphical();
    tree.transformDivision();

    std::cout << "\nИсходное дерево:\n";
    tree.printGraphical();

    tree.transformDivision();
    std::cout << "\nПосле замены деления:\n";
    tree.printGraphical();

    tree.saveTreeToFileForTask4("result_task4.txt");
    std::cout << "\nРезультат сохранен в result_task4.txt\n";
    std::cout << "\n";
    std::cout << "./\\.../\\" << std::endl;
    std::cout << "(.'0.0'.)" << std::endl;
    std::cout << " ..=*=.." << std::endl;
    std::cout << "(.\\.||./.)~~**" << std::endl;
}

void MenuManager::task26Menu() {
    std::cout << "\nЗАДАЧА 26\n";
    std::cout << "1. Случайное выражение\n";
    std::cout << "2. С клавиатуры\n";
    std::cout << "3. Из файла (FN1.txt)\n";
    std::cout << "0. Назад\n";
    std::cout << "Выберите пункт: ";

    int choice = Validator::getIntInput(0, 3, "");

    if (choice == 0) return;

    switch (choice) {
        case 1:
            tree.loadRandomForTask26();
            break;
        case 2:
            tree.loadFromKeyboardForTask26();
            break;
        case 3:
            if (Validator::fileExists("FN1.txt")) {
                tree.loadFromFileForTask26("FN1.txt");
                std::cout << "Выражение загружено из файла\n";
            } else {
                // Убрали подстановку по умолчанию
                std::cout << "Ошибка: Файл FN1.txt не найден!\n";
            }
            break;
    }

    if (tree.isEmpty()) {
        std::cout << "Дерево не было создано. Операция отменена.\n";
        return;
    }

    std::cout << "\nИсходное дерево:\n";
    tree.printGraphical();

    int x = Validator::getIntInput("Введите значение x: ");
    int result = tree.evaluateAndTransform(x);

    std::cout << "\nРезультат вычисления: " << result << std::endl;
    std::cout << "\nПосле замены x на " << x << ":\n";
    tree.printGraphical();

    std::ofstream out("FN2.txt");
    if (out.is_open()) {
        out << "x = " << x << std::endl;
        out << "Результат: " << result << std::endl << std::endl;
        out.close();
    }

    tree.printTreeToFile("FN2.txt");
    std::cout << "\nРезультат сохранен в FN2.txt\n";

    // Котик :)
    std::cout << "\n./\\.../\\\n(.'0.0'.)\n ..=*=..\n(.\\.||./.)~~**\n" << std::endl;
}
