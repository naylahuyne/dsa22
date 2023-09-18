// TASK 2
#include <iostream>

using namespace std;

struct Node {
    Node* next;
    int data;
};

struct LinkedList
{
    private:
        Node* head;
    public:
        LinkedList() {
            head = nullptr;
        }
        void insertElement(int pos, int x) {
            Node* node = head;
            while (pos > 1) {
                if (!node) {
                    cout << "Exceed list's length. Can't insert." << endl;
                    return;
                }
                node = node->next;
                pos--;
            }
            if (!node) {
                if (pos == 0) {
                    node = new Node;
                    node->next = nullptr;
                    node->data = x;
                    head = node;
                }
                else {
                    cout << "Exceed list's length. Can't insert." << endl;
                    return;
                }
            }
            else {
                if (!(node->next)) {
                    node->next = new Node;
                    node = node->next;
                    node->next = nullptr;
                    node->data = x;
                }
                else {
                    Node* newNode = new Node;
                    newNode->next = node->next;
                    newNode->data = x;
                    node->next = newNode;
                }
            }
        }

        void deleteElement(int pos) {
            Node* node = head;
            while (pos > 1) {
                if (!node) return;
                node = node->next;
                pos--;
            }
            if (!node || !(node->next)) return;
            else {
                Node* tmp = (node->next)->next;
                delete node->next;
                node->next = tmp;
            }
        }

        void print() {
            Node* node = head;
            while (node) {
                cout << node->data << " ";
                node = node->next;
            }
        }
};

/**
 * @param listOperator accept "insert" and "delete" as value
 * @param list the list in which the operation carries out
*/
void runQuery(string listOperator, LinkedList &list) {
    if (listOperator == "insert") {
        int pos, x;
        cin >> pos >> x;
        list.insertElement(pos, x);
    }
    else if (listOperator == "delete") {
        int pos;
        cin >> pos;
        list.deleteElement(pos);
    }
    else {
        cout << "Undefined operator." << endl;
    }
}

int main() {
    LinkedList list;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string listOperator;
        cin >> listOperator;
        runQuery(listOperator, list);
    }
    list.print();
    return 0;
}
