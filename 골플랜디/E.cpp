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

struct xy {
	ll x, y;
	bool operator<(const xy& rhs) const {
		if (x ^ rhs.x) return x < rhs.x;
		return y < rhs.y;
	}
};

int n;
xy a[101010];
ll r, d;
vt<int> idxx[10101010], idxy[10101010];
vt<int> adj[101010];

struct cmp1 {
	bool operator() (int u, int v) const {
		return a[u].x < a[v].x;
	}
};

void input() {
	cin >> n >> r;
	FOR(i, 1, n + 1) {
		cin >> a[i].x >> a[i].y;
	}
	cin >> d;
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	FOR(i, 1, n + 1) {
		if (a[i] < a[1]) swap(a[1], a[i]);
	}

	FOR(i, 1, n + 1) {
		idxx[a[i].x].push_back(i);
		idxy[a[i].y].push_back(i);
	}

	vt<pii> arr;
	FOR(i, r) {
		EACH(j, idxx[i]) 
			arr.push_back({ a[j].y, j });
	}
	
	FOR(i, r, 10101010) {
		sort(all(arr));
		
	}

	return 0;
}