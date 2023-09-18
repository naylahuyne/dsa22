// TASK 4
#include <iostream>

using namespace std;

struct MyQueue {
    private:
        static const int N_MAX = 100000;
        int elements[N_MAX];
        int posFront;
        int posRear;
        int totalElements;
    public:
        MyQueue() {
            posFront = 0;
            posRear = 0;
            totalElements = 0;
        }

        void enqueue(int x) {
            if (totalElements == N_MAX) {
                cout << "Max size of queue is " << N_MAX << ". " << "Can't enqueue.\n";
                return;
            }
            if (totalElements == 0) {
                elements[posFront] = x;
                elements[posRear] = x;
                totalElements++;
            }
            else {
                posRear = (posRear + 1) % N_MAX;
                elements[posRear] = x;
                totalElements++;
            }
        }

        void dequeue() {
            if (totalElements == 0) {
                cout << "Queue is empty. Can't dequeue.\n";
            }
            else {
                posFront = (posFront + 1) % N_MAX;
                totalElements--;
                if (totalElements == 0)
                    posRear = posFront;
            }
        }

        void print() {
            if (posFront <= posRear) {
                for (int i = posFront; i <= posRear; i++) {
                    cout << elements[i] << " ";
                }
                cout << endl;
            }
            else {
                for (int i = posFront; i < N_MAX; i++) {
                    cout << elements[i] << " ";
                }
                for (int i = 0; i <= posRear; i++) {
                    cout << elements[i] << " ";
                }
                cout << endl;
            }
        }
};

/**
 * @param queueOperator accept "enqueue" and "dequeue" as value
 * @param q the queue in which the operation is performed
*/
void runQuery(string queueOperator, MyQueue &q) {
    if (queueOperator == "enqueue") {
        int x;
        cin >> x;
        q.enqueue(x);
    }
    else if (queueOperator == "dequeue") {
        q.dequeue();
    }
    else {
        cout << "Undefined operator." << endl;
    }
}

int main() {
    MyQueue q = MyQueue();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string queueOperator;
        cin >> queueOperator;
        runQuery(queueOperator, q);
    }
    q.print();
    return 0;
}
