#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
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

    int n, s1, s2;
    cin >> n >> s1 >> s2;
    
    vector<int> a(n + 1);
    for (int i = 0; i < s1; i++) cin >> a[i];
    for (int i = n; i >= s1; i--) cin >> a[i];

    Tree seg{n + 1};

    int idx = -1;
    for (int i = 0; i <= n; i++) {
        seg.update(i, a[i]);
        if (a[i] == 0) idx = i;
    }
    assert(idx != -1);

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        if (!a[i]) continue;
        int res = 0;
        if (i < idx) res = seg.query(i, idx + 1);
        else res = seg.query(idx, i + 1);

        if (res <= a[i]) ans++;
    }
    cout << ans << '\n';
}
