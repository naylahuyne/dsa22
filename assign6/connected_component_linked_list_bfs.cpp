/**
 * Count connected components.
 * Implement by using BFS.
*/
#include <iostream>

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

int nextUnvisitedVertex(bool *visited, int n) {
    int i = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) return i + 1;
    }
    return n + 1;
}

int countConnectedComponents(SinglyLinkedList *list, int n) {
    bool visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    SinglyLinkedList wait;
    int countCntedCpns = 0;
    int nextUnvisited = nextUnvisitedVertex(visited, n);
    while (nextUnvisited != n + 1) {
        wait.insertBack(nextUnvisited);
        visited[nextUnvisited - 1] = true;
        while (wait.head) {
            Node* node = list[wait.head->label - 1].head;
            while (node) {
                if (!visited[node->label - 1]) {
                    wait.insertBack(node->label);
                    visited[node->label - 1] = true;
                }
                node = node->next;
            }
            wait.erase(wait.head->label);
        }
        countCntedCpns++;
        nextUnvisited = nextUnvisitedVertex(visited, n);
    }
    return countCntedCpns;
}

int main() {
    int n, m;
    cin >> n >> m;

    SinglyLinkedList list[n];
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        list[x - 1].insertBack(y);
        list[y - 1].insertBack(x);
    }

    cout << countConnectedComponents(list, n);

    return 0;
}