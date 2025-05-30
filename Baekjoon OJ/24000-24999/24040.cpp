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

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
    while (tc--) {
        ll n; cin >> n;
        // x * y = n AND (x + y) = 0 (mod 3)
        // (x = 3p AND y = 3q) -> n = 9pq
        // or (x = 3p + 1 AND y = 3q + 2) -> n = 9pq + 6p + 3q + 2

        if (n % 9 == 0) cout << "TAK";
        else if ((n - 2) % 3 == 0) cout << "TAK";
        else cout << "NIE";
        cout << '\n';
    }

	return 0;
}