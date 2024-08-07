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

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	string a, b;
	cin >> a >> b;

	int l = sz(b), r = sz(a) - sz(b) - 1;

	for (int i = 0; i < sz(b); i++) {
		if (a[i] == '?' || b[i] == '?') continue;
		if (a[i] != b[i]) { l = i; break; }
	}

	for (int i = sz(a) - 1; i >= sz(a) - sz(b); i--) {
		if (a[i] == '?' || b[i - sz(a) + sz(b)] == '?') continue;
		if (a[i] != b[i - sz(a) + sz(b)]) { r = i; break; }
	}
	//cout << l << ' ' << r << '\n';
	for (int x = 0; x <= sz(b); x++) {
		int nl = x - 1, nr = sz(a) - (sz(b) - x);
		//cout << nl << ' ' << nr << ' ';
		if (l <= nl || nr <= r) cout << "No\n";
		else cout << "Yes\n";
	}

	return 0;
}