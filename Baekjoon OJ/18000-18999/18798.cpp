#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 252525;
const int MAXD = 29;

int flag;
struct Seg {
    vector<int> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1, -1);
    }
    void modify(int l, int r, int val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] = val;
            propagate(n, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
    void propagate(int n, int nl, int nr) {
        if (lazy[n] != -1) {
            if (n < flag) {
                lazy[n << 1] = lazy[n];
                lazy[n << 1 | 1] = lazy[n];
            }
            t[n] = lazy[n];
            lazy[n] = -1;
        }
    }
}seg;

struct Fenwick {
    int flag;
    vector<int> t;
    void build(int N) {
        flag = N;
        t.resize(flag + 1);
    }
    void modify(int l, int r) {
        for (; l <= flag; l += l & -l) t[l]++;
        for (r++; r <= flag; r += r & -r) t[r]--;
    }
    int query(int x) {
        int ret = 0;
        for (; x; x ^= x & -x) ret += t[x];
        return ret;
    }
}fw;

int N, K;
vector<int> A(MAXN), cntBit(MAXN);
set<int> byBit[MAXD + 1];

void input() {
    cin >> N >> K;
    fw.build(N);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        if ((K & A[i]) == A[i]) A[i] = K - A[i];
        else { A[i] = 0; fw.modify(i, i); }
    }
}

void updateBit(int l, int r, int x) {
    for (int d = 0; d <= MAXD; d++) {
        if (!((1 << d) & x)) continue;

        auto it = byBit[d].lower_bound(l);
        vector<int> del;
        while (it != byBit[d].end() && *it <= r) { del.push_back(*it); it++; }
        for (auto& i : del) {
            byBit[d].erase(i);
            cntBit[i]--;
            if (cntBit[i]) continue;
            if (fw.query(i)) continue;
            seg.modify(i, i, 1); 
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    seg.build(N);

    for (int i = 1; i <= N; i++) {
        for (int d = 0; d <= MAXD; d++) {
            if ((1 << d) & A[i]) {
                byBit[d].insert(i);
                cntBit[i]++;
            }
        }
        if (cntBit[i]) continue;
        if (fw.query(i)) continue;
        seg.modify(i, i, 1); 
    }

    int q; cin >> q;
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        
        if (op == 1) {
            int x; cin >> x;
            if ((x & K) == x) updateBit(l, r, x);
            else {
                seg.modify(l, r, 0);
                fw.modify(l, r);
            }
        }
        if (op == 2) cout << seg.query(l, r) << '\n';
    }
}
