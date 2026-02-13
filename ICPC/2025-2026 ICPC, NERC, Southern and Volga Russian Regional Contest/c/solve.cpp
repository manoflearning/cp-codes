#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;
constexpr char o = '(', e = ')';

int f(int l, int r, bool turn, const string &s, vector<vector<int>> &dp, vector<vector<bool>> &vis) {
    int &ret = dp[l][r];
    if (vis[l][r]) return ret;
    vis[l][r] = 1;
    if (l == r) return ret = 0;

    if (turn) {
        ret = 0;
        ret = min(ret, (s[l] == o ? +1 : -1) + f(l + 1, r, !turn, s, dp, vis));
        ret = min(ret, (s[r - 1] == o ? +1 : -1) + f(l, r - 1, !turn, s, dp, vis));
    } else {
        ret = -INF;
        ret = max(ret, f(l + 1, r, !turn, s, dp, vis));
        ret = max(ret, f(l, r - 1, !turn, s, dp, vis));
    }

    // DEBUG
    // cout << l << ' ' << r << ' ' << ret << '\n';
    
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n;
        string s;
        cin >> n >> s;

        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        vector<vector<bool>> vis(n + 1, vector<bool>(n + 1));

        int ans = INF;
        if (s[0] == o) ans = min(ans, 1 + f(1, n, 0, s, dp, vis));
        if (s[n - 1] == o) ans = min(ans, 1 + f(0, n - 1, 0, s, dp, vis));

        // cout << ans << ' ';
        cout << (ans <= 0 ? "Monocarp" : "Polycarp") << '\n';
    }
}