#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 202020;
const int INF = 1e9 + 7;

int n;
ll h[MAXN];

struct Node {
    ll mxh1, mxh2;
    ll sum1, sum2, len1, len2;
    Node operator+(const Node &o) const {
        Node ret;
        if (mxh1 < o.mxh1) {
            ret.mxh1 = o.mxh1;
            ret.mxh2 = o.mxh2;
            ret.sum1 = (len1 + len2 + o.len1) * o.mxh1;
            ret.sum2 = o.sum2;
            ret.len1 = len1 + len2 + o.len1;
            ret.len2 = o.len2;
        } else if (mxh2 < o.mxh1) {
            ret.mxh1 = mxh1;
            ret.mxh2 = o.mxh1;
            ret.sum1 = sum1;
            ret.sum2 = (len2 + o.len1) * o.mxh1 + o.sum2;
            ret.len1 = len1;
            ret.len2 = len2 + o.len1 + o.len2;
        } else {
            ret.mxh1 = mxh1;
            ret.mxh2 = o.mxh2;
            ret.sum1 = sum1;
            ret.sum2 = sum2 + o.sum1 + o.sum2;
            ret.len1 = len1;
            ret.len2 = len2 + o.len1 + o.len2;
        }
        return ret;
    }
};

int flag;
struct Mx {
    vector<ll> t;
    void build(int n, bool fw) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        for (int i = flag; i < flag + n; i++) {
            if (fw) t[i] = h[i - flag + 1];
            else {
                int j = i - flag + 1;
                t[i] = h[n - j + 1];
            }
        }
        for (int i = flag - 1; i >= 1; i--)
            t[i] = max(t[i << 1], t[i << 1 | 1]);
    }
    int find(int l, int r, ll val, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return INF;
        if (l <= nl && nr <= r) {
            if (t[n] < val) return nl;
            if (nl == nr) return nl + 1;
            int mid = (nl + nr) >> 1;
            if (t[n << 1 | 1] >= val) return find(l, r, val, n << 1 | 1, mid + 1, nr);
            else return find(l, r, val, n << 1, nl, mid);
        }
        int mid = (nl + nr) >> 1;
        return min(find(l, r, val, n << 1, nl, mid), find(l, r, val, n << 1 | 1, mid + 1, nr));
    }
} mx1, mx2;

struct Seg {
    vector<Node> t;
    void build(int n, bool fw) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        for (int i = flag; i < flag + n; i++) {
            if (fw) t[i] = {h[i - flag + 1], 0, h[i - flag + 1], 0, 1, 0};
            else {
                int j = i - flag + 1;
                t[i] = {h[n - j + 1], 0, h[n - j + 1], 0, 1, 0};
            }
        }
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return {0, 0, 0, 0, 0, 0};
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
} seg1, seg2;

void input() {
    cin >> n;
    for (int i = 1; i + 1 <= n; i++) cin >> h[i];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    mx1.build(n - 1, 1);
    mx2.build(n - 1, 0);
    seg1.build(n - 1, 1);
    seg2.build(n - 1, 0);

    int q; cin >> q;
    while (q--) {
        int st, en;
        cin >> st >> en;

        if (st <= en) {
            // cout << seg1.query(st, en - 1).mxh1 << '\n';
            st = min(st, mx1.find(1, st - 1, seg1.query(st, en - 1).mxh1));
            
            auto res = seg1.query(st, en - 1);
            cout << res.sum1 + res.sum2 << '\n';
        } else {
            st = n - st + 1, en = n - en + 1;
            st = min(st, mx2.find(1, st - 1, seg2.query(st, en - 1).mxh1));
            auto res = seg2.query(st, en - 1);
            cout << res.sum1 + res.sum2 << '\n';
        }
    }
}
