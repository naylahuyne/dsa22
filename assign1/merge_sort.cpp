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

vector<int> merge(const vector<int> &first, const vector<int> &second) {
    vector<int> mergedArr;
    int n1 = first.size();
    int n2 = second.size();
    int idx1(0), idx2(0);
    for (int i = 0; i < n1 + n2; i++) {
        if (idx1 < n1 && idx2 < n2) {
            if (first[idx1] < second[idx2])
                mergedArr.push_back(first[idx1++]);
            else
                mergedArr.push_back(second[idx2++]);
        }
        else if (idx1 < n1)
            mergedArr.push_back(first[idx1++]);
        else
            mergedArr.push_back(second[idx2++]);
    }
    return mergedArr;
}

void mergeSort(vector<int> &arr) {
    if (arr.size() <= 1) return;
    int mid = arr.size() / 2;
    vector<int> first(arr.begin(), arr.begin() + mid);
    vector<int> second(arr.begin() + mid, arr.end());
    mergeSort(first);
    mergeSort(second);
    arr = merge(first, second);
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
    mergeSort(arr);
    cout << "Sorted array:\n";
    printArr(arr);
    return 0;
}



