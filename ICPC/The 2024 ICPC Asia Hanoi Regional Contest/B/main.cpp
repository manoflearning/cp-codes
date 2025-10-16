#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int K = 19;
const int N = 19;
const int M = 15;

const int INF = 1e9;

int k = K, n = N, m = M;
int d[N][N];
struct Edge { int u, v; };
Edge e[M];

int dp1[N][1 << N];
pair<int, int> opt1[N][1 << N];

int dp2[1 << M];
pair<int, int> opt2[1 << M];

int dp3[1 << M];
pair<int, int> opt3[1 << M];

vector<vector<int>> ans1;
vector<int> ans2;

void init() {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < (1 << n); j++) {
            dp1[i][j] = INF;
        }
    }
    for (int i = 0; i < (1 << m); i++) {
        dp2[i] = dp3[i] = INF;
    }

    ans1.clear();
    ans2.clear();
}

void input() {
    cin >> n >> k >> m;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cin >> d[i][j];
            d[j][i] = d[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        cin >> e[i].u >> e[i].v;
        e[i].u--, e[i].v--;
    }
}

void f1() { // TC: O(n^2 * 2^n) (~= 2 * 10^8)
    // base case
    for (int v = 0; v < n; v++) {
        dp1[v][1 << v] = 0;
    }

    // inductive step
    for (int bit = 1; bit < (1 << n); bit++) {
        for (int v = 0; v < n; v++) {
            if (!(bit & (1 << v))) continue;

            for (int u = 0; u < n; u++) {
                if (bit & (1 << u)) continue;

                int nbit = bit | (1 << u);
                if (dp1[v][bit] + d[u][v] < dp1[u][nbit]) {
                    dp1[u][nbit] = dp1[v][bit] + d[u][v];
                    opt1[u][nbit] = {v, bit};
                }
            }
        }
    }
}

void f2() {
    for (int bit = 1; bit < (1 << n); bit++) {
        if (k < __builtin_popcount(bit)) continue;

        int ebit = 0;
        for (int i = 0; i < m; i++) {
            bool x = 1;
            x &= (bit & (1 << e[i].u) ? 1 : 0);
            x &= (bit & (1 << e[i].v) ? 1 : 0);
            ebit |= x * (1 << i);
        }

        for (int v = 0; v < n; v++) {
            if (dp1[v][bit] < dp2[ebit]) {
                dp2[ebit] = dp1[v][bit];
                opt2[ebit] = {v, bit};
            }
        }
    }
}

void f3() {
    dp3[0] = 0;

    for (int bit2 = 1; bit2 < (1 << m); bit2++) {
        if (dp2[bit2] == INF) continue;
        for (int bit3 = 0; bit3 < (1 << m); bit3++) {
            if (dp3[bit3] == INF) continue;

            int nbit = bit2 | bit3;
            if (dp2[bit2] + dp3[bit3] < dp3[nbit]) {
                dp3[nbit] = dp2[bit2] + dp3[bit3];
                opt3[nbit] = {bit2, bit3};
            }
        }
    }
}

void rf32() {
    int now = (1 << m) - 1;
    while (now > 0) {
        ans2.push_back(opt3[now].first);
        now = opt3[now].second;
    }
}
void rf21() {
    ans1.resize(sz(ans2));
    for (int i = 0; i < sz(ans2); i++) {
        auto [v, bit] = opt2[ans2[i]];
        ans1[i].push_back(v);
        while (1) {
            int tmp = v;
            v = opt1[tmp][bit].first;
            bit = opt1[tmp][bit].second;
            if (bit == 0) break;
            ans1[i].push_back(v);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        f1();
        f2();
        f3();

        rf32();
        rf21();

        cout << dp3[(1 << m) - 1] << ' ' << sz(ans1) << '\n';
        for (auto &i : ans1) {
            cout << sz(i) << ' ';
            for (auto &j : i) {
                cout << j + 1 << ' ';
            }
            cout << '\n';
        }
    }
}
