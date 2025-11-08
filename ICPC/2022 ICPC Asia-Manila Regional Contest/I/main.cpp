#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;
constexpr int M = 202020;

int n, m;
vector<int> adj[M];
bool is_leaf[M];
int c[M];
int leaf_hash[M], leaf_cnt = 0;

vector<vector<int>> arr;
vector<int> arr_base;

void input() {
    cin >> n >> m;
    for (int v = 1; v <= m; v++) {
        int nxt; cin >> nxt;
        if (nxt > 0) {
            while (nxt--) {
                int u; cin >> u;
                adj[v].push_back(u);
            }
        } else {
            is_leaf[v] = 1;
            cin >> c[v];
            leaf_hash[v] = leaf_cnt++;
            arr_base.push_back(c[v]);
        }
    }
}

vector<int> f(int st) {
    vector<int> ret(leaf_cnt);
    vector<int> w(m + 1);

    w[st] = 1;
    for (int v = 1; v <= m; v++) {
        if (is_leaf[v]) {
            ret[leaf_hash[v]] = w[v];
        } else {
            for (auto &u : adj[v]) w[u] = min(INF, w[u] + w[v]);
        }
    }

    return ret;
}

int ans = 0;

void bt(int idx, int res) {
    if (idx == sz(arr)) {
        ans = max(ans, res);
        return;
    }

    bt(idx + 1, res);

    bool is_valid = 1;
    for (int i = 0; i < sz(arr[idx]); i++) {
        if (arr_base[i] < arr[idx][i]) is_valid = 0;
    }

    if (!is_valid) return;

    for (int i = 0; i < sz(arr[idx]); i++) {
        arr_base[i] -= arr[idx][i];
    }
    bt(idx + 1, res + 1);
    for (int i = 0; i < sz(arr[idx]); i++) {
        arr_base[i] += arr[idx][i];
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    for (int st = 1; st <= n; st++) {
        arr.push_back(f(st));
    }

    bt(0, 0);

    cout << ans;
}
