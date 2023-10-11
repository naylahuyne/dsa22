/**
 * Find shortest path
 * Implement by using BFS.
*/
#include <iostream>
#include <cstdint> // for INT32_MAX only

using namespace std;

struct Node {
    Node *next;
    int label;
    Node (int label) {
        next = nullptr;
        this->label = label;
    }
};

struct SinglyLinkedList {
    Node *head;

    SinglyLinkedList() {
        head = nullptr;
    }

    void insertBack(int label) {
        if (!head) {
            head = new Node(label);
            return;
        }
        Node *node = head;
        while (node->next) {
            node = node->next;
        }
        node->next = new Node(label);
    }

    bool find(int label) {
        if (!head) return false;
        Node *node = head;
        while (node) {
            if (node->label == label) {
                return true;
            }
        }
        return false;
    }

    void erase(int label) {
        if (!head) return;
        Node *node = head;
        if (head->label == label) {
            head = head->next;
            delete node;
            return;
        }
        while (node->next) {
            if (node->next->label == label) {
                Node* store = node->next;
                node->next = node->next->next;
                delete store;
                return;
            }
            node = node->next;
        }
    }

    void print() {
        Node *node = head;
        while (node) {
            cout << node->label << " ";
            node = node->next;
        }
    }
};

int findShortestPath(int x, int y, SinglyLinkedList *list, bool *visited, int n) {
    if (x == y) return 0;
    int shortestPath = INT32_MAX;
    Node *node = list[x - 1].head;
    visited[x - 1] = true;
    if (!node || visited[node->label - 1]) return INT32_MAX;
    while (node) {
        int tmp = findShortestPath(node->label, y, list, visited, n);
        if (tmp < shortestPath) {
            shortestPath = tmp + 1;
        }
        node = node->next;
    }
    return shortestPath;
}

int main() {
    int n, m, X, Y;
    cin >> n >> m >> X >> Y;

    SinglyLinkedList list[n];
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        list[x - 1].insertBack(y);
    }

    bool visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    cout << findShortestPath(X, Y, list, visited, n);
    return 0;
}