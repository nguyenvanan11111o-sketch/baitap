
#include <iostream>
#include <fstream>
#include <iomanip>
#include <climits>
using namespace std;

const int MAX = 100;

int A[MAX][MAX];
int n;

// Cau 2: Ham Nhap do thi tu file
void Nhap() {
    ifstream fin("Grap.txt");

    if (!fin.is_open()) {
        cout << "Khong mo duoc file Grap.txt!\n";
        exit(1);
    }

    fin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> A[i][j];
        }
    }

    fin.close();
}

// Cau 3: Ham Hien Thi ma tran trong so
void HienThi() {
    cout << "\nMa tran trong so cua do thi:\n";

    cout << setw(5) << " ";
    for (int i = 0; i < n; i++)
        cout << setw(5) << "V" + to_string(i + 1);
    cout << '\n';

    for (int i = 0; i < n; i++) {
        cout << setw(5) << "V" + to_string(i + 1);

        for (int j = 0; j < n; j++)
            cout << setw(5) << A[i][j];

        cout << '\n';
    }
}

// Cau 4: Tim duong di ngan nhat bang Dijkstra
void TimDuongDi(int u, int v) {
    // u, v duoc danh so tu 1 den n
    u--;
    v--;

    if (u < 0 || u >= n || v < 0 || v >= n) {
        cout << "Dinh khong hop le!\n";
        return;
    }

    int d[MAX], truoc[MAX];
    bool daXet[MAX] = {};

    for (int i = 0; i < n; i++) {
        d[i] = INT_MAX;
        truoc[i] = -1;
    }

    d[u] = 0;

    for (int k = 0; k < n; k++) {
        int x = -1;

        // Tim dinh chua xet co khoang cach nho nhat
        for (int i = 0; i < n; i++) {
            if (!daXet[i] &&
                d[i] != INT_MAX &&
                (x == -1 || d[i] < d[x])) {
                x = i;
            }
        }

        if (x == -1)
            break;

        daXet[x] = true;

        if (x == v)
            break;

        // Cap nhat khoang cach cac dinh ke voi x
        for (int y = 0; y < n; y++) {
            if (A[x][y] > 0 && !daXet[y]) {
                if (d[x] + A[x][y] < d[y]) {
                    d[y] = d[x] + A[x][y];
                    truoc[y] = x;
                }
            }
        }
    }

    if (d[v] == INT_MAX) {
        cout << "\nKhong co duong di tu V"
             << u + 1 << " den V" << v + 1 << ".\n";
        return;
    }

    // Truy vet duong di
    int path[MAX], dem = 0;

    for (int x = v; x != -1; x = truoc[x])
        path[dem++] = x;

    cout << "\nDuong di ngan nhat tu V"
         << u + 1 << " den V" << v + 1 << ": ";

    for (int i = dem - 1; i >= 0; i--) {
        cout << "V" << path[i] + 1;
        if (i > 0)
            cout << " -> ";
    }

    cout << "\nTong trong so: " << d[v] << '\n';
}

// Cau 5: Ham main
int main() {
    Nhap();

    HienThi();

    TimDuongDi(1, 6);  // Tu V1 den V6

    return 0;
}
