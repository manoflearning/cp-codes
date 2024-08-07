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

const int MAXN = 252525;

int n;
ll S;
ll a[MAXN], psum[MAXN];

void input() {
    cin >> n >> S;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        psum[i] = a[i] + psum[i - 1];
    }
}

ll sum(ll l, ll r) { return psum[r] - psum[l - 1]; }

ll ans = 0, res = 1;
int cnt[MAXN], p = 1;

void solve() {
    // base case
    cnt[1] = 1;
    ans += res;

    // inductive step
    for (int i = 2; i <= n; i++) {
        while (S < sum(p, i)) {
            cnt[i] += cnt[p];
            res += cnt[p];
            p++;
        }
        cnt[i]++;
        res++;
        ans += res;
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

    solve();

    cout << ans;
}