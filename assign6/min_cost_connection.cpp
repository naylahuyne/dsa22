#include <iostream>
#include <fstream>

using namespace std;

struct Edge {
    int u;
    int v;
    int weight;
};

// // for debugging
//void print(Edge edgeList[], int m) {
//    for (int i = 0; i < m; i++) {
//        cout << edgeList[i].u << " " << edgeList[i].v << " " << edgeList[i].weight << endl;
//    }
//}

void merge(Edge edgeList[], int left, int mid, int right) {

    Edge first[mid - left + 1];
    Edge second[right - mid];
    for (int i = left; i <= mid; i++) {
        first[i - left] = edgeList[i];
    }
    for (int i = mid + 1; i <= right; i++) {
        second[i - mid - 1] = edgeList[i];
    }
    int firstIndex = 0;
    int secondIndex = 0;
    for (int i = left; i <= right; i++) {
        if (firstIndex < mid - left + 1 && secondIndex < right - mid) {
            if (first[firstIndex].weight <= second[secondIndex].weight) {
                edgeList[i] = first[firstIndex++];
            }
            else {
                edgeList[i] = second[secondIndex++];
            }
        }
        else if (secondIndex >= right - mid) {
            edgeList[i] = first[firstIndex++];
        }
        else {
            edgeList[i] = second[secondIndex++];
        }
    }
}

void mergeSort(Edge edgeList[], int left, int right) {
    if (left == right) return;
    int mid = (left + right) / 2;
    mergeSort(edgeList, left, mid);
    mergeSort(edgeList, mid + 1, right);
    merge(edgeList, left, mid, right);
}

void findMinCostConnection(Edge edgeList[], int edges, int vertices, ofstream &of) {
    bool visited[vertices];
    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }
    mergeSort(edgeList, 0, edges - 1);
    Edge chosen[vertices - 1];
    chosen[0] = edgeList[0];
    visited[edgeList[0].u - 1] = true;
    visited[edgeList[0].v - 1] = true;
    int countVisited = 2;
    int countChosen = 1;
    int totalCost = edgeList[0].weight;
    while (countVisited < vertices) {
        for (int i = 0; i < edges; i++) {
            if (visited[edgeList[i].u - 1] != visited[edgeList[i].v - 1]) {
                visited[edgeList[i].v - 1] = true;
                visited[edgeList[i].u - 1] = true;
                chosen[countChosen] = edgeList[i];
                totalCost += edgeList[i].weight;
                countChosen++;
                countVisited++;
                break;
            }
        }
    }
    mergeSort(chosen, 0, vertices - 2);
    of << totalCost << endl;
    for (int i = 0; i < vertices - 1; i++) {
        of << chosen[i].u << " " << chosen[i].v << " "
            << chosen[i].weight << endl;
    }
}

int main() {
    ifstream f ("connection.txt");
    if (f.is_open()) {
        int n, m;
        f >> n >> m;
        Edge edgeList[m];
        for (int i = 0; i < m; i++) {
            f >> edgeList[i].u >> edgeList[i].v >> edgeList[i].weight;
        }
        f.close();
        ofstream of ("connection.out");
        findMinCostConnection(edgeList, m, n, of);
    }
    else {
        cout << "Error opening input file";
    }
    return 0;
}
