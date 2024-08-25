#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int N = 202020;

int n, p[N];
vector<int> chd[N];
vector<int> lca_cnts;

int dfs(int v) {
    if (sz(chd[v]) == 1) return dfs(chd[v][0]);
    if (sz(chd[v]) == 0) return 0;

    vector<int> acc;
    for (auto& i : chd[v]) {
        acc.push_back(dfs(i));
    }
    sort(acc.rbegin(), acc.rend());
    for (int i = 2; i < sz(acc); i++) {
        if (acc[i])
            lca_cnts.push_back(acc[i]);
    }
    return acc[0] + acc[1] + 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        chd[p[i]].push_back(i);
    }

    int leaf_cnt = 0;
    for (int v = 1; v <= n; v++) {
        if (sz(chd[v]) == 0) leaf_cnt++;
    }

    lca_cnts.push_back(dfs(1));
    sort(lca_cnts.rbegin(), lca_cnts.rend());

    // for (auto& i : lca_cnts)
    //     cout << i << '\n';

    int ans = 0;
    for (auto i : lca_cnts) {
        leaf_cnt--;
        ans += 1;
        cout << ans << ' ';
        while (i--) {
            ans += 2;
            leaf_cnt--;
            cout << ans << ' ';
        }
    }
    while (leaf_cnt--) {
        cout << ++ans << ' ';
    }
}
