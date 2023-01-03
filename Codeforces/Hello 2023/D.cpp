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

int n, m;
ll a[202020], b[202020], x[202020], cnt[606060];
vector<ll> c;

void input() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> x[i];
}

bool BbiggerthanA() {
	for (int i = 1; i <= n; i++) {
		if (a[i] < b[i]) return 1;
	}
	return 0;
}

void cc() {
	c.push_back(-INF);
	for (int i = 1; i <= n; i++) {
		c.push_back(a[i]);
		c.push_back(b[i]);
	}
	for (int i = 1; i <= m; i++)
		c.push_back(x[i]);
	
	sort(all(c));
	c.erase(unique(all(c)), c.end());

	for (int i = 1; i <= n; i++) {
		a[i] = lower_bound(all(c), a[i]) - c.begin();
		b[i] = lower_bound(all(c), b[i]) - c.begin();
	}
	for (int i = 1; i <= m; i++) {
		x[i] = lower_bound(all(c), x[i]) - c.begin();
		cnt[x[i]]++;
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
		input();

		if (BbiggerthanA()) {
			cout << "NO\n";
			continue;
		}

		cc();

		stack<int> stk;
		for (int i = 1; i <= n; i++) {
			while (sz(stk) && stk.top() < b[i]) stk.pop();

			if (sz(stk) && stk.top() == b[i]) continue;
			if (a[i] == b[i]) continue;
			
			stk.push(b[i]);
			cnt[b[i]]--;
		}

		int ans = 1;
		for (int i = 1; i < sz(c); i++) {
			if (cnt[i] < 0) ans = 0;
		}

		cout << (ans ? "YES" : "NO") << '\n';

		// init
		for (int i = 1; i < sz(c); i++) cnt[i] = 0;
		c.clear();
	}

	return 0;
}