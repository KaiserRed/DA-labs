#include <cstdint>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>

const int MAX_KEY_LEN = 257;

struct node {
    char *key;
    int priority;
    uint64_t value;
    node *left, *right;

    node(const char *key, uint64_t value) {
        this->key = new char[MAX_KEY_LEN];
        std::strncpy(this->key, key, MAX_KEY_LEN);
        this->value = value;
        this->priority = rand();
        this->left = this->right = nullptr;
    }

    ~node() {
        delete[] key;
    }
};

void destroy(node *node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

void split(node *root, node *&left, node *&right, const char *key) {
    if (root == nullptr) {
        left = right = nullptr;
        return;
    }
    if (std::strcmp(root->key, key) <= 0) {
        left = root;
        split(root->right, left->right, right, key);
    } else {
        right = root;
        split(root->left, left, right->left, key);
    }
}

node *merge(node *left, node *right) {
    if (left == nullptr) { 
        return right;
    }
    if (right == nullptr) { 
        return left;
    }

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

void insert(node *&root, node *item) {
    if (root == nullptr) {
        root = item;
        return;
    }
    if (item->priority > root->priority) {
        split(root, item->left, item->right, item->key);
        root = item;
    } else {
        if (std::strcmp(item->key, root->key) < 0) {
            insert(root->left, item);
        } else {
            insert(root->right, item);
        }
    }
}

void remove(node *&root, const char *key) {
    if (root == nullptr) {
        return;
    }
    if (std::strcmp(root->key, key) == 0) {
        node *temp = merge(root->left, root->right);
        delete root;
        root = temp;
        return;
    }
    if (std::strcmp(root->key, key) > 0) {
        remove(root->left, key);
    } else {
        remove(root->right, key);
    }
}

node *search(node *root, const char *key) {
    if (root == nullptr) {
        return nullptr;
    } else if (std::strcmp(root->key, key) == 0) {
        return root;
    } else if (std::strcmp(root->key, key) > 0) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

void toLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = std::tolower(str[i]);
    }
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    node *root = nullptr;

    char command[MAX_KEY_LEN];
    char key[MAX_KEY_LEN];
    uint64_t value;

    while (input >> command) {
        if (std::strcmp(command, "+") == 0) {
            input >> key >> value;
            toLower(key);
            if (search(root, key)) {
                output << "Exist" << "\n";
            } else {
                insert(root, new node(key, value));
                output << "OK" << "\n";
            }
        } else if (std::strcmp(command, "-") == 0) {
            input >> key;
            toLower(key);
            if (search(root, key)) {
                remove(root, key);
                output << "OK" << "\n";
            } else {
                output << "NoSuchWord" << "\n";
            }
        } else {
            toLower(command);
            node *found_node = search(root, command);
            if (found_node) {
                output << "OK: " << found_node->value << "\n";
            } else {
                output << "NoSuchWord" << "\n";
            }
        }
    }

    destroy(root);
    input.close();
    output.close();
    return 0;
}