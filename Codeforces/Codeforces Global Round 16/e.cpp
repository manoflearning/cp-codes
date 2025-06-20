#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 202020;

int n;
vector<int> t[N];
bool is_used[N], is_bud[N];
int cnt_leaves_with_parent_1 = 0;
int cnt_buds = 0;
int cnt_leaves_with_bud = 0;

void init() {
    for (int i = 1; i <= n; i++) {
        t[i].clear();
        is_used[i] = is_bud[i] = 0;
    }
    cnt_leaves_with_parent_1 = 0;
    cnt_buds = 0;
    cnt_leaves_with_bud = 0;
    n = 0;
}

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    int cnt_leaves = 0;
    for (auto &i : t[v]) {
        if (i == prv) continue;
        dfs(i, v);
        
        if (!is_used[i]) {
            is_bud[v] = 1;
            cnt_leaves++;
        }
    }

    if (!is_bud[v]) return;

    if (v == 1) {
        cnt_leaves_with_parent_1 += cnt_leaves;
    } else {
        is_used[v] = 1;
        for (auto &i : t[v]) {
            if (i != prv) is_used[i] = 1;
        }
        cnt_buds++;
        cnt_leaves_with_bud += cnt_leaves;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();
        
        dfs(1, -1);

        // cout << cnt_leaves_with_parent_1 << ' ' << cnt_leaves_with_bud << ' ' << cnt_buds << '\n';
        if (cnt_leaves_with_parent_1 > 0) {
            cout << cnt_leaves_with_bud + cnt_leaves_with_parent_1 - cnt_buds << '\n';
        } else {
            cout << cnt_leaves_with_bud - cnt_buds + 1 << '\n';
        }
    }
}
