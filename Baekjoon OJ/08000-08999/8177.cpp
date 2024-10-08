#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, m, d;
ll k;

class Node {
public:
    ll all, mnl, mnr, mn;
    Node operator+(const Node& rhs) const {
        Node ret;
        ret.all = all + rhs.all;
        ret.mnl = min(mnl, all + rhs.mnl);
        ret.mnr = min(mnr + rhs.all, rhs.mnr);
        ret.mn  = min({ mn, rhs.mn, mnr + rhs.mnl });
        return ret;
    }
};

int flag;
class Seg {
public:
    vector<Node> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        for (int i = flag; i < flag + n; i++) {
            if (n - d + 1 <= i - flag + 1) {
                t[i] = { 0, 0, 0, 0 };
            } else t[i] = { k, k, k, k };
        }
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void add(int p, ll val) {
        t[p + flag - 1].all += val;
        t[p + flag - 1].mnl += val;
        t[p + flag - 1].mnr += val;
        t[p + flag - 1].mn  += val;
        for (p += flag - 1; p > 1; p >>= 1) {
            if (p & 1) t[p >> 1] = t[p ^ 1] + t[p];
            else t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return { 0, 0, 0, 0 };
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k >> d;

    seg.build(n);

    while (m--) {
        int x; ll val;
        cin >> x >> val;
        seg.add(x, -val);

        ll res = seg.query(1, n).mn + d * k;
        cout << (res >= 0 ? "TAK" : "NIE") << '\n';
    }
}
