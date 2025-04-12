#include "my_btree_funcs.h"

BTree *create_node (int data) {
    BTree *node = new BTree();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

BTree *btree_insert (BTree *node, int data) {
    if (node == nullptr)
        return create_node(data);
    if (data < node->data) {
        node->left = btree_insert(node->left, data);
    }
    else if (data > node->data) {
        node->right = btree_insert(node->right, data);
    } else {
        node->left = btree_insert(node->left, data);
    }
return node;
}

void btree_inorder (BTree *node) {
    if (node == nullptr)
        return;
    cout << node->data << " ";
    btree_inorder(node->left);
    btree_inorder(node->right);
}

void btree_preorder (BTree *node) {
    if (node == nullptr)
        return;
    btree_preorder(node->left);
    cout << node->data << " ";
    btree_preorder(node->right);
}

void btree_postorder (BTree *node) { // хуй знает я тупой
    if (node == nullptr)
        return;
    btree_postorder(node->left);
    btree_postorder(node->right);
    cout << node->data << " ";
}

void find_min (BTree *node) {

    while (node->left != nullptr)
       node = node->left;
    cout << node->data << endl;
}

void find_max (BTree *node) {
    while (node->right != nullptr)
        node = node->right;
    cout << node->data << endl;
}

//------------------------------------------------------
//обход в ширину BFS (разобраться)

Queue* create_queue(int capacity) {
    Queue* queue = new Queue();
    queue->arr = new BTree*[capacity];
    queue->start = 0;
    queue->end = -1;
    queue->capacity = capacity;
    return queue;
}

bool is_queue_empty(Queue* queue) {
    return queue->start > queue->end;
}

void enable_queue(Queue* queue, BTree* node) {
    if (queue->end == queue->capacity - 1) {
        cout << "Queue overflow!" << endl;
        return;
    }
    queue->arr[++queue->end] = node;
}

BTree* delete_queue(Queue* queue) {
    if (is_queue_empty(queue)) {
        cout << "Queue underflow!" << endl;
        return nullptr;
    }
    return queue->arr[queue->start++];
}

int count_nodes(BTree* root) {
    if (root == nullptr)
        return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

void btree_wideorder(BTree* root) {
    if (root == nullptr) {
        cout << "Tree is empty!" << endl;
        return;
    }
    int capacity = count_nodes(root);
    Queue* queue = create_queue(capacity);
    enable_queue(queue, root);
    while (!is_queue_empty(queue)) {
        BTree* current = delete_queue(queue);
        cout << current->data << " ";
        if (current->left != nullptr)
            enable_queue(queue, current->left);
        if (current->right != nullptr)
            enable_queue(queue, current->right);
    }
    cout << endl;
    delete[] queue->arr;
    delete queue;
}
//------------------------------------------------------

BTree *btree_delete (BTree *node, int data) {
    if (node == nullptr)
        return node;
    if (node->data > data)
        node->left = btree_delete(node->left, data);
    else if (node->data < data)
        node->right = btree_delete(node->right, data);
    else {
        if (node->left == nullptr) {
            BTree *temp = node->right;
            delete node;
            return temp;
        }
        if (node->right == nullptr) {
            BTree *temp = node->left;
            delete node;
            return temp;
        }
        BTree *temp = node->right;
        while (temp != nullptr && temp->left != nullptr)
            temp = temp->left;
        node->data = temp->data;
        node->right = btree_delete(node->right, temp->data);
    }
    return node;
}

void btree_destroy(BTree* node) {
    if (node == nullptr) return;
    btree_destroy(node->left);
    btree_destroy(node->right);
    delete node;
}







// Рекурсивная функция для записи узлов и связей в DOT-файл
void writeNodes(BTree* current, int parentID, ofstream& dotFile) {
    if (current == nullptr) return;

    int currentID = current->data; // Используем значение узла как его ID

    // Записываем текущий узел
    dotFile << "    " << currentID << " [label=\"" << currentID << "\"];\n";

    // Если есть родительский узел, записываем связь
    if (parentID != -1) {
        dotFile << "    " << parentID << " -> " << currentID << ";\n";
    }

    // Рекурсивно записываем потомков
    writeNodes(current->left, currentID, dotFile);
    writeNodes(current->right, currentID, dotFile);
}

// Функция для генерации графа дерева и преобразования его в PNG
void print_tree_graph(BTree* node, char* filename) {
    // Открываем файл для записи
    ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи." << endl;
        return;
    }

    // Записываем заголовок DOT-файла
    dotFile << "digraph Tree {\n";
    dotFile << "    node [shape=circle, fontname=Arial, fontsize=12];\n";

    // Начинаем запись с корня
    writeNodes(node, -1, dotFile);

    // Закрываем DOT-файл
    dotFile << "}\n";
    dotFile.close();

    cout << "DOT-файл успешно создан: " << filename << endl;

    // Преобразуем DOT-файл в PNG
    string outputImage = string(filename) + ".png"; // Добавляем расширение .png
    string command = "dot -Tpng " + string(filename) + " -o " + outputImage;
    if (system(command.c_str()) == 0) {
        cout << "Изображение успешно создано: " << outputImage << endl;
    } else {
        cerr << "Ошибка: не удалось создать изображение. Убедитесь, что Graphviz установлен." << endl;
    }
}
