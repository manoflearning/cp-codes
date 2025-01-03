// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = 2020, MAXV = 101010;

int n, k, d;
int a[MAXN], v[MAXV];
ll ans = 0;

void init() {
    ans = 0;
}

void input() {
    cin >> n >> k >> d;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= k; i++) cin >> v[i];
}

void solve() {
    vector<int> psum(4040);
    
    for (int i = 1; i <= n; i++) {
        if (i < a[i]) continue;

        int val = a[i];
        int lb = -1, ub = 2 * n; // [lb, ub]

        if (val == i) lb = 0;

        for (int j = 1; j <= 2 * n; j++) {
            int vnow = v[(j - 1) % k + 1];

            if (i <= vnow) val++;

            if (val == i && lb == -1) lb = j;
            if (val == i + 1) { ub = j - 1; break; }
        }

        if (lb != -1) {
            psum[lb]++;
            psum[ub + 1]--;
        }
    }

    ans = 0;
    for (int i = 0; i <= min(2 * n, d - 1); i++) {
        if (i > 0) psum[i] += psum[i - 1];

        ll res = psum[i];
        res += (d - i - 1) / 2;
        ans = max(ans, res);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        solve();

        cout << ans << '\n';
    }
}