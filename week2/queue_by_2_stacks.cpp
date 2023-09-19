#include <iostream>
#include <stack>

using namespace std;

template<typename T>
struct MyQueue {
    private:
        stack<T> enqueueStack;
        stack<T> dequeueStack;
        static const int ENQUEUE_STATE = 0;
        static const int DEQUEUE_STATE = 1;
        int latestState;

        void changeState() {
            if (latestState == ENQUEUE_STATE) {
                while (!enqueueStack.empty()) {
                    dequeueStack.push(enqueueStack.top());
                    enqueueStack.pop();
                }
                latestState = DEQUEUE_STATE;
            }
            else {
                while(!dequeueStack.empty()) {
                    enqueueStack.push(dequeueStack.top());
                    dequeueStack.pop();
                }
                latestState = ENQUEUE_STATE;
            }
        }
    public:
        MyQueue() {
            latestState = ENQUEUE_STATE;
        }

        bool empty() {
            return (enqueueStack.empty() && dequeueStack.empty());
        }

        void enqueue(T x) {
            if (latestState == ENQUEUE_STATE) {
                enqueueStack.push(x);
            }
            else {
                changeState();
                enqueueStack.push(x);
            }
        }

        void dequeue() {
            if (latestState == ENQUEUE_STATE) {
                changeState();
                dequeueStack.pop();
            }
            else {
                dequeueStack.pop();
            }
        }

        T front() {
            if (latestState == ENQUEUE_STATE) {
                changeState();
            }
            return dequeueStack.top();
        }
};

template<typename T>
void printQueue(MyQueue<T> q) {
    while(!q.empty()) {
        cout << q.front() << " ";
        q.dequeue();
    }
    cout << endl;
}

int main() {
    MyQueue<int> q = MyQueue<int>();
    q.enqueue('a');
    q.enqueue('b');
    q.enqueue('c');
    printQueue(q);
    q.dequeue();
    q.enqueue('d');
    printQueue(q);

    MyQueue<char> cQ = MyQueue<char>();
    cQ.enqueue('a');
    cQ.enqueue('b');
    cQ.enqueue('c');
    printQueue(cQ);
    cQ.dequeue();
    cQ.enqueue('d');
    printQueue(cQ);
    return 0;
}
