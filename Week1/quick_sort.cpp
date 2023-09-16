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

void quickSort(vector<int> &arr, int idxPivot) {
    if (arr.size() <= 1) return;
    int n = arr.size();
    vector<int> first;
    vector<int> second;
    for (int i = 0; i < n; i++) {
        if (arr[i] < arr[idxPivot])
            first.push_back(arr[i]);
        else if (i != idxPivot)
            second.push_back(arr[i]);
    }
    quickSort(first, first.size() - 1);
    quickSort(second, second.size() - 1);
    arr = first;
    arr.push_back(arr[idxPivot]);
    arr.insert(arr.end(), second.begin(), second.end());
}

void quickSort(vector<int> &arr) {
    quickSort(arr, arr.size() - 1);
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
    quickSort(arr);
    cout << "Sorted array:\n";
    printArr(arr);
    return 0;
}


