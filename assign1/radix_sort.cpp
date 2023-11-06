#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void printArr(const vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int countDigits(int n) {
    int res(1);
    while (n / 10 > 0) {
        n /= 10;
        res++;
    }
    return res;
}

// digitPlace: 0 for ones, 1 for tens, 2 for hundreds, ...
void countingSort(vector<int> &arr, int digitPlace) {
    vector<vector<int>> countArr(10);
    int n = arr.size();
    int powTen = pow(10, digitPlace);
    for (int i = 0; i < n; i++) {
        int digit = arr[i] / powTen;
        digit %= 10;
        countArr[digit].push_back(arr[i]);
    }
    arr.clear();
    for (int i = 0; i < 10; i++) {
        int l = countArr[i].size();
        for (int j = 0; j < l; j++) {
            arr.push_back(countArr[i][j]);
        }
    }
}

void radixSort(vector<int> &arr) {
        int maxElement = *max_element(arr.begin(), arr.end());
        int numDigits = countDigits(maxElement);
        for (int i = 0; i < numDigits; i++) {
            countingSort(arr, i);
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
    radixSort(arr);
    cout << "Sorted array:\n";
    printArr(arr);
    return 0;
}


