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

int n, x;
int cnt[505050];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> x;
	for (int i = 0; i < n; i++) {
		int val; cin >> val;
		cnt[val]++;
	}
	
	for (int i = 1; i < x; i++) {
		cnt[i + 1] += cnt[i] / (i + 1);
		cnt[i] %= (i + 1);
		if (cnt[i]) {
			cout << "No\n";
			return 0;
		}
	}

	if (cnt[x]) cout << "Yes";
	else cout << "No";
	
	return 0;
}