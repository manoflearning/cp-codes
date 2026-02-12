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

    const int n = 5;

    int m = 0;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            adj[j].push_back(i);
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

    cout << '\n';
    cout << "# paths = " << sz(paths) << '\n';
    for (int i = 0; i < sz(paths); i++) {
        cout << i + 1 << "th path is: ";
        cout << sz(paths[i]) << ' ';
        for (const int u : paths[i]) cout << u + 1 << ' ';
        cout << '\n';
    }

    return 0;
}
