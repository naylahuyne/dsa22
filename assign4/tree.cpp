#include <iostream>
#include <stack>
#include <queue>
#include <cstdint>
using namespace std;

// Một Node trong cây
class Node {
    // Chứa thông tin của Node đó
    int data;
    // Con trỏ đến Node cha
    Node* fatherNode;

    // Con trỏ đến các Node con
    // Đây là một danh sách liên kết (con trỏ đến con đầu tiên)
    // Thứ tự ưu tiên từ nhỏ đến lớn (con nhỏ được duyệt trước)
    Node* firstChild;
    Node* nextSibling;

public:
    Node() {
        this->data = 0;
        this->fatherNode = nullptr;
    }
    // Các hàm khởi tạo khác nếu cần thiết
    Node(int data, Node *fatherNode) {
        this->data = data;
        this->fatherNode = fatherNode;
        this->firstChild = nullptr;
        this->nextSibling = nullptr;
    }

    friend class Tree;
};

// Lớp Cây
class Tree {
    // Chứa một Node gốc
    Node* root;
public:
    Tree() {
        this->root = nullptr;
    }
    // Các hàm khởi tạo khác nếu cần thiết
    Tree(int data) {
        root = new Node(data, nullptr);
    }

    Tree(Node* root) {
        this->root = root;
    }

    // Hàm thêm một Node vào cây
    // Hàm trả về false nếu Node cha không tồn tại trên cây
    // hoặc Node father đã có con là data
    bool insert(int father, int data);

    // Hàm xoá một Node trên cây
    // Nếu không phải Node lá xoá Node đó và toàn bộ các Node con của nó
    // Hàm trả về số lượng Node đã xoá
    // Nếu Node data không tồn tại trả về 0 (zero)
    int remove(int data);

    // Hàm in ra các Node theo thứ tự preorder
    void preorder();

    // Hàm in ra các Node theo thứ tự postorder
    void postorder();

    // Hàm kiểm tra cây nhị phân
    bool isBinaryTree();

    // Hàm kiểm tra cây tìm kiếm nhị phân
    bool isBinarySearchTree();

    // Hàm kiểm tra cây max-heap
    bool isMaxHeapTree();

    // Hàm in ra các Node theo thứ tự inorder nếu là cây nhị phân
    void inorder();

    // Hàm trả về độ cao của cây
    int height();

    // Hàm trả về độ sâu của một Node
    int depth(int data);

    // Hàm đếm số lượng lá
    int numOfLeaves();

    // Hàm trả về Node có giá trị lớn nhất
    int findMax();

    // Hàm trả về Node có nhiều con nhất
    int findMaxChild();

    int findMin();
};

bool Tree::insert(int father, int data) {
    if (!root) return false;
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node *node = nullptr;
        if (st.top()->data == father) {
            node = st.top()->firstChild;
            if (!node) {
                // Nếu node father chưa có con nào
                st.top()->firstChild = new Node(data, st.top());
                return true;
            }
            // Nếu con đầu là node data
            if (node->data == data) return false;
            while (node->nextSibling) {
                // Nếu các con khác có node data
                if (node->nextSibling->data == data) return false;
                node = node->nextSibling;
            }
            // Nếu chưa có con là node data
            node->nextSibling = new Node(data, st.top());
            return true;
        }
        else {
            node = st.top()->firstChild;
            st.pop();
            // Thêm các con của node vừa duyệt vào stack
            while (node) {
                st.push(node);
                node = node->nextSibling;
            }
        }
    }
    // Nếu duyệt hết mà chưa gặp node father
    return false;
}

int Tree::remove(int data) {
    if (!root) return 0;
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        if (st.top()->data == data) {
            if (st.top()->data == root->data) root = nullptr;
            else if (st.top()->fatherNode->firstChild->data != st.top()->data) {
                Node* node = st.top()->fatherNode->firstChild;
                while(node->nextSibling->data != st.top()->data) {
                    node = node->nextSibling;
                }
                node->nextSibling = node->nextSibling->nextSibling;
            }
            else {
                st.top()->fatherNode->firstChild = st.top()->nextSibling;
            }
            int counter = 0;
            stack<Node*> iter;
            stack<Node*> destruct;
            iter.push(st.top());
            while (!iter.empty()) {
                destruct.push(iter.top());
                Node* node = iter.top()->firstChild;
                iter.pop();
                while (node) {
                    iter.push(node);
                    node = node->nextSibling;
                }
            }
            while (!destruct.empty()) {
                Node* node = destruct.top();
                destruct.pop();
                if (node->nextSibling) node->nextSibling = nullptr;
                if (node->firstChild) node->firstChild = nullptr;
                delete node;
                counter++;
            }
            return counter;
        }
        else {
            Node *node = st.top()->firstChild;
            st.pop();
            // Thêm các con của node vừa duyệt vào stack
            while (node) {
                st.push(node);
                node = node->nextSibling;
            }
        }
    }
    // Nếu duyệt hết mà không gặp node data
    return 0;
}

