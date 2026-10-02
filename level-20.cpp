#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    explicit Node(int number) : value(number), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    } else {
        cout << "重複值 " << value << "，不插入。\n";
    }
    return root;
}

Node* findNode(Node* root, int value) {
    if (root == nullptr || root->value == value) {
        return root;
    }
    return value < root->value
        ? findNode(root->left, value)
        : findNode(root->right, value);
}

Node* minimumNode(Node* root) {
    while (root != nullptr && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

Node* erase(Node* root, int value, bool& removed) {
    if (root == nullptr) {
        return nullptr;
    }
    if (value < root->value) {
        root->left = erase(root->left, value, removed);
    } else if (value > root->value) {
        root->right = erase(root->right, value, removed);
    } else {
        removed = true;
        if (root->left == nullptr) {
            Node* replacement = root->right;
            delete root;
            return replacement;
        }
        if (root->right == nullptr) {
            Node* replacement = root->left;
            delete root;
            return replacement;
        }

        Node* successor = minimumNode(root->right);
        root->value = successor->value;
        root->right = erase(root->right, successor->value, removed);
    }
    return root;
}

void preorder(const Node* root, vector<int>& output) {
    if (root == nullptr) return;
    output.push_back(root->value);
    preorder(root->left, output);
    preorder(root->right, output);
}

void inorder(const Node* root, vector<int>& output) {
    if (root == nullptr) return;
    inorder(root->left, output);
    output.push_back(root->value);
    inorder(root->right, output);
}

void postorder(const Node* root, vector<int>& output) {
    if (root == nullptr) return;
    postorder(root->left, output);
    postorder(root->right, output);
    output.push_back(root->value);
}

vector<int> levelorder(const Node* root) {
    vector<int> output;
    if (root == nullptr) return output;
    queue<const Node*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
        const Node* current = nodes.front();
        nodes.pop();
        output.push_back(current->value);
        if (current->left != nullptr) nodes.push(current->left);
        if (current->right != nullptr) nodes.push(current->right);
    }
    return output;
}

int height(const Node* root) {
    if (root == nullptr) return 0;
    return 1 + max(height(root->left), height(root->right));
}

void printValues(const vector<int>& values) {
    if (values.empty()) {
        cout << "（空）";
        return;
    }
    for (size_t index = 0; index < values.size(); ++index) {
        if (index != 0) cout << ' ';
        cout << values[index];
    }
}

void printTraversals(const Node* root) {
    vector<int> values;
    cout << "前序：";
    preorder(root, values);
    printValues(values);
    values.clear();
    cout << "\n中序：";
    inorder(root, values);
    printValues(values);
    values.clear();
    cout << "\n後序：";
    postorder(root, values);
    printValues(values);
    cout << "\n層序：";
    printValues(levelorder(root));
    cout << '\n';
}

void destroy(Node* root) {
    if (root == nullptr) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

bool readInteger(int& value, const string& prompt) {
    cout << prompt;
    if (cin >> value) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }
    cout << "請輸入有效整數。\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

int main() {
    Node* root = nullptr;
    int choice = -1;
    cout << "====================================\n"
         << "  第 20 關：二元搜尋樹種樹\n"
         << "  左子樹 < 節點 < 右子樹\n"
         << "====================================\n";

    while (choice != 0) {
        cout << "\n[1] 插入數字  [2] 搜尋數字  [3] 刪除數字\n"
             << "[4] 顯示四種走訪與樹高  [5] 種入範例樹  [0] 離開\n";
        if (!readInteger(choice, "請選擇功能：")) continue;

        int value = 0;
        switch (choice) {
        case 1:
            if (readInteger(value, "要插入的整數：")) {
                root = insert(root, value);
                cout << "插入操作完成。\n";
            }
            break;
        case 2:
            if (readInteger(value, "要搜尋的整數：")) {
                cout << (findNode(root, value) != nullptr
                    ? "找到 " : "找不到 ") << value << "。\n";
            }
            break;
        case 3:
            if (readInteger(value, "要刪除的整數：")) {
                bool removed = false;
                root = erase(root, value, removed);
                cout << (removed ? "已刪除 " : "找不到 ") << value << "。\n";
            }
            break;
        case 4:
            printTraversals(root);
            cout << "節點數：";
            {
                vector<int> values;
                inorder(root, values);
                cout << values.size() << "，樹高：" << height(root) << '\n';
            }
            break;
        case 5: {
            const int sample[] = {50, 30, 70, 20, 40, 60, 80};
            for (int item : sample) root = insert(root, item);
            cout << "已插入範例數列：50 30 70 20 40 60 80。\n";
            break;
        }
        case 0:
            cout << "已離開二元搜尋樹練習。\n";
            break;
        default:
            cout << "沒有這個功能，請選擇 0 到 5。\n";
        }
    }

    destroy(root);
    return 0;
}
