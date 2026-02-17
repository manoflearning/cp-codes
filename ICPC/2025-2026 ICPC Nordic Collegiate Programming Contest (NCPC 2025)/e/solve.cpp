#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

optional<vector<string>> f(int n, vector<string> a, int cnt) {
    auto ret = a;

    int cnt_l = 0;
    vector<int> l(n);
    l[0] = n;
    for (int x = 1; x < n; x++) l[x] = n - x + 1;

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < l[x]; y++) cnt_l += a[x][y] == 'C';
    }

    if (cnt_l > cnt / 2) return nullopt;

    for (int x = 0; x < n; x++) {
        for (int &y = l[x]; y < 2 * n - 1 && a[x][y] != '#'; y++) {
            if (cnt_l == cnt / 2) break;
            cnt_l += (a[x][y] == 'C');
        }
    }

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < 2 * n - 1; y++) {
            if (a[x][y] == '#') continue;
            ret[x][y] = (y < l[x] ? 'A' : 'B');
        }
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<string> a(n);
    for (auto &i : a) cin >> i;

    int cnt = 0;
    for (auto &i : a) for (auto &j : i) cnt += (j == 'C');

    if (cnt & 1) {
        cout << "impossible\n";
        exit(0);
    }

    auto ans = a;
    int cnt_a = 0;

    auto update = [&](int x, int y) {
        if (cnt_a < cnt / 2) {
            ans[x][y] = 'A';
            cnt_a += (a[x][y] == 'C');
        } else {
            ans[x][y] = 'B';
        }
    };

    int cnt_last_row = 0;
    for (char c : a[n - 1]) cnt_last_row += (c == 'C');

    if (cnt / 2 <= cnt_last_row) {
        if (cnt / 2 == cnt_last_row) {
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < 2 * n - 1; y++) {
                    if (a[x][y] == '#') continue;
                    if (x + 1 == n) ans[x][y] = 'A';
                    else ans[x][y] = 'B';
                }
            }
        } else {
            auto res1 = f(n, a, cnt);
            if (res1) ans = *res1;
            else {
                for (auto &i : a) reverse(all(i));
                auto res2 = f(n, a, cnt);
                if (res2) {
                    ans = *res2;
                    for (auto &i : ans) reverse(all(i));
                } else {
                    cout << "impossible\n";
                    exit(0);
                }
            }
        }
    } else {
        for (int x = n - 1; x >= 0; x--) {
            for (int i = (n - x - 1); i < n; i++) {
                if (i == n - 1) {
                    update(x, i);
                } else {
                    update(x, i);
                    update(x, 2 * n - i - 2);
                }
            }
        }
    }

    for (auto &i : ans) cout << i << '\n';
}
