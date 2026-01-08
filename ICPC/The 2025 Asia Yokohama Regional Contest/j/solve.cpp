#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (x).size()
#define all(x) (x).begin(), (x).end()

constexpr int MOD = 998'244'353;

int n, m;
vector<string> a, ans;
bool yes;

void input() {
    cin >> n >> m;
    a.assign(n, string());
    for (auto &i : a) cin >> i;
    yes = 0;
}

bool try_fill_row(int i, vector<string> &arr, char c0, char c1) {
    string prv = arr[i];
    for (int j = 0; j < sz(arr[i]); j++) {
        char c = (j & 1 ? c1 : c0);
        if (arr[i][j] != '?' && arr[i][j] != c) {
            arr[i] = prv;
            return 0;
        }
        arr[i][j] = c;
    }
    return 1;
}

pair<bool, vector<string>> try_fill(vector<string> arr, int row0, int row1) {
    for (int i = 0; i < sz(arr); i++) {
        const int row = (i & 1 ? row1 : row0);

        if (row == 0) {
            if (!try_fill_row(i, arr, 'C', 'C')) return {0, arr};
        } else if (row == 1) {
            if (!try_fill_row(i, arr, 'I', 'P')) 
                if (!try_fill_row(i, arr, 'P', 'I')) return {0, arr};
        } else if (row == 2) {
            if (!try_fill_row(i, arr, 'C', 'P')) 
                if (!try_fill_row(i, arr, 'P', 'C')) return {0, arr};
        } else if (row == 3) {
            if (!try_fill_row(i, arr, 'C', 'I')) 
                if (!try_fill_row(i, arr, 'I', 'C')) return {0, arr};
        }
    }
    return {1, arr};
}

void solve() {
    vector<pii> types = {{0, 1}, {1, 0}, {2, 3}, {3, 2}};
    for (const auto &[row0, row1] : types) {
        const auto [valid, res] = try_fill(a, row0, row1);
        if (valid) { ans = res, yes = 1; return; }
    }

    vector<string> b(m, string(n, '?'));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            b[j][i] = a[i][j];
        }
    }

    for (const auto &[row0, row1] : types) {
        const auto [valid, res] = try_fill(b, row0, row1);
        if (valid) {
            ans.assign(n, string(m, '?'));
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    ans[j][i] = res[i][j];
            yes = 1; return;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        input();

        solve();

        if (yes) {
            cout << "yes\n";
            for (auto &i : ans) {
                cout << i << '\n';
            }
        } else {
            cout << "no\n";
        }
    }
}
