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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll cnt[101010];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int d, t;
        cin >> d >> t;
        cnt[d - 1] += t;
    }

    ll ans = 0;
    ll A = 0, B = 0;
    for (int d = 0; d < 100000; d++) {
        if (d % 7 <= 4) A++;
        B++;

        if (A + B < cnt[d]) {
            cout << -1;
            return 0;
        }

        ll tmp = cnt[d];
        cnt[d] -= min(tmp, A);
        A -= min(tmp, A);

        tmp = cnt[d];
        ans += min(tmp, B);
        cnt[d] -= min(tmp, B);
        B -= min(tmp, B);
    }

    cout << ans;

	return 0;
}