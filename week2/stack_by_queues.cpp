#include <iostream>
#include <queue>

using namespace std;

template<typename T>
struct MyStack {
    private:
        queue<T> firstQueue;
        queue<T> secondQueue;
        static const int FIRST_STATE = 0;
        static const int SECOND_STATE = 1;
        int latestState;
    public:
        MyStack() {
            latestState = FIRST_STATE;
        }

        bool empty() {
            return (firstQueue.empty() && secondQueue.empty());
        }

        void push(T x) {
            if (latestState == FIRST_STATE) {
                firstQueue.push(x);
            }
            else {
                secondQueue.push(x);
            }
        }

        void pop() {
            if (latestState == FIRST_STATE) {
                while (true) {
                    T tmp = firstQueue.front();
                    firstQueue.pop();
                    if (firstQueue.empty()) {
                        break;
                    }
                    secondQueue.push(tmp);
                }
                latestState = SECOND_STATE;
            }
            else {
                while (true) {
                    T tmp = secondQueue.front();
                    secondQueue.pop();
                    if (secondQueue.empty()) {
                        break;
                    }
                    firstQueue.push(tmp);
                }
                latestState = FIRST_STATE;
            }
        }

        T top() {
            T res;
            if (latestState == FIRST_STATE) {
                while (!firstQueue.empty()) {
                    T tmp = firstQueue.front();
                    firstQueue.pop();
                    if (firstQueue.empty()) {
                        res = tmp;
                    }
                    secondQueue.push(tmp);
                }
                latestState = SECOND_STATE;
            }
            else {
                while (!secondQueue.empty()) {
                    T tmp = secondQueue.front();
                    secondQueue.pop();
                    if (secondQueue.empty()) {
                        res = tmp;
                    }
                    firstQueue.push(tmp);
                }
                latestState = FIRST_STATE;
            }
            return res;
        }
};

template<typename T>
void printStack(MyStack<T> st) {
    MyStack<T> printSt = MyStack<T>();
    while (!st.empty()) {
        printSt.push(st.top());
        st.pop();
    }
    while (!printSt.empty()) {
        cout << printSt.top() << " ";
        printSt.pop();
    }
    cout << endl;
}

int main() {
    MyStack<char> st = MyStack<char>();
    st.push('a');
    st.push('b');
    st.push('c');
    st.pop();
    printStack(st);
    return 0;
}

