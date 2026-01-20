#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int dy[] = {0, 0, 1, 1};
constexpr int dx[] = {0, 1, 0, 1};

bool valid(int n, int m, const vector<vector<ll>> &ans) {
    bool ret = 1;

    unordered_set<ll> st;

    vector<vector<ll>> res(n - 1, vector<ll>(m - 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i + 1 < n && j + 1 < m) {
                res[i][j] ^= ans[i][j];
                res[i][j] ^= ans[i][j + 1];
                res[i][j] ^= ans[i + 1][j];
                res[i][j] ^= ans[i + 1][j + 1];
            }

            st.insert(ans[i][j]);
        }
    }

    ret &= sz(st) == n * m;
    // cout << sz(st) << '\n';
    for (int i = 0; i + 1 < n; i++) {
        for (int j = 0; j + 1 < m; j++) {
            if (i + 3 < n && j + 3 < m) {
                ret &= res[i][j] == res[i + 2][j + 2];
            }
            if (i + 3 < n && 0 <= j - 2) {
                ret &= res[i][j] == res[i + 2][j - 2];
            }

            // cout << res[i][j] << ' ';
        }
        // cout << '\n';
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    
    mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> dist(0, (1ll << 62) - 1);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<vector<ll>> ans(n, vector<ll>(m));
        for (int i = 0; i < n; i++) {
            const ll hash = dist(mt);
            for (int j = 0; j < m; j++) ans[i][j] ^= hash;
        }
        for (int j = 0; j < m; j++) {
            const ll hash = dist(mt);
            for (int i = 0; i < n; i++) ans[i][j] ^= hash;
        }

        cout << n * m << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << ans[i][j] << ' ';
            }
            cout << '\n';
        }

        assert(valid(n, m, ans));
    }
}
