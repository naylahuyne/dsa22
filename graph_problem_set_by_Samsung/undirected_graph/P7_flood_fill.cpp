#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<vector<int>> grid;
vector<vector<bool>> mark;
int m, n;

void floodFill(int r, int c, int color, int oldColor) {
    // nằm ngoài grid
    if (r < 0 || r >= m || c < 0 || c >= n) {
        return;
    }
    // visited hoặc không cùng màu cũ
    if (mark[r][c] || grid[r][c] != oldColor) {
        return;
    }

    mark[r][c] = true;
    grid[r][c] = color;

    floodFill(r - 1, c, color, oldColor);
    floodFill(r + 1, c, color, oldColor);
    floodFill(r, c - 1, color, oldColor);
    floodFill(r, c + 1, color, oldColor);
}

void floodFill(int r, int c, int color) {
    floodFill(r, c, color, grid[r][c]);
}

int main() {
    // m hàng, n cột
    cin >> m >> n;
    // điểm ảnh gốc để flood fill các điểm kề và màu mới
    int r, c, color;
    cin >> r >> c >> color;
    grid.assign(m, vector<int> (n));
    mark.assign(m, vector<bool> (n, false));
    // nhập pixel grid
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    floodFill(r, c, color);
    cout << endl;
    cout << "New pixels grid:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
