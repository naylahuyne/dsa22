#include <iostream>
//#include <list>
#include <queue>
#include <fstream>

using namespace std;

/**
 * Tìm các công việc có thể làm đầu tiên và đưa lần lượt vào hàng đợi.
 * Với mỗi phần tử trong hàng đợi, 
 * kiểm tra xem đã làm công việc cần làm sau nó (next job) hay chưa (bằng danh sách cạnh),
 * nếu chưa làm, kiếm tra tiếp xem công việc (next job) có cần làm sau công việc nào chưa được làm hay không,
 * nếu không, làm công việc đó.
*/
void orderJobs(int edgeList[][2], int m, int n, ofstream &of) {
    queue<int> q;
    bool done[n];
    for (int i = 0; i < n; i++) {
        done[i] == false;
    }
    for (int i = 0; i < m; i++) {
        bool fatal = false;
        for (int j = 0; j < m; j++) {
            if (edgeList[i][0] == edgeList[j][1]) {
                fatal = true;
                break;
            }
        }
        if (fatal) continue;
        if (done[edgeList[i][0] - 1] == false) {
            done[edgeList[i][0] - 1] = true;
            q.push(edgeList[i][0]);
            of << edgeList[i][0] << " ";
        }
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < m; i++) {
            if (edgeList[i][0] == cur) {
                if (!done[edgeList[i][1] - 1]) {
                    bool fatal = false;
                    for (int j = 0; j < m; j++) {
                        if (edgeList[j][1] == edgeList[i][1]
                            && i != j
                            && done[edgeList[j][0] - 1] == false) {
                            fatal = true;
                            break;
                        }
                    }
                    if (fatal) continue;
                    done[edgeList[i][1] - 1] = true;
                    q.push(edgeList[i][1]);
                    of << edgeList[i][1] << " ";
                }
            }
        }
    }
}

int main() {
    ifstream f ("jobs.txt");
    if (f.is_open()) {
        int n, m;
        f >> n >> m;
        int edgeList[m][2];
        for (int i = 0; i < m; i++) {
            f >> edgeList[i][0] >> edgeList[i][1];
        }
        f.close();
        ofstream of ("jobs.out");
        orderJobs(edgeList, m, n, of);
    }
    else {
        cout << "Error opening input file";
    }
    return 0;
}
