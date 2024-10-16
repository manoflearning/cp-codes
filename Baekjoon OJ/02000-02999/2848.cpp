#define _USE_MATH_DEFINES
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

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
vt<string> s;
vt<int> adj[26];
int ex[26], indeg[26], vi[26];

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	cin >> n;
	s.resize(n);
	EACH(i, s) cin >> i;

	EACH(i, s) {
		EACH(j, i) ex[j - 'a'] = 1;
	}

	int isM = 0, isI = 0;

	FOR(i, n) {
		FOR(j, i + 1, n) {
			FOR(k, min(sz(s[i]), sz(s[j]))) {
				int v = s[i][k] - 'a', u = s[j][k] - 'a';
				if (v != u) {
					adj[v].push_back(u);
					indeg[u]++;
					break;
				}

				if (k == min(sz(s[i]), sz(s[j])) - 1 && sz(s[i]) > sz(s[j])) isI = 1;
			}
		}
	}

	vt<int> ans;
	queue<int> q;

	FOR(26) {
		if (ex[i] && !indeg[i]) {
			q.push(i);
			vi[i] = 1;
		}
	}

	while (sz(q)) {
		if (sz(q) >= 2) isM = 1;
		
		int v = q.front();
		q.pop();

		ans.push_back(v);

		EACH(i, adj[v]) {
			indeg[i]--;
			if (!indeg[i]) {
				q.push(i);
				vi[i] = 1;
			}
		}
	}

	FOR(26) {
		if (ex[i] && !vi[i]) isI = 1;
	}

	if (isI) cout << '!';
	else if (isM) cout << '?';
	else {
		EACH(i, ans) cout << char(i + 'a');
	}

	return 0;
}