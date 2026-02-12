#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

void bt(int now, vector<int> &path, vector<vector<int>> &paths, const vector<vector<int>> &adj) {
    path.push_back(now);

    paths.push_back(path);
    for (const int nxt : adj[now]) {
        bt(nxt, path, paths, adj);
    }

    path.pop_back();
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    const int n = 15;

    int m = 0;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            adj[i].push_back(j);
            m++;
        }
    }

    vector<vector<int>> paths;
    for (int i = 0; i < n; i++) {
        vector<int> path;
        bt(i, path, paths, adj);
    }

    sort(all(paths));

    cout << "n = " << n << '\n';
    cout << "m = " << m << '\n';
    cout << "# possible queries = " << 32 * (n + m) << '\n';

    set<pii> e;
    for (int i = 0; i < 32 * (n + m); i++) {
        for (int j = 0; j + 1 < sz(paths[i]); j++) {
            e.insert({paths[i][j], paths[i][j + 1]});
        }
    }

    cout << "naive answer = " << sz(e) << '\n';

    cout << '\n';
    cout << "# paths = " << sz(paths) << '\n';
    for (int i = 0; i < sz(paths); i++) {
        cout << i + 1 << "th path is: ";
        for (const int u : paths[i]) cout << u << ' ';
        cout << '\n';
    }

    return 0;
}
