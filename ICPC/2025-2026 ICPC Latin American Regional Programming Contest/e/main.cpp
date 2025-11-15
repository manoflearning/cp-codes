#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;
constexpr ll dx[] = {1, -1, 1, -1};
constexpr ll dy[] = {1, 1, -1, -1};

constexpr int Q = 303030;

int flag;
struct Seg {
    vector<ll> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, INF);
        lazy.resize(flag << 1);
        for (int i = 1; i <= n; i++) t[i + flag - 1] = i - 1;
        for (int i = flag - 1; i >= 1; i--)
            t[i] = min(t[i << 1], t[i << 1 | 1]);
    }
    void propagate(int n) {
        if (lazy[n]) {
            if (n < flag) {
                lazy[n << 1] += lazy[n];
                lazy[n << 1 | 1] += lazy[n];
            }
            t[n] += lazy[n];
            lazy[n] = 0;
        }
    }
    void add(int l, int r, ll val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] += val;
            propagate(n);
            return;
        }
        int mid = (nl + nr) >> 1;
        add(l, r, val, n << 1, nl, mid);
        add(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = min(t[n << 1], t[n << 1 | 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
} seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    seg.build(Q);

    int q; cin >> q;
    while (q--) {
        string s; cin >> s;

        int x = stoi(s.substr(1, sz(s) - 1));

        x = min(x, Q);

        if (s[0] == '+') {
            seg.add(1, x, 1);
        } else {
            seg.add(1, x, -1);
        }

        auto res = seg.query(1, Q);
        cout << res << ' ';
    }
}