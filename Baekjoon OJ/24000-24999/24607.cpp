#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

// what: normalized rational type with exact arithmetic and comparisons.
// time: O(log max(|n|,|d|)) per op; memory: O(1)
// constraint: denominator != 0; results must fit in 64-bit.
// usage: fraction a(1, 3), b(2, 5); fraction c = a + b;
struct fraction {
    ll n, d;

    fraction(ll n_ = 0, ll d_ = 1) { set(n_, d_); }
    static ll gcd_ll(ll a, ll b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b) {
            ll t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
    void set(ll n_, ll d_) {
        // goal: normalize sign + reduce
        n = n_;
        d = d_;
        norm();
    }
    void norm() {
        if (d < 0) n = -n, d = -d;
        ll g = gcd_ll(n, d);
        if (g) n /= g, d /= g;
    }

    bool operator==(const fraction &rhs) const { return n == rhs.n && d == rhs.d; }
    bool operator!=(const fraction &rhs) const { return !(*this == rhs); }
    bool operator<(const fraction &rhs) const {
        return (__int128)n * rhs.d < (__int128)rhs.n * d;
    }
    bool operator>(const fraction &rhs) const { return rhs < *this; }
    bool operator<=(const fraction &rhs) const { return !(rhs < *this); }
    bool operator>=(const fraction &rhs) const { return !(*this < rhs); }
    fraction operator+(const fraction &rhs) const {
        fraction ret;
        ret.n = n * rhs.d + rhs.n * d;
        ret.d = d * rhs.d;
        ret.norm();
        return ret;
    }
    fraction operator-(const fraction &rhs) const {
        fraction ret;
        ret.n = n * rhs.d - rhs.n * d;
        ret.d = d * rhs.d;
        ret.norm();
        return ret;
    }
    fraction operator*(const fraction &rhs) const {
        fraction ret;
        ret.n = n * rhs.n;
        ret.d = d * rhs.d;
        ret.norm();
        return ret;
    }
    fraction operator/(const fraction &rhs) const {
        fraction ret;
        ret.n = n * rhs.d;
        ret.d = d * rhs.n;
        ret.norm();
        return ret;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    ll a, b;
    int n;
    cin >> a >> b >> n;

    fraction s{a, b};

    fraction x{-1, 1}, y{0, 1};

    const fraction neg1{-1, 1}, pos1{1, 1};
    for (int t = 0; t <= n; t++) {
        if (t) s.n *= -1;

        // cout << x.n << ' ' << x.d << ' ' << y.n << ' ' << y.d << '\n';

        fraction nx{}, ny{};
        if (x != pos1) {
            nx = pos1;
            ny = s * (nx - x) + y;
            if (neg1 <= ny && ny <= pos1) {
                x = nx, y = ny;
                continue;
            }
        }
        if (x != neg1) {
            nx = neg1;
            ny = s * (nx - x) + y;
            if (neg1 <= ny && ny <= pos1) {
                x = nx, y = ny;
                continue;
            }
        }
        if (y != pos1) {
            ny = pos1;
            nx = (ny - y) / s + x;
            if (neg1 <= nx && nx <= pos1) {
                x = nx, y = ny;
                continue;
            }
        }
        if (y != neg1) {
            ny = neg1;
            nx = (ny - y) / s + x;
            if (neg1 <= nx && nx <= pos1) {
                x = nx, y = ny;
                continue;
            }
        }
    }

    cout << x.n << ' ' << x.d << ' ' << y.n << ' ' << y.d << '\n';
}
