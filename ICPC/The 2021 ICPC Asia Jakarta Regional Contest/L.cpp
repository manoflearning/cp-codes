#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;
const int INF = 1e9 + 7;
const int sq = 337;

int flag;
struct Seg {
    vector<int> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, -INF);
        lazy.resize(flag << 1, -INF);
    }
    void modify(int l, int r, int val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] = val;
            propagate(n);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = max(t[n << 1], t[n << 1 | 1]);
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);

        if (r < nl || nr < l) return -INF;
        if (l <= nl && nr <= r) return t[n];
        
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
    void propagate(int n) {
        if (n < flag) {
            lazy[n << 1] = max(lazy[n << 1], lazy[n]);
            lazy[n << 1 | 1] = max(lazy[n << 1 | 1], lazy[n]);
        }
        t[n] = max(t[n], lazy[n]);
        lazy[n] = -INF;
    }
}seg[sq];

int N;
ll K, D;
ll a[MAXN];
int t[MAXN];
ll dp[101010];

void input() {
    cin >> N >> K >> D;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= N - 1; i++) cin >> t[i];
}

void naive() {
    for (int i = 1; i <= N; i++) dp[i] = -INF;

    for (int i = 1; i < N; i++) {
        if (i == 1) dp[i] = a[i];
        else {
            dp[i] += a[i];
            dp[i] += (N - min<ll>(N, (i + K - 1) / K * K)) / K * D;
        }

        for (int j = i + 1; j <= i + t[i]; j++) {
            ll res = dp[i] - (N - i) / K * D;
            dp[j] = max(dp[j], res);
        }
    }
}

void solve1() {
    for (int i = 0; i < K; i++) seg[i].build(N);

    for (int i = 1; i <= N; i++) dp[i] = -INF;

    for (int i = 1; i <= N; i++) {
        if (i == 1) dp[i] = a[i];
        else {
            for (int mod = 0; mod < K; mod++) {
                ll res = seg[mod].query(i, i);
                res += a[i];
                res += (N - min((ll)N, (i + K - 1) / K * K + mod) - 1) / K * D;
                dp[i] = max(dp[i], res);
            }
        }

        ll val = dp[i] - (N - i) / K * D;
        seg[i % K].modify(i + 1, i + t[i], val);
    }
}

void solve2() {
    
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    if (K <= sq) solve1();
    else solve2();

    cout << dp[N];
}