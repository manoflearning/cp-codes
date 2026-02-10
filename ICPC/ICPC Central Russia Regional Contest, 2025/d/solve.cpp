#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

struct Tree {
    typedef pii T;
    static constexpr T unit = {0, -1};
    T f(T a, T b) { return max(a, b); }
    vector<T> s; int n;
    Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) {
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<int> a(n);
    for (auto &i : a) cin >> i;

    vector<int> cc;
    for (auto &i : a) {
        cc.push_back(i);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    Tree seg_d{sz(cc)}, seg_u{sz(cc)};

    for (auto &i : a) {
        i = lower_bound(all(cc), i) - cc.begin();
    }

    vector<vector<int>> dp(n, vector<int>(2, -INF));
    vector<vector<int>> opt(n, vector<int>(2, -1));
    // base case
    dp[0][0] = 1;
    dp[0][1] = 1;
    seg_d.update(a[0], {dp[0][0], 0});
    seg_u.update(a[0], {dp[0][1], 0});

    // inductive step
    for (int i = 1; i < n; i++) {
        auto res_d = seg_u.query(a[i] + 1, sz(cc));
        auto res_u = seg_d.query(0, a[i]);

        dp[i][0] = res_d.first + 1;
        dp[i][1] = res_u.first + 1;
        opt[i][0] = res_d.second;
        opt[i][1] = res_u.second;

        seg_d.update(a[i], {dp[i][0], i});
        seg_u.update(a[i], {dp[i][1], i});
    }

    int opt_k = 0;
    int opt_i = -1, opt_j = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            if (dp[i][j] < 3) continue;
            if (opt_k < dp[i][j]) {
                opt_k = dp[i][j];
                opt_i = i, opt_j = j;
            }
        }
    }

    cout << opt_k << '\n';
    if (opt_k == 0) return 0;

    vector<int> ans;
    while (opt_i != -1) {
        ans.push_back(opt_i);
        opt_i = opt[opt_i][opt_j];
        opt_j = 1 - opt_j;
    }

    reverse(all(ans));
    for (auto &i : ans) cout << i << ' ';
}
