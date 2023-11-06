#include <iostream>
#include <vector>

using namespace std;

void printArr(const vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void selectionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        int idxMin = i;
        for (int j = i; j < n; j++) {
            if (arr[j] < arr[idxMin])
                idxMin = j;
        }
        int tmp = arr[idxMin];
        arr[idxMin] = arr[i];
        arr[i] = tmp;
    }
}

int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    selectionSort(arr);
    cout << "Sorted array:\n";
    printArr(arr);
    return 0;
}

