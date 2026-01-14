#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int r, c;
vector<string> a;
ll ans = 0;

inline ll nc4(ll n) {
    if (n < 4) return 0;
    return n * (n - 1) * (n - 2) * (n - 3) / 24;
}
inline ll nc3(ll n) {
    if (n < 3) return 0;
    return n * (n - 1) * (n - 2) / 6;
}
inline ll nc2(ll n) {
    if (n < 2) return 0;
    return n * (n - 1) / 2;
}
inline ll nc1(ll n) {
    if (n < 1) return 0;
    return n;
}

void solve() {
    vector<vector<ll>> ps(r, vector<ll>(c));
    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) {
            ps[y][x] = (a[y][x] == '.') + (x ? ps[y][x - 1] : 0);
            // cout << ps[y][x] << ' ';
        }
        // cout << '\n';
    }
    // cout << '\n';

    { // case 1
        for (int y = 0; y < r; y++) {
            ans += nc4(ps[y][c - 1]) * 24;
        }
    }
    { // case 2
        for (int x = 0; x < c; x++) {
            ll acc = 0;
            for (int y = 0; y < r; y++) {
                if (a[y][x] == '#') continue;

                ans += acc * nc2(ps[y][c - 1] - 1) * 4;
                acc++;
            }
        }
    }
    { // case 3
        ll res = 0;
        for (int x = 0; x < c; x++) {
            ll acc = 0;
            for (int y = r - 1; y >= 0; y--) {
                if (a[y][x] == '#') continue;

                res += acc * nc2(ps[y][c - 1] - 1) * 4;
                acc++;
            }
            // cout << x << ' ' << acc << '\n';
        }
        ans += res;
        // cout << res << '\n';
    }
    { // case 4
        ll res = 0;
        for (int x = 0; x < c; x++) {
            ll acc = 0;
            for (int y = 0; y < r; y++) {
                if (a[y][x] == '#') continue;

                res += acc * nc1(ps[y][c - 1] - 1) * 2;
                acc += nc1(ps[y][c - 1] - 1);
            }
            // cout << x << ' ' << acc << '\n';
        }
        ans += res;
        // cout << res << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> r >> c;
    a.assign(r, string{});
    for (auto &i : a) cin >> i;

    solve();

    vector<string> tmp(c, string(r, '#'));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            tmp[j][i] = a[i][j];
        }
    }
    swap(r, c);
    a = tmp;

    solve();

    cout << ans << '\n';
}
