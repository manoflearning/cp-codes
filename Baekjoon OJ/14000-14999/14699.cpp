#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5050;

int n, m, h[MAXN];
vector<int> dag[MAXN];
int dp[MAXN];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (h[u] > h[v]) swap(u, v);
        dag[u].push_back(v);
    }
}

void f() {
    vector<int> ord;
    for (int v = 1; v <= n; v++) ord.push_back(v);
    sort(ord.begin(), ord.end(), [&](int p1, int p2) {
        return h[p1] > h[p2];
    });

    for (int v : ord) {
        for (auto& i : dag[v]) {
            dp[v] = max(dp[v], dp[i]);
        }
        dp[v]++;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    f();

    for (int i = 1; i <= n; i++) cout << dp[i] << '\n';
}