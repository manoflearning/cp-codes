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

ll h, w;
int n;
ll cnt[33];
ll bars[33];

void f(ll x, ll y, ll cnt) {
    if (x <= 0 || y <= 0) return;
    
    if (x > y) swap(x, y);

    ll base = 1, b = 0;
    for (base = 1, b = 0; base <= min(x, y); base <<= 1, b++);
    base >>= 1; b--;

    if (b < 0) return;
    bars[b] += cnt * (y / base);
    bars[b] %= MOD;

    f(x - base, base, cnt * (y / base) % MOD);
    f(x, y % base, cnt);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> h >> w >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    f(h, w, 1);

    for (int i = 30; i >= 0; i--) {
        if (bars[i] < cnt[i]) { cout << "No"; return 0; }
        bars[i] -= cnt[i];
        if (bars[i] > 0 && i - 1 >= 0) {
            bars[i - 1] += 4 * bars[i];
            bars[i - 1] = min(1000ll, bars[i - 1]);
        }
    }

    cout << "Yes";
}