void Tree::preorder() {
    if (!root) {
        cout << "Empty tree! Preorder Traversal." << endl;
        return;
    }
    cout << root->data << " ";
    Node* node = root->firstChild;
    while (node) {
        Tree subtree(node);
        subtree.preorder();
        node = node->nextSibling;
    }
}

void Tree::postorder() {
    if (!root) {
        cout << "Empty tree! Postorder Traversal." << endl;
        return;
    }
    Node* node = root->firstChild;
    while (node) {
        Tree subtree(node);
        subtree.postorder();
        node = node->nextSibling;
    }
    cout << root->data << " ";
}

void Tree::inorder() {
    if (!root) {
        cout << "Empty tree! Inorder Traversal." << endl;
        return;
    }
    Node* node = root->firstChild;
    if (node) Tree(node).inorder();
    cout << root->data << " ";
    if (node && node->nextSibling) Tree(node->nextSibling).inorder();
}

bool Tree::isBinaryTree() {
    if (!root) return true;
    Node* node = root->firstChild;
    // Nếu có ít nhất 3 con
    if (node && node->nextSibling && node->nextSibling->nextSibling)
        return false;
    while (node) {
        Tree subtree(node);
        if (!subtree.isBinaryTree()) return false;
        node = node->nextSibling;
    }
    return true;
}

int Tree::findMin() {
    if (!root) return INT32_MAX;
    if (!root->firstChild) return root->data;
    Node *node = root->firstChild;
    int minElement = root->data;
    while (node) {
        int subMin = Tree(node).findMin();
        if (subMin < minElement) minElement = subMin;
        node = node->nextSibling;
    }
    return minElement;
}

int Tree::findMax() {
    if (!root) return INT32_MIN;
    if (!root->firstChild) return root->data;
    Node *node = root->firstChild;
    int maxElement = root->data;
    while (node) {
        int subMax = Tree(node).findMax();
        if (subMax > maxElement) maxElement = subMax;
        node = node->nextSibling;
    }
    return maxElement;
}

bool Tree::isBinarySearchTree() {
    if (!root) return true;
    Node* node = root->firstChild;
    // Nếu có ít nhất 3 con
    if (node && node->nextSibling && node->nextSibling->nextSibling)
        return false;
    if (node) {
        if (Tree(node).findMax() > root->data) return false;
        if (node->nextSibling) {
            if (Tree(node->nextSibling).findMin() < root->data) return false;
            if (!Tree(node).isBinarySearchTree() 
                || !Tree(node->nextSibling).isBinarySearchTree())
                 return false;
        }
    }
    return true;
}

bool Tree::isMaxHeapTree() {
    if (!root) return true;
    Node* node = root->firstChild;
    // Nếu có ít nhất 3 con
    if (node && node->nextSibling && node->nextSibling->nextSibling)
        return false;
    if (node) {
        if ((!node->nextSibling) && node->firstChild) return false;
        if (node->data > root->data) return false;
        if (node->nextSibling) {
            if (node->nextSibling->data > root->data) return false;
            if (!Tree(node).isMaxHeapTree()) return false;
            if (!Tree(node->nextSibling).isMaxHeapTree()) return false;
        }
    }
    return true;
}

int Tree::height() {
    if (!root) return 0;
    if (!root->firstChild) return 0;
    Node* node = root->firstChild;
    int height = 0;
    while (node) {
        int subHeight = Tree(node).height();
        if (subHeight > height) height = subHeight;
        node = node->nextSibling;
    }
    return height + 1;
}

int Tree::depth(int data) {
    if (!root) return INT32_MIN;
    if (root->data == data) return 0;
    Node* node = root->firstChild;
    while (node) {
        int depth = Tree(node).depth(data);
        if (depth >= 0) return depth + 1;
        node = node->nextSibling;
    }
    // Không tồn tại node
    return -1;
}

int Tree::numOfLeaves() {
    if (!root) return 0;
    if (!root->firstChild) return 1;
    int leavesCounter = 0;
    Node *node = root->firstChild;
    while (node) {
        leavesCounter += Tree(node).numOfLeaves();
        node = node->nextSibling;
    }
    return leavesCounter;
}

int Tree::findMaxChild() {
    if (!root) return INT32_MIN;
    stack<Node*> st;
    st.push(root);
    int maxChild = 0;
    int parent = root->data;
    while (!st.empty()) {
        Node *node = st.top()->firstChild;
        int tempParent = st.top()->data;
        st.pop();
        int childCounter = 0;
        while (node) {
            childCounter++;
            st.push(node);
            node = node->nextSibling;
        }
        if (childCounter > maxChild) {
            maxChild = childCounter;
            parent = tempParent;
        }
    }
    return parent;
}

