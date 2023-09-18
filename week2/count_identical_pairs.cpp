// TASK 1
#include <iostream>

using namespace std;

struct Node {
    Node* next;
    int data;
};

void insertBack(Node** head, int data) {
    if (!(*head)) {
        *head = new Node;
        (*head)->data = data;
        (*head)->next = nullptr;
        return;
    }
    insertBack(&((*head)->next), data);
}

/**
 * Get the number of pairs(i, j) such that data of node at pos i = data of node at pos j,
 * i != j, pos of head = 0
 * @param arr the given list of numbers
 * @param listSize the size of the list
 * @return the number of pairs sastisfied
*/
int countIdenticalPairs(Node* head) {
    int counter = 0;
    Node* i = head;
    while (i) {
        Node* j = i->next;
        while (j) {
            if (i->data == j->data) {
                counter++;
            }
            j = j->next;
        }
        i = i->next;
    }
    return counter;
}

int main() {
    int n;
    cin >> n;
    Node* head = nullptr;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        insertBack(&head, x);
    }

    cout << countIdenticalPairs(head);
    return 0;
}
