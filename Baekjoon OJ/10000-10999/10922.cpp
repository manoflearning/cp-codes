#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

struct Node {
    ll x; int mod;
    Node operator*(const Node& rhs) const {
        Node ret;
        ret.x = x * rhs.x;
        ret.mod = mod || rhs.mod;
        if (ret.x >= MOD) {
            ret.x %= MOD;
            ret.mod = 1;
        }
        return ret;
    }
};

int flag = 1;
struct MulSeg {
    vector<Node> t;
    void build(int N) {
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1, { 1, 0 });
    }
    void modify(int p, ll val) {
        for (t[p += flag - 1] = { val, 0 }; p > 1; p >>= 1)
            t[p >> 1] = t[p] * t[p ^ 1];
    }
    Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return { 1, 0 };
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) * query(l, r, n << 1 | 1, mid + 1, nr);
    }
}mul;

int n;
ll x[505050], y[505050];

struct OptSeg {
    vector<int> t;
    int cal(int optl, int optr) {
        if (optl > optr) swap(optl, optr);
        Node v = mul.query(optl + 1, optr);
        if (v.mod || (!v.mod && y[optl] < v.x * y[optr])) return optr;
        else return optl;
    }

    void build(int N) {
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1, 1);
        for (int i = 1; i <= N; i++) t[i + flag - 1] = i;
        for (int i = flag - 1; i >= 1; i--) {
            t[i] = cal(t[i << 1], t[i << 1 | 1]);
        }
    }
    void modify(int p) {
        t[p + flag - 1] = p;
        for (p += flag - 1; p > 1; p >>= 1) {
            t[p >> 1] = cal(t[p], t[p ^ 1]);
        }
    }
    int query() { return t[1]; }
}opt;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];
    for (int i = 1; i <= n; i++) cin >> y[i];
}

ll getAns(int opt) { return y[opt] * mul.query(1, opt).x % MOD; }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    // y[i] >= max(x[i + 1] * ... * x[j] * y[j])면 모든 말을 팔고,
    // 그렇지 않으면 말을 팔지 않는다.

    // initialize
    mul.build(n);
    for (int i = 1; i <= n; i++) mul.modify(i, x[i]);

    opt.build(n);

    cout << getAns(opt.query()) << '\n';

    // query
    int m; cin >> m;
    while (m--) {
        int op, p, q;
        cin >> op >> p >> q;
        p++;
        
        if (op == 1) {
            mul.modify(p, q);
            opt.modify(p);
        }
        if (op == 2) {
            y[p] = q;
            opt.modify(p);
        }
        
        cout << getAns(opt.query()) << '\n';
    }
}