void sampleTree(Tree &tree);

void sampleBst(Tree &tree);

void sampleMaxHeapTree(Tree &tree);

int main(int argc, char const *argv[]) {
    Tree tree;

    //sampleTree(tree);
    sampleBst(tree);
    //sampleMaxHeapTree(tree);
    
    cout << "Preorder Traversal: ";
    tree.preorder();
    cout << endl;
    cout << "Postorder Traversal: ";
    tree.postorder();
    cout << endl;
    cout << "Inorder Traversal: ";
    if (tree.isBinaryTree()) tree.inorder();
    else cout << "Not a binary tree!";
    cout << endl;

    cout << "Height: " << tree.height() << endl;
    cout << "Max element in the tree: " << tree.findMax() << endl;
    int toFind = 4;
    cout << "Depth of " << toFind << ": " << tree.depth(toFind) << endl;
    cout << "Number of leaves: " << tree.numOfLeaves() << endl;
    cout << "Node that has most children: " << tree.findMaxChild() << endl;

    cout << "Binary tree: " << boolalpha << tree.isBinaryTree() << endl;
    cout << "BST: " << boolalpha << tree.isBinarySearchTree() << endl;
    cout << "Max heap tree: " << boolalpha << tree.isMaxHeapTree() << endl;
    return 0;
}

void sampleTree(Tree &tree) {
    tree = Tree(15);
    tree.insert(15, 7);
    tree.insert(15, 27);
    tree.insert(15, 28);
    tree.insert(7, 8);
    tree.insert(7, 9);
    tree.insert(7, 10);
    tree.insert(7, 11);
    tree.insert(8, 1);
    tree.insert(9, 2);
    tree.insert(9, 3);
    tree.insert(9, 4);
    tree.insert(9, 5);
    tree.insert(5, 6);
    tree.insert(6, 12);
    tree.insert(6, 13);
    tree.insert(13, 14);
    tree.insert(12, 24);
    tree.insert(12, 25);
    tree.insert(27, 16);
    tree.insert(27, 17);
    tree.insert(27, 18);
    tree.insert(17, 19);
    tree.insert(17, 20);
    tree.insert(19, 21);
    tree.insert(19, 22);
    tree.insert(19, 23);
    tree.insert(19, 26);
    tree.insert(19, 29);
    tree.insert(19, 30);
    cout << "Number of nodes removed: " << tree.remove(27) << endl;
}

void sampleBst(Tree &tree) {
    tree = Tree(46);
    tree.insert(46, 15);
    tree.insert(15, 9);
    tree.insert(9, 4);
    tree.insert(4, 3);
    tree.insert(9, 13);
    tree.insert(13, 10);
    tree.insert(13, 14);
    tree.insert(15, 33);
    tree.insert(33, 27);
    tree.insert(27, 18);
    tree.insert(27, 31);
    tree.insert(33, 41);
    tree.insert(41, 39);
    tree.insert(41, 43);
    tree.insert(46, 74);
    tree.insert(74, 57);
    tree.insert(57, 52);
    tree.insert(52, 51);
    tree.insert(52, 55);
    tree.insert(57, 63);
    tree.insert(63, 61);
    tree.insert(63, 71);
    tree.insert(74, 93);
    tree.insert(93, 84);
    tree.insert(84, 76);
    tree.insert(84, 87);
    tree.insert(93, 98);
    tree.insert(98, 97);
    tree.insert(98, 99);
}

void sampleMaxHeapTree(Tree &tree) {
    tree = Tree(94);
    tree.insert(94, 92);
    tree.insert(92, 80);
    tree.insert(80, 72);
    tree.insert(72, 13);
    tree.insert(72, 31);
    tree.insert(80, 26);
    tree.insert(26, 10);
    tree.insert(26, 18);
    tree.insert(92, 87);
    tree.insert(87, 36);
    tree.insert(36, 24);
    tree.insert(36, 31);
    tree.insert(87, 69);
    tree.insert(69, 12);
    tree.insert(69, 57);
    tree.insert(94, 87);
    tree.insert(87, 82);
    tree.insert(82, 77);
    tree.insert(77, 36);
    tree.insert(77, 58);
    tree.insert(82, 73);
    tree.insert(73, 68);
    tree.insert(73, 57);
    tree.insert(87, 85);
    tree.insert(85, 72);
    tree.insert(72, 35);
    tree.insert(72, 63);
    tree.insert(85, 54);
    tree.insert(54, 4);
}
