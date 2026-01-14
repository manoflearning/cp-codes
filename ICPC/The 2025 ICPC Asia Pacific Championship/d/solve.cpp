#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int MOD = 998'244'353;
constexpr int N = 101010;

array<ll, N> pow2{};

struct Node {
    int len{};
    array<int, 3> mp{};
    array<ll, 3> val{};
};

Node concat(const Node &a, const Node &b) {
    Node ret{};
    ret.len = a.len + b.len;
    for (int i = 0; i < 3; i++) {
        ret.mp[i] = a.mp[b.mp[i]];
        ret.val[i] = (a.val[b.mp[i]] + b.val[i] * pow2[a.len]) % MOD;
    }
    return ret;
}

Node get_node(ll x) {
    Node ret{};
    ret.len = 1;
    for (int i = 0; i < 3; i++) {
        if (x == i) {
            ret.mp[i] = i;
        } else {
            ret.mp[i] = 3 - (x + i);
            ret.val[i] = pow2[0];
        }
    }
    return ret;
}

constexpr Node UNIT = {0, {0, 1, 2}, {0, 0, 0}};

struct Tree {
    typedef Node T;
    static constexpr T unit = UNIT;
    T f(T a, T b) { return concat(a, b); }
    vector<T> s; int n;
    Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) { // query [b, e)
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

int n, q;
vector<int> p;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    // preprocessing
    pow2[0] = 1;
    for (int i = 1; i < N; i++) {
        pow2[i] = 2 * pow2[i - 1] % MOD;
    }

    cin >> n >> q;
    p.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> p[i]; p[i]--;
    }

    Tree seg{n + 5};
    for (int i = 1; i <= n; i++) {
        Node val = get_node(p[i]);
        seg.update(i, val);
    }

    for (int i = 0; i < q; i++) {
        char op; int x, y;
        cin >> op >> x >> y;

        if (op == 's') {
            cout << seg.query(x, y + 1).val[0] << '\n';
        } else {
            p[x] = --y;
            Node val = get_node(p[x]);
            seg.update(x, val);
        }
    }
}
