#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

struct Tree {
    typedef int T;
    static constexpr T unit = 0;
    T f(T a, T b) { return max(a, b); }
    vector<T> s; int n;
    Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;) {
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
        }
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

    int h, w;
    cin >> h >> w;

    vector<string> a(h);
    for (auto &i : a) cin >> i;

    Tree seg{w};
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            if (a[x][y] == '_') continue;
            const int res = seg.query(y + 1, w) + 1;
            seg.update(y, res);
        }
    }

    cout << seg.query(0, w) << '\n';
}