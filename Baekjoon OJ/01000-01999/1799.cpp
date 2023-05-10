// solution 1
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

int n, a[15][15];
vector<pii> idx[2];
vector<pii> prv;

int bt(int x, int parity) {
    if (x == idx[parity].size()) return prv.size();

    int ret = 0, pos = 1;
    auto& it = idx[parity][x];
    for (auto& i : prv) {
        if (abs(i.fr - it.fr) == abs(i.sc - it.sc)) { pos = 0; break; }
    }

    ret = max(ret, bt(x + 1, parity));

    if (pos) {
        prv.push_back(it);
        ret = max(ret, bt(x + 1, parity));
        prv.pop_back();
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            if (a[i][j]) {
                idx[(i + j) & 1].push_back({ i, j });
            }
        }
    }

    cout << bt(0, 0) + bt(0, 1);
}

// solution 2
// 두 가지 종류의 대각선을 생각할 수 있다. 1. 좌측 상단 -> 우측 하단, 2. 우측 상단 -> 좌측 하단.
// 대각선은 각 종류당 2n - 1개다. 이를 정수 1, 2, ..., 2n - 1로 해싱할 수 있다.

// 같은 대각선에 두 개 이상의 비숍이 위치해서는 안된다.
// 한 좌표는 해당하는 두 종류의 대각선 해싱 값의 pair로 생각할 수 있다. (a_i, b_i).
// 이제 문제는 (a_i, b_i)들이 주어질 때, 모든 a_i 값이 중복되지 않고, 모든 b_i 값이 중복되지 않도록 최대한 많은 좌표를 고르는 것이다.
// 한 a_i 값에 대해 최대 하나의 b_i를 고르는 것으로 생각할 수 있다. 비트마스킹 dp로 답을 구할 수 있다.
/*#include <bits/stdc++.h>
using namespace std;

int n, a[11][11];
int label1[11][11], label2[11][11];

set<int> idx1[22];
int vi2[22];
int dp[20][1 << 20];

int f(int v, int bit) {
    int& ret = dp[v][bit];
    if (ret != -1) return ret;
    if (v == 2 * n - 1) return ret = 0;

    ret = f(v + 1, bit);
    for (auto& i : idx1[v]) {
        if (bit & (1 << i)) continue;
        ret = max(ret, 1 + f(v + 1, bit | (1 << i)));
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // initialize
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < (1 << 20); j++) {
            dp[i][j] = -1;
        }
    }

    // input
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    // labeling
    for (int i = 1; i <= n; i++) 
        label1[1][i] = label2[1][i] = i - 1;
    for (int i = 2; i <= n; i++) 
        label1[i][1] = label2[i][n] = n + i - 2;

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (2 <= j) label1[i][j] = label1[i - 1][j - 1];
            if (j <= n - 1) label2[i][j] = label2[i - 1][j + 1];
        }
    }

    // solve
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!a[i][j]) continue;
            idx1[label1[i][j]].insert(label2[i][j]);
        }
    }

    cout << f(0, 0);
}*/