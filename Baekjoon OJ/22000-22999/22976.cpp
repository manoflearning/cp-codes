#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

struct Node {
    ll a, b; // ax + b
    Node operator+(const Node& rhs) const {
        // rhs.a(ax + b) + rhs.b
        // a * rhs.a * x + rhs.a * b + rhs.b
        Node ret;
        ret.a = a * rhs.a % MOD;
        ret.b = (b * rhs.a + rhs.b) % MOD;;
        return ret;
    }
};

int flag;
struct Seg {
    vector<Node> t;
    void build(int N) {
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1);
        for (int i = flag; i < flag + N; i++) {
            char op; ll x;
            cin >> op >> x;
            if (op == '+') { t[i].a = 1; t[i].b = x; }
            if (op == '*') { t[i].a = x; t[i].b = 0; }
        }
        for (int i = flag + N; i < 2 * flag; i++) t[i] = { 1, 0 };
        for (int i = flag - 1; i >= 1; i--) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }
    void modify(int p, Node val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1) {
            if (p & 1) t[p >> 1] = t[p ^ 1] + t[p];
            else t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    ll query() {
        return t[1].b % MOD;
    }
}seg;

int n, q;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> q;
    seg.build(n);
    
    for (int i = 0; i < q; i++) {
        int p; char op; int x;
        cin >> p >> op >> x;
        Node res;
        if (op == '+') { res.a = 1; res.b = x; }
        if (op == '*') { res.a = x; res.b = 0; }
        seg.modify(p, res);
        cout << seg.query() << '\n';
    }
}