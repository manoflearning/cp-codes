#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

unordered_set<int> st;
int mx{}, cnt{};
void bt(int i, int j, int acc, const int n, const vector<vector<int>> &a) {
    acc += a[i][j];

    if (i == n - 1 && j == n - 1) {
        st.insert(acc);
        mx = max(mx, acc);
        cnt++;
        return;
    }

    if (i + 1 < n) bt(i + 1, j, acc, n, a);
    if (j + 1 < n) bt(i, j + 1, acc, n, a);
}

bool is_valid(const int n, const vector<vector<int>> &a) {
    bt(0, 0, 0, n, a);
    return sz(st) == cnt && mx <= (int)6e6;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<vector<int>> a(n, vector<int>(n));
    vector<vector<int>> l(n, vector<int>(n, INF));
    vector<vector<int>> r(n, vector<int>(n, -INF));

    a[0][0] = 0;
    l[0][0] = 0, r[0][0] = 0;

    for (int len = 1; len < 2 * n - 1; len++) {
        for (int i = max(0, len - (n - 1)); i <= min(n - 1, len); i++) {
            const int j = len - i;

            if (i > max(0, len - (n - 1))) {
                l[i][j] = r[i - 1][j + 1] + 1;
            } else {
                l[i][j] = 0;
            }

            int cnt = 0, prv_l = INF;
            if (i > 0) {
                cnt += r[i - 1][j] - l[i - 1][j] + 1;
                prv_l = min(prv_l, l[i - 1][j]);
            }
            if (j > 0) {
                cnt += r[i][j - 1] - l[i][j - 1] + 1;
                prv_l = min(prv_l, l[i][j - 1]);
            }

            r[i][j] = l[i][j] + cnt - 1;
            a[i][j] = l[i][j] - prv_l;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }

    // assert(is_valid(n, a));

    return 0;
}
