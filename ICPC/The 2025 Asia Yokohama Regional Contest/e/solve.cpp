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

struct fraction {
    __int128_t n, d;

    fraction(__int128_t n_ = 0, __int128_t d_ = 1) { set(n_, d_); }
    void set(__int128_t n_, __int128_t d_) {
        n = n_;
        d = d_;
        norm();
    }
    __int128_t gcd_ll(__int128_t a, __int128_t b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b) {
            __int128_t t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
    void norm() {
        if (d < 0) n = -n, d = -d;
        __int128_t g = gcd_ll(n, d);
        if (g) n /= g, d /= g;
    }
    bool operator<(const fraction &rhs) const {
        return (__int128_t)n * rhs.d < (__int128_t)rhs.n * d;
    }
    fraction operator/(const fraction &rhs) const {
        fraction ret;
        ret.n = n * rhs.d;
        ret.d = d * rhs.n;
        ret.norm();
        return ret;
    }
};

fraction bs(ll a, ll b, ll c, const ll tgt) {
    ll l = 1, r = 2e9;
    while (l < r) {
        ll mid = (l + r) >> 1;

        fraction len{a, mid};

        fraction a_cnt = fraction{a, 1} / len;
        __int128_t aa = a_cnt.n / a_cnt.d;
        fraction b_cnt = fraction{b, 1} / len;
        __int128_t bb = b_cnt.n / b_cnt.d;
        fraction c_cnt = fraction{c, 1} / len;
        __int128_t cc = c_cnt.n / c_cnt.d;

        // __int128_t res = aa * bb * cc;
        if (aa > 0 && bb > 0 && cc > 0 && (tgt + cc - 1) / cc <= aa * bb) r = mid;
        else l = mid + 1;
    }
    return fraction{a, l};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll a, b, c;
        cin >> a >> b >> c;

        ll k; cin >> k;

        fraction ans{0, 1};
        ans = max(ans, bs(a, b, c, k));
        ans = max(ans, bs(b, c, a, k));
        ans = max(ans, bs(c, a, b, k));

        cout << (ll)ans.n << ' ' << (ll)ans.d << '\n';
    }
}