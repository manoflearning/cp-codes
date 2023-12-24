// a + (b * c) = a^2 + ab + ac + bc
// iff a * (a + b + c - 1) = 0

// if a = 0 => YES
// else if a != 0 and c = 1 - a - b => YES

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

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;

    ll ans = 0;

    // if a = 0
    ans += (2 * n + 1) * (2 * n + 1);

    // if a != 0 and c = 1 - a - b
    for (ll a = -n; a <= n; a++) {
        if (a == 0) continue;
        for (ll b = -n; b <= n; b++) {
            ll c = 1 - a - b;
            if (-n <= c && c <= n) ans++;
        }
    }

    cout << ans;
}