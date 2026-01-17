#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Tree {
    typedef ll T;
    static constexpr T unit = 0;
    T f(T a, T b) { return a + b; }
    vector<T> s; int n;
    Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] += val; pos /= 2;) {
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
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    
    int n;
    string s;
    cin >> n >> s;

    vi ps(n + 1); //, lc(n + 1), rc(n + 1);
    // int cnt_c = 0;
    for (int i = 1; i <= n; i++) {
        ps[i] = (s[i - 1] == 'A' ? 1 : (s[i - 1] == 'B' ? -1 : 0)) + ps[i - 1];

        // lc[i] = cnt_c;

        // if (s[i - 1] == 'C') cnt_c++;
        // else cnt_c = 0;
    }

    // cnt_c = 0;
    // for (int i = n; i >= 1; i--) {
    //     rc[i] = cnt_c;
    //     if (s[i - 1] == 'C') cnt_c++;
    //     else cnt_c = 0;
    // }

    ll ans = 0;

    Tree seg{2 * n + 1};
    seg.update(ps[0] + n, 1);
    for (int i = 1; i <= n; i++) {
        ans += seg.query(0, ps[i] + n);
        seg.update(ps[i] + n, 1);
    }

    cout << ans << '\n';
}