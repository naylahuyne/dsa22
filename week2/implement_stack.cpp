// TASK 5
#include <iostream>

using namespace std;

struct MyStack {
    private:
        static const int N_MAX = 100000;
        int elements[N_MAX];
        int totalElements;
    public:
        MyStack() {
            totalElements = 0;
        }

        void push(int x) {
            if (totalElements == N_MAX) {
                cout << "Max size of stack is " << N_MAX << ". " << "Can't push.\n";
                return;
            }
            elements[totalElements] = x;
            totalElements++;
        }

        void pop() {
            if (totalElements == 0) {
                cout << "Stack is empty. Can't pop";
                return;
            }
            totalElements--;
        }

        void print() {
            for (int i = 0; i < totalElements; i++) {
                cout << elements[i] << " ";
            }
            cout << endl;
        }
};

/**
 * @param stackOperator accept "push" and "pop" as value
 * @param st the stack in which the operation is performed
*/
void runQuery(string stackOperator, MyStack &st) {
    if (stackOperator == "push") {
        int x;
        cin >> x;
        st.push(x);
    }
    else if (stackOperator == "pop") {
        st.pop();
    }
    else {
        cout << "Undefined operator." << endl;
    }
}

int main() {
    MyStack st = MyStack();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string stackOperator;
        cin >> stackOperator;
        runQuery(stackOperator, st);
    }
    st.print();
    return 0;
}
