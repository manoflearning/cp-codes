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

void test() {
    int x = 1000;
    map<int, int> vi;
    for (int i = 1; i <= x; i++) {
        for (int j = i; j <= x; j++) {
            vi[i * j] = 1;
        }
    }
    
    for (int i = 1; i <= x * x; i++) {
        //cout << i << ' ' << vi[i] << '\n';
        
        //cout << vi[i] << ' ';
        //if (i % x == 0) cout << '\n';

        //if (!vi[i]) cout << i << '\n';
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    //test();

	ll n, m;
    cin >> n >> m;

    if (m <= n) { cout << m; return 0; }
    if ((__int128_t)n * n < m) { cout << -1; return 0; }
    
    // Now n < m AND m <= n * n

    ll ans = 1e18;
    for (ll i = 1; i <= n; i++) {
        ll j = (m + i - 1) / i;
        if (j < i) break;
        if (j <= n) ans = min(ans, i * j);
    }

    cout << ans;

	return 0;
}