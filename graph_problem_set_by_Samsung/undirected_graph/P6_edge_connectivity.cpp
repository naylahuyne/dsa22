#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adjList;
vector<int> inTime, low;
int timer = 0;
bool bridgeFound;

void dfs(int u, int parent) {
    // thời điểm duyệt u
    inTime[u] = ++timer;
    // thời điểm nhỏ nhất duyệt node x mà u có thể tới x bằng nhiều nhất một
    // back edge từ u (và tổ tiên của u)
    low[u] = inTime[u];
    for (auto v : adjList[u]) {
        if (!inTime[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            // con cháu của v và v không thể đi tới u hoặc tổ tiên của u mà không đi qua (u, v)
            if (low[v] > inTime[u]) {
                bridgeFound = true;
            }
        }
        else if (v != parent) {
            low[u] = min(low[u], inTime[v]);
        }
    }
}

int main() {
    int v, e;
    // Nhập số đỉnh, số cạnh
    cin >> v >> e;
    adjList.resize(v);
    // Nhập danh sách cạnh (đánh số đỉnh bắt đầu từ 0)
    for (int i = 0; i < e; i++) {
        int s, t;
        cin >> s >> t;
        adjList[s].push_back(t);
        adjList[t].push_back(s);
    }
    inTime.assign(v, 0);
    low.resize(v);
    bridgeFound = false;
    dfs(0, -1);
    if (bridgeFound) {
        cout << "Graph has at least one bridges.";
    } else {
        cout << "There aren't any bridges.";
    }
    return 0;
}
