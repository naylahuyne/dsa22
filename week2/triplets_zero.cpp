// TASK 3
#include <iostream>

using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int data;
};

void insert_back(Node** head, Node** tail, int data) {
    if (*head == nullptr) {
        *head = new Node;
        (*head)->next = nullptr;
        (*head)->prev = nullptr;
        (*head)->data = data;
        *tail = *head;
    }
    else if (*tail == *head) {
        *tail = new Node;
        (*tail)->next = nullptr;
        (*tail)->prev = *head;
        (*tail)->data = data;
        (*head)->next = *tail;
    }
    else {
        Node* tmp = *tail;
        (*tail)->next = new Node;
        ((*tail)->next)->prev = tmp;
        ((*tail)->next)->next = nullptr;
        ((*tail)->next)->data = data;
        *tail = (*tail)->next;
        tmp->next = *tail;
    }
}

/**
 * Count three consecutive nodes such that sum of those nodes' data equals to 0
 * @param head the head node of the list
 * @param tail the tail node of the list
 */
int count_triplets(Node* head, Node* tail) {
    int counter = 0;
    if (!head) return 0;
    if (!(head->next)) return 0;
    if (!((head->next)->next)) return 0;
    int sum = head->data + (head->next)->data + ((head->next)->next)->data;
    if (sum == 0)
        counter++;
    counter += count_triplets(head->next, tail);
    return counter;
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int data;
        cin >> data;
        insert_back(&head, &tail, data);
    }
    Node* node = head;
    cout << count_triplets(head, tail) << endl;
    return 0;
}

