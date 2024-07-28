#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 1e9 + 7;
const int N = 101010;

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, ll val) {
        p += flag - 1;
        for (t[p] = (t[p] + val) % MOD; p > 1; p >>= 1)
            t[p >> 1] = (t[p] + t[p ^ 1]) % MOD;
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return (query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr)) % MOD;
    }
}seg[12];

int n, a[N];
ll dp[N][12];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // vector<int> ord(n);
    // iota(all(ord), 1);

    // sort(all(ord), [&](int i, int j) {
    //     return a[i] < a[j];
    // });

    for (int i = 1; i <= 11; i++) seg[i].build(n);

    for (int i = 1; i <= n; i++) {
        seg[1].add(a[i], 1);
        for (int j = 2; j <= 11; j++) {
            ll cnt = seg[j - 1].query(1, a[i] - 1);
            seg[j].add(a[i], cnt);
        }
    }

    cout << seg[11].query(1, n);
}