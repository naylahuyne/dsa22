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

void maxHeapify(vector<int> &arr, int heapSize, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (arr[left] > arr[largest] && left < heapSize) {
        largest = left;
    }
    if (arr[right] > arr[largest] && right < heapSize) {
        largest = right;
    }
    if (largest != i) {
        int tmp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = tmp;
        maxHeapify(arr, heapSize, largest);
    }
}

void buildHeap(vector<int> &arr) {
    int n = arr.size();
    for (int i = n / 2; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

void heapSort(vector<int> &arr) {
    buildHeap(arr);
    int heapSize = arr.size();
    for (int i = arr.size() - 1; i >= 0; i--) {
        int tmp = arr[heapSize - 1];
        arr[heapSize - 1] = arr[0];
        arr[0] = tmp;
        heapSize--;
        maxHeapify(arr, heapSize, 0);
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
    heapSort(arr);
    cout << "Sorted array:\n";
    printArr(arr);
    return 0;
}



