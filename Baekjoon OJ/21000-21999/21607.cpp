// f * g = 2(4x^3 - 3x)^2 - 1
// = 32x^6 - 48x^4 + 18x^2 - 1
// g * f = 4(2x^2 - 1)^3 - 3(2x^2 - 1)
// = 32x^6 - 48x^4 + 18x^2 - 1
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 100003;
const int MAXD = 20;
const int MAXN = 505050;

struct Fenwick { // 1-indexed
    int flag;
    vector<ll> t;
    void build(int N) {
        flag = N;
        t.resize(flag + 1);
    }
    void modify(int l, int r) { // add a val to all elements in interval [l, r]
        for (; l <= flag; l += l & -l) t[l]++;
        for (r++; r<= flag; r += r & -r) t[r]--;
    }
    ll query(int x) {
        ll ret = 0;
        for (; x; x ^= x & -x) ret += t[x];
        return ret;
    }
} fw1, fw2;

int n, q;
vector<ll> a;
ll sp1[MOD][MAXD + 1], sp2[MOD][MAXD + 1];

void input() {
    cin >> n >> q;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void buildSP() {
    for (ll i = 0; i < MOD; i++) {
        sp1[i][0] = (2 * i * i + MOD - 1) % MOD;
        sp2[i][0] = (4 * i * i * i - 3 * i) % MOD;
    }
    for (int d = 1; d <= MAXD; d++) {
        for (int i = 0; i < MOD; i++) {
            sp1[i][d] = sp1[sp1[i][d - 1]][d - 1];
            sp2[i][d] = sp2[sp2[i][d - 1]][d - 1];
        }
    }
}

ll query(int idx, ll cnt1, ll cnt2) {
    ll ret = a[idx];
    for (int d = 0; d <= MAXD; d++) {
        if ((1 << d) & cnt1) ret = sp1[ret][d];
    }
    for (int d = 0; d <= MAXD; d++) {
        if ((1 << d) & cnt2) ret = sp2[ret][d];
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    fw1.build(n);
    fw2.build(n);

    buildSP();

    while (q--) {
        int op;
        cin >> op;
        if (op == 1 || op == 2) {
            int l, r;
            cin >> l >> r;
            if (op == 1) fw1.modify(l, r);
            if (op == 2) fw2.modify(l, r);
        }
        if (op == 3) {
            int x; cin >> x;
            cout << query(x, fw1.query(x), fw2.query(x)) << '\n';
        }
    }
}