#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr ld EPS = 1e-7;
constexpr ll INF = 1e17;

ll n, s;
ll ans = 0;

void init() {
    ans = 0;
}

ll get_sqrt(ll x) {
    ll l = 0, r = x;
    while (l < r) {
        ll mid = (l + r) >> 1;
        if (mid * mid < x) l = mid + 1;
        else r = mid;
    }
    return (l * l == x ? l : -1);
}

void case1() {
    if (s % 100 == 0) {
        if (s / 100 == n * n) {
            ans++;
        } else {
            const ll sq = get_sqrt(s / 100);
            if (sq != -1) ans = INF;
        }
    }
}

void case2() {
    if (s % 50 == 0 && get_sqrt(s / 50) != -1 && get_sqrt(s / 50) % 2 == 0) return;

    const ld sq = sqrt((ld)s / 50);
    // if (sq == -1) return;
    // cout << sq << '\n';
    for (int x = 1; x <= n - 1; x++) {
        if (x < sq / 2) continue;
        if (n - x < sq / 2) continue;

        const ll y_d = ceil(sq / 2);
        const ll y_u = n - y_d;

        ans += max(0ll, y_u - y_d + 1);
    }
}

void case3() {
    for (ll _l = 10; _l * _l <= 2 * s; _l += 10) {
        const ll l = _l / 10;
        // cout << l << '\n';
        if (s >= _l * _l) continue;
        // cout << l << '\n';
        ans += (n - l + 1) * (n - l + 1) * ((_l * _l == 2 * s ? 1 : 2));
        ans += (n - l) * (n - l) * ((_l * _l == 2 * s ? 0 : 2));
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int q;
    cin >> n >> q;

    // n *= 10; // 10^1 <= n <= 2 * 10^4

    while (q--) {
        init();

        ld _s; cin >> _s;
        s = _s * 100 + EPS;
        // cout << s << '\n';

        case1();
        case2();
        case3();

        cout << (ans >= INF ? -1 : ans) << '\n';
    }
}
