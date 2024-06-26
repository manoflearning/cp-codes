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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll n, m;
ll a[101010], lb, mx;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        lb = max(lb, a[i]);
    }

    for (int i = 1; i <= n; i++) {
        ll x; cin >> x;
        x += a[i] * (a[i] - 1) / 2;

        __int128 l = 1, r = x;
        while (l < r) {
            __int128 mid = (l + r + 1) >> 1;
            if (mid * (mid - 1) / 2 <= x) l = mid;
            else r = mid - 1;
        }

        a[i] = l;
        mx = max(mx, a[i]);
    }

    __int128 l = lb - 1, r = mx + m;
    while (l < r) {
        __int128 mid = (l + r + 1) >> 1, res = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] >= mid) continue;
            res += mid - a[i];
        }
        if (res > m) r = mid - 1;
        else l = mid;
    }

    ll ans = l;
    if (ans == lb - 1) {
        cout << -1;
    }
    else cout << ans;

	return 0;
}