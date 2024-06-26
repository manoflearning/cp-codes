#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 505050;
const ll INF = 1e18;

int n;
ll p, a[MAXN];

void input() {
    cin >> n >> p;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

int st[MAXN];
void getStartIndex() {
    priority_queue<pll> pq;
    st[1] = 1;
    pq.push({ a[1], -1 });
    for (int i = 2; i <= n; i++) {
        st[i] = st[i - 1];
        pq.push({ a[i], -i });
        while (1) {
            ll x = pq.top().fr, y = -pq.top().sc;
            if (y < st[i]) { pq.pop(); continue; }
            if (p - (i - st[i]) >= x) break;
            while (p - (i - st[i]) < x) st[i]++;
        }
    }
}

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, INF);
    }
    void modify(int p, ll val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = min(t[p], t[p ^ 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg;

ll dp[MAXN];

inline int add(int idx) { return n - idx - 1; }
inline int del(int idx) { return idx - n; }

int stk[MAXN];
void f() {
    int top = 1;
    seg.build(n + 1);

    // base case
    dp[0] = 0;
    seg.modify(top, a[1] + dp[0] + add(0));

    // inductive step
    for (int i = 1; i <= n; i++) { // O(nlogn)
        while (top > 1 && a[stk[top]] <= a[i]) top--;
        stk[++top] = i;

        ll val = a[i] + dp[stk[top - 1]] + add(stk[top - 1]);
        seg.modify(top, val);

        int l = lower_bound(stk + 1, stk + top + 1, st[i]) - stk + 1;
        int r = top;
        dp[i] = seg.query(l, r) + del(i);
        
        int idx = *lower_bound(stk + 1, stk + top + 1, st[i]);
        dp[i] = min(dp[i], a[idx] + dp[st[i] - 1] + i - st[i]);
    }
}

// void naive() {
//     dp[1] = a[1];
//     for (int i = 2; i <= n; i++) {
//         ll mx = a[i];
//         dp[i] = mx + dp[i - 1];
//         for (int j = i - 1; j >= 1; j--) {
//             mx = max(mx, a[j]);
//             if (mx > p - (i - j)) break;
//             dp[i] = min(dp[i], i - j + mx + dp[j - 1]);
//         }
//     }
// }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    getStartIndex();

    // naive();

    f();

    cout << dp[n];
}