//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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

int n, k;
ll p2[101010];
vector<ll> cnt(101010);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    p2[0] = 1;
    for (int i = 1; i < 101010; i++) {
        p2[i] = 2 * p2[i - 1] % MOD;
    }

    // input
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x % k]++;
    }

    // solve
    ll ans = 1;
    for (int i = 0; i <= (k - i); i++) {
        int x = i, y = k - i;
        int xcnt = cnt[x], ycnt = cnt[y];
        if ((x + x) % k) {
            ans = ans * ((p2[xcnt] + p2[ycnt] + MOD - 1) % MOD) % MOD;
        }
        else {
            ans = ans * (xcnt + 1) % MOD;
        }
    }

    ans = (ans + MOD - (n + 1)) % MOD;

    cout << ans;
}