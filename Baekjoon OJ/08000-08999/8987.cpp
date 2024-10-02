#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 303030;
const ll INF = 1e18;

int flag;
struct Seg {
    vector<ll> t;
    void build() {
        for (flag = 1; flag < (MAXN >> 1); flag <<= 1);
        t.resize(flag << 1, INF);
    }
    void modify(int p, ll val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = min(t[p], t[p ^ 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg;

int n;
ll xs[MAXN >> 1], ys[MAXN >> 1], xe[MAXN >> 1], ye[MAXN >> 1];
unordered_map<ll, vector<int>> mp;
int k;

void input() {
    cin >> n; n >>= 1;
    for (int i = 1; i <= n; i++) {
        cin >> xs[i] >> ys[i];
        cin >> xe[i] >> ye[i];
        mp[ye[i]].push_back(i);
        assert(xs[i] == xe[i]);
    }
    cin >> k;
}

priority_queue<ll> pq;

ll f(int l, int r, ll prv_h) {
    if (l >= r) return -INF;

    ll now_h = seg.query(l, r - 1);

    auto& arr = mp[now_h];
    
    int lb = lower_bound(all(arr), l) - arr.begin();
    int ub = lower_bound(all(arr), r) - arr.begin();

    assert(lb < ub);

    vector<ll> res;
    for (int i = lb; i < ub; i++) {
        if (i == lb) res.push_back(f(l, arr[i], now_h));
        if (i + 1 == ub) res.push_back(f(arr[i] + 1, r, now_h));
        
        if (i + 2 <= ub) {
            res.push_back(f(arr[i] + 1, arr[i + 1], now_h));
        }
    }

    sort(all(res));

    ll now_area = (now_h - prv_h) * (xs[r] - xs[l]);
    if (res.back() == -INF) return now_area;

    for (int i = 0; i + 1 < sz(res); i++) {
        if (res[i] != -INF) pq.push(res[i]);
    }
    return now_area + res.back();
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    seg.build();
    for (int i = 1; i <= n - 1; i++) {
        seg.modify(i, ye[i]);
    }

    pq.push(f(1, n, 0));

    ll ans = 0;
    while (!pq.empty() && k--) {
        ans += pq.top();
        pq.pop();
    }

    cout << ans;
}
