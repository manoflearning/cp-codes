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
    static constexpr T unit = INT_MIN;
    T f(T a, T b) { return max(a, b); }
    vector<T> s; int n;
    Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2; )
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
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

    int n; cin >> n;
    
    vector<int> a(n), b(n), t(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> t[i];

    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) {
        if (a[i] ^ a[j]) return a[i] < a[j];
        else return t[i] > t[j];
    });

    vector<int> cc;
    for (int i = 0; i < n; i++) {
        b[i] = a[i] + t[i];
        cc.push_back(b[i]);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (int i = 0; i < n; i++) {
        b[i] = lower_bound(all(cc), b[i]) - cc.begin();
    }

    Tree seg(sz(cc));
    vector<int> dp(n);
    for (int i : ord) {
        const int res = max(-1, seg.query(b[i], sz(cc))) + 1;
        dp[i] = res;
        seg.update(b[i], res);
    }

    for (auto &i : dp) cout << i << ' ';
}
