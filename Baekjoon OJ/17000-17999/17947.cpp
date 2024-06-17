#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int N = 101010, K = 404040;

int n, m, k;
bool vis[4 * N];
int lb, ans = 0;

void input() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        vis[u] = vis[v] = 1;
    }
    int u, v;
    cin >> u >> v;
    vis[u] = vis[v] = 1;
    lb = abs(u % k - v % k) + 1;
}

vector<int> acc;
void solve() {
    for (int i = 1; i <= 4 * n; i++) {
        if (!vis[i]) acc.push_back(i % k);
    }

    sort(acc.begin(), acc.end());

    int mid = sz(acc) / 2;

    int p1 = 0, p2 = mid;
    while (p1 < mid && p2 < sz(acc)) {
        while (p2 < sz(acc) && acc[p2] - acc[p1] < lb) p2++;

        if (p2 == sz(acc)) break;

        ans++, p1++, p2++;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    cout << min(ans, m - 1);
}