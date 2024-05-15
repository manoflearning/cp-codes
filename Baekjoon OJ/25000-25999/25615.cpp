#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

struct Fraction {
    ll n, d; // represent n/d

    Fraction(ll N, ll D) { n = N, d = D; reduce(); }
    Fraction(ll N) { n = N, d = 1; }
    Fraction() { n = 0, d = 1; }

    void reduce() {
        ll g = gcd(n, d);
        n /= g, d /= g;
        if (d < 0) n *= -1, d *= -1;
    }
    Fraction abs() const {
        Fraction ret = Fraction(n, d);
        if (ret.n < 0) ret.n *= -1;
        return ret;
    }

    bool operator==(const Fraction& rhs) const {
        return n * rhs.d == rhs.n * d;
    }
    bool operator!=(const Fraction& rhs) const {
        return n * rhs.d != rhs.n * d;
    }
    bool operator<(const Fraction& rhs) const {
        return n * rhs.d < rhs.n * d;
    }
    bool operator>(const Fraction& rhs) const {
        return n * rhs.d > rhs.n * d;
    }

    Fraction operator+(const Fraction& rhs) const {
        Fraction ret;
        ret.n = n * rhs.d + rhs.n * d;
        ret.d = d * rhs.d;
        ret.reduce();
        return ret;
    }
    Fraction operator-(const Fraction& rhs) const {
        Fraction ret;
        ret.n = n * rhs.d - rhs.n * d;
        ret.d = d * rhs.d;
        ret.reduce();
        return ret;
    }
    Fraction operator*(const Fraction& rhs) const {
        Fraction ret;
        ret.n = n * rhs.n;
        ret.d = d * rhs.d;
        ret.reduce();
        return ret;
    }
    Fraction operator/(const Fraction& rhs) const {
        Fraction ret;
        ret.n = n * rhs.d;
        ret.d = d * rhs.n;
        ret.reduce();
        return ret;
    }
};

ll ccw(const pll& a, const pll& b, pll& c) {
    // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
    ll res = (b.fr - a.fr) * (c.sc - a.sc) - (c.fr - a.fr) * (b.sc - a.sc);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

int N;
ll x1[MAXN], Y1[MAXN], x2[MAXN], y2[MAXN];

bool YES;
Fraction ansx, ansy;

void input() {
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> x1[i] >> Y1[i] >> x2[i] >> y2[i];
}

inline ll a(int i) { return Y1[i] - y2[i]; }
inline ll b(int i) { return x2[i] - x1[i]; }
inline ll c(int i) { return x1[i] * y2[i] - x2[i] * Y1[i]; }

bool is_point_exists() {
    for (int i = 1; i <= N; i++) {
        if (x1[i] == x2[i] && Y1[i] == y2[i]) return 1;
    }
    return 0;
}

void zero_area() {
    vector<pll> arr;
    for (int i = 1; i <= N; i++) {
        if (x1[i] == x2[i] && Y1[i] == y2[i]) continue;
        arr.push_back({ x1[i], Y1[i] });
        arr.push_back({ x2[i], y2[i] });
    }

    sort(all(arr));
    arr.erase(unique(all(arr)), arr.end());

    if (sz(arr) >= 2) {
        for (int i = 2; i < sz(arr); i++) {
            if (ccw(arr[0], arr[1], arr[i]) != 0) {
                YES = 0;
                return;
            }
        }
        YES = 1;
        ansx = Fraction(arr[0].fr);
        ansy = Fraction(arr[0].sc);
    }
    else if (sz(arr) == 0) {
        YES = 1;
        ansx = Fraction();
        ansy = Fraction();
    }
}

void n_is_eq_1() {
    YES = 1;
    ansx = Fraction();
    ansy = Fraction();
}

void n_is_eq_2() {
    for (int i = 0; i < 2; i++) {
        ll A = a(1) + (i == 0 ? 1 : -1) * a(2);
        ll B = b(1) + (i == 0 ? 1 : -1) * b(2);
        ll C = c(1) + (i == 0 ? 1 : -1) * c(2);

        if (!(A == 0 && B == 0 && C != 0)) {
            YES = 1;
            ansx = Fraction();
            ansy = Fraction(-B, C);
            return;
        }
    }
}

void normalize(ll& x, ll& y) {
    ll g = gcd(x, y);
    x /= g, y /= g;
    if (y < 0) x *= -1, y *= -1;
}

void solve() {
    // get slopes of each line segments
    map<pll, int> mp;
    for (int i = 1; i <= N; i++) {
        ll x = x1[i] - x2[i], y = Y1[i] - y2[i];
        normalize(x, y);
        mp[{ x, y }] = i;
    }

    if (sz(mp) >= 3) {
        int idx1 = -1, idx2 = -1, idx3 = -1;
        for (auto& i : mp) {
            if (idx1 == -1) idx1 = i.sc;
            else if (idx2 == -1) idx2 = i.sc;
            else if (idx3 == -1) idx3 = i.sc;
            else break;
        }

        for (int bit = 0; bit < 4; bit++) {
            ll a1 = a(idx1), b1 = b(idx2), c1 = c(idx3);
            ll a2 = (bit & 1 ? 1 : -1) * a(idx2);
            ll b2 = (bit & 1 ? 1 : -1) * b(idx2);
            ll c2 = (bit & 1 ? 1 : -1) * c(idx2);
            ll a3 = (bit & 2 ? 1 : -1) * a(idx3);
            ll b3 = (bit & 2 ? 1 : -1) * b(idx3);
            ll c3 = (bit & 2 ? 1 : -1) * c(idx3);

            if (bit == 0) {
                cout << a2 << ' ' << b2 << ' ' << c2 << '\n';
                cout << a1 << ' ' << b1 << ' ' << c1 << '\n';
                cout << a3 << ' ' << b3 << ' ' << c3 << '\n';
            }

            Fraction x(
                (b2 - b1) * (c3 - c2) + (b2 - b3) * (c2 - c1),
                (b2 - b3) * (a1 - a2) - (b2 - b1) * (a3 - a2)
            );
            Fraction y(
                (c3 - c2) * x.d + (a3 - a2) * x.n,
                (b2 - b3) * x.d
            );

            set<Fraction> st;
            for (int i = 1; i <= N; i++) {
                Fraction area = Fraction(y2[i] - Y1[i]) * x 
                - Fraction(x2[i] - x1[i]) * y 
                + Fraction(x2[i] * Y1[i] - x1[i] * y2[i]);

                area = area.abs();

                st.insert(area);
            }

            if (sz(st) == 1) {
                YES = 1;
                ansx = x, ansy = y;
            }
            else YES = 0;
        }
    }
    else if (sz(mp) == 2) {

    }
    else if (sz(mp) == 1) {

    }
}

void output() {
    if (YES) {
        cout << "YES\n";
        ansx.reduce();
        ansy.reduce();
        cout << ansx.n << ' ' << ansx.d << '\n';
        cout << ansy.n << ' ' << ansy.d << '\n';
    }
    else cout << "NO";
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    if (is_point_exists()) zero_area();
    else if (N == 1) n_is_eq_1();
    else if (N == 2) n_is_eq_2();
    else if (N >= 3) solve();

    output();
}