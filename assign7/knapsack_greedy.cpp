/**
 * Thứ tự nhập dữ liệu.
 * Dòng đầu tiên, W - trọng tải tối đa của balo, n - số vật phẩm.
 * n dòng tiếp theo, weight - trọng lượng vật phẩm, value - giá trị vật phẩm.
*/

#include <iostream>

using namespace std;

struct Item {
    int weight;
    int value;
};

void merge(Item items[], int left, int mid, int right) {
    Item first[mid - left + 1];
    Item second[right - mid];
    for (int i = 0; i < mid - left + 1; i++) {
        first[i] = items[left + i];
    }
    for (int i = 0; i < right - mid; i++) {
        second[i] = items[mid + 1 + i];
    }
    int firstIndex = 0, secondIndex = 0;
    for (int i = 0; i < right - left + 1; i++) {
        if (firstIndex + left <= mid && secondIndex + mid + 1 <= right) {
            if (1.0 * first[firstIndex].value / first[firstIndex].weight
                    >= 1.0 * second[secondIndex].value / second[secondIndex].weight) {
                items[left + i] = first[firstIndex++];
            }
            else {
                items[left + i] = second[secondIndex++];
            }
        }
        else if (secondIndex + mid + 1 > right) {
            items[left + i] = first[firstIndex++];
        }
        else {
            items[left + i] = second[secondIndex++];
        }
    }
}

void mergeSort(Item items[], int left, int right) {
    if (left == right) return;
    int mid = (left + right) / 2;
    mergeSort(items, left, mid);
    mergeSort(items, mid + 1, right);
    merge(items, left, mid, right);
}

/*void print(Item items[], int n) {
    for (int i = 0; i < n; i++) {
        cout << items[i].weight << " " << items[i].value << endl;
    }
}*/

void greedyKnapsack(Item items[], int capacity, int n) {
    int totalWeight = 0;
    int totalValue = 0;
    for (int i = 0; i < n; i++) {
        if (totalWeight + items[i].weight <= capacity) {
            totalWeight += items[i].weight;
            totalValue += items[i].value;
        }
    }
    cout << "Total weight stole: " << totalWeight << endl;
    cout << "Total value stole: " << totalValue;
}

int main() {
    int capacity, n;
    cout << "Enter capacity of knapsack, number of artifacts (respectively):\n";
    cin >> capacity >> n;
    Item items[n];
    cout << "Enter each artifact's weight and value (respectively):\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight;
        cin >> items[i].value;
    }
    // Descending
    mergeSort(items, 0, n - 1);
    greedyKnapsack(items, capacity, n);
    return 0;
}
