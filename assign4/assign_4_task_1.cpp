#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int label;
    vector<Node*> children;

    Node(int label) {
        this->label = label;
        children = vector<Node*>();
    }
};

Node* findNode(Node *root, int label) {
    if (root == nullptr) return nullptr;
    if (root->label == label) return root;
    int n = root->children.size();
    if (n == 0) return nullptr;
    for (int i = 0; i < n; i++) {
        Node *res = findNode(root->children[i], label);
        if (res) return res;
    }
    return nullptr;
}

int getHeight(Node *root) {
    if (!root) return 0;
    int n = root->children.size();
    if (n == 0) return 0;
    int maxSubtreeHeight = 0;
    for (int i = 0; i < n; i++) {
        int subtreeHeight = getHeight(root->children[i]);
        if (subtreeHeight > maxSubtreeHeight) {
            maxSubtreeHeight = subtreeHeight;
        }
    }
    return 1 + maxSubtreeHeight;
}

bool isBinaryTree(Node* root) {
    if (!root) return true;
    int n = root->children.size();
    if (n > 2) return false;
    for (int i = 0; i < n; i++) {
        if (!isBinaryTree(root->children[i])) return false;
    }
    return true;
}

void preorderTraversal(Node* root) {
    if (!root) return;
    int n = root->children.size();
    cout << root->label << " ";
    for (int i = 0; i < n; i++) {
        preorderTraversal(root->children[i]);
    }
}

void postorderTraversal(Node *root) {
    if (!root) return;
    int n = root->children.size();
    for (int i = 0; i < n; i++) {
        postorderTraversal(root->children[i]);
    }
    cout << root->label << " ";
}

void inorderTraversal(Node *root) {
    if (!root) return;
    if (!isBinaryTree(root)) {
        cout << "NOT BINARY TREE";
        return;
    }
    int n = root->children.size();
    if (n > 0) inorderTraversal(root->children[0]);
    cout << root->label << " ";
    if (n == 2) inorderTraversal(root->children[1]);
}



void deleteTree(Node *root) {
    if (!root) return;
    int n = root->children.size();
    if (n == 0) delete root;
    for (int i = 0; i < n; i++) {
        deleteTree(root->children[i]);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    if (m != n - 1 && n != 0) {
        cout << "NOT A TREE!";
        exit(0);
    }
    Node* root = nullptr;
    if (m == 0 && n != 0) {
        int parent;
        cin >> parent;
        root = new Node(parent);
    }
    else {
        for (int i = 0; i < m; i++) {
            int parent, child;
            cin >> parent >> child;
            if (!root) {
                root = new Node(parent);
                root->children.push_back(new Node(child));
            }
            else {
                findNode(root, parent)->children.push_back(new Node(child));
            }
        }
    }
    cout << getHeight(root) << endl;
    preorderTraversal(root);
    cout << endl;
    postorderTraversal(root);
    cout << endl;
    inorderTraversal(root);
    cout << endl;
    deleteTree(root);
    return 0;
}

