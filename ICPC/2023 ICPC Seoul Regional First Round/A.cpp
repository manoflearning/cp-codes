#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) (int)(a).size()

const int MAXN = 50505;

int n;
vector<int> t[MAXN];
int ans[MAXN];
int up[MAXN], lb = 1, ub = n;

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
    lb = 1, ub = n;
}

void dfs(int v, int prv) {
    if (prv == -1 || up[prv] == 0) { ans[v] = lb++; up[v] = 0; }
    else {
        ans[v] = ub--;
        up[v] = 1;
    }

    for (auto& i : t[v]) {
        if (i == prv) continue;
        dfs(i, v);
    }
}

void solve() {
    for (int v = 1; v <= n; v++) {
        if (sz(t[v]) > 1) {
            dfs(v, -1);
            break;
        }
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

    for (int v = 1; v <= n; v++)
        cout << ans[v] << ' ';
}