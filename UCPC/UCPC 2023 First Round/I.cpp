#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second

const ll INF = 1e18;

int flag;
struct Seg {
    vector<ll> t, lazy;
    void build(int n) {
        t.clear();
        lazy.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);
        lazy.resize(2 * flag);
    }
    void add(int l, int r, ll val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] += val;
            propagate(n, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        add(l, r, val, n << 1, nl, mid);
        add(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = min(t[n << 1], t[n << 1 | 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (r < nl || nr < l) return INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
    void propagate(int n, int nl, int nr) {
        if (lazy[n] != 0) {
            if (n < flag) {
                lazy[n << 1] += lazy[n];
                lazy[n << 1 | 1] += lazy[n];
            }
            t[n] += lazy[n];
            lazy[n] = 0;
        }
    }
}seg;

int N, K;
int a[505050];

void input() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> a[i];
}

ll solvelr() {
    ll ret = -INF;

    seg.build(N);
    seg.add(1, 1, a[1]);
    for (int i = 2; i <= N; i++) {
        seg.add(1, i - 1, K);
        ret = max(ret, a[i] - seg.query(1, i - 1));
        seg.add(i, i, a[i]);
    }

    return ret;
}
ll solverl() {
    ll ret = -INF;

    seg.build(N);
    seg.add(N, N, a[N]);
    for (int i = N - 1; i >= 1; i--) {
        seg.add(i + 1, N, K);
        ret = max(ret, a[i] - seg.query(i + 1, N));
        seg.add(i, i, a[i]);
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    ll ans = solvelr();
    ans = max(ans, solverl());
    
    cout << ans;
}