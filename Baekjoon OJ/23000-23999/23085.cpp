#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define vt vector
#define pb push_back
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, k, cnt0, cnt1;
int dist[3005];

void init() {
	memset(dist, -1, sizeof(dist));
}

void input() {
	cin >> n >> k;
	string s; cin >> s;
	EACH(c, s) {
		if (c == 'H') cnt0++;
		else cnt1++;
	}
}

void f() {
	queue<int> q;
	
	q.push(cnt0);
	dist[cnt0] = 0;

	while (q.size()) {
		int a = q.front(), b = n - a;
		q.pop();

		FOR(k + 1) {
			int m1 = i, m2 = k - i;

			if (a < m1 || b < m2) continue;
			if (dist[a - m1 + m2] != -1) continue;

			dist[a - m1 + m2] = dist[a] + 1;
			q.push(a - m1 + m2);
		}
	}
}

void solve() {
	init();

	input();

	f();

	cout << dist[0];
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}
