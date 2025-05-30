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

int h1, w1, h2, w2;
vector<string> a1, a2;

int f(int di, int dj) {
	int ret = 0;
	for (int i = 0; i < h1; i++) {
		for (int j = 0; j < w1; j++) {
			if (a1[i][j] == '.') continue;

			int ni = i + di, nj = j + dj;

			if (ni < 0 || h2 <= ni || nj < 0 || w2 <= nj) ret++;
			else if (a2[ni][nj] == '.') ret++;
		}
	}

	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> h1 >> w1;
	a1.resize(h1);
	for (auto& i : a1) cin >> i;
	cin >> h2 >> w2;
	a2.resize(h2);
	for (auto& i : a2) cin >> i;

	int ans = INF;
	for (int i = -10; i <= 10; i++) {
		for (int j = -10; j <= 10; j++) {
			ans = min(ans, f(i, j));
		}
	}

	cout << ans;

	return 0;
}