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

const int MAX = 1e5;

int N;
vector<int> p(MAX + 1, -1);

int find(int x) {
	if (p[x] < 0) return x;
	return p[x] = find(p[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	if (A > B) p[B] = A;
	else p[A] = B;
}

void solve() {
	int n; cin >> n;

	vt<int> a(n);
	FOR(n) cin >> a[i];

	int prv = 0;
	stack<int> st;
	FOR(n) {
		while (st.size() && find(st.top()) > a[i]) {
			merge(a[i], st.top());
			st.pop();
		}

		st.push(a[i]);
	}

	set<int> s;
	FOR(n) s.insert(find(a[i]));

	cout << sz(s);

	FOR(i, 1, n + 1) p[i] = -1;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	
	FOR(tc) {
		solve();
		cout << '\n';
	}

	return 0;
}
