#include <iostream>

using namespace std;

int findLcsLength(int a[], int b[], int m, int n) {
    // dp[i][j] store length of longest common subsequence
    // of first i elements in a and first j elements in b
    int dp[m + 1][n + 1];
    for (int i = 0; i <= n; i++) {
        dp[0][i] = 0;
    }
    for (int i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }
    return dp[m][n];
}

int main() {
    int m, n;
    cout << "Enter number of elements of array a, b:\n";
    cin >> m >> n;
    int a[m], b[n];
    cout << "Enter array a:\n";
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    cout << "Enter array b:\n";
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    cout << "Length of longest common subsequence: "
         << findLcsLength(a, b, m, n);
    return 0;
}
