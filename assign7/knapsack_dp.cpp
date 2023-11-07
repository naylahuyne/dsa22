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

void dpKnapsack(Item items[], int capacity, int n) {
    int dp[capacity + 1][n + 1];
    for (int i = 0; i <= capacity; i++) {
        dp[i][0] = 0;
    }
    for (int i = 0; i <= n; i++) {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= capacity; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i][j - 1];
            if (items[j - 1].weight <= i) {
                dp[i][j] = max(dp[i][j],
                               dp[i - items[j - 1].weight][j - 1] + items[j - 1].value);
            }
        }
    }
    cout << "Total value stole: " << dp[capacity][n];
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
    dpKnapsack(items, capacity, n);
    return 0;
}
