#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

const int MAX = 1000000;

char in_buf[MAX];
char out_buf[MAX];

inline char read_next()
{
	static int i = MAX;
	if (i == MAX)
	{
		fread(in_buf, 1, MAX, stdin);
		i = 0;
	}
	return in_buf[i++];
}

inline int read_int()
{
	int r = read_next() - '0';
	char ch;
	while ((ch = read_next()) >= '0' && ch <= '9')
		r = r * 10 + ch - '0';
	return r;
}

int n, m;
vt<int> adj[10101];
int b1, b2 = 1, vi[10101], fi[10101];

void input_fast() {
	n = read_int(), m = read_int();
	
	for (register int i = 0; i < m; i++) {
		int u = read_int(), v = read_int();
		adj[u].push_back(v);
	}
}

void dfs_iter(int v) {
	stack<int> stk;

	stk.push(v);
	vi[v] = 1;

	while (sz(stk)) {
		int v = stk.top(), isC = 0;

		for (register int i : adj[v]) {
			if (!vi[i]) {
				stk.push(i);
				vi[i] = isC = 1;
			}
			else if (!fi[i]) b2 = 0;
		}

		if (!isC) {
			fi[v] = 1;
			stk.pop();
		}
	}
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
	
	input_fast();

	for (register int i = 1; i <= n; i++) {
		if (!vi[i]) {
			b1 = 1;
			dfs_iter(i);
		}
	}

	cout << (b1 & b2 ? "No" : "Yes");

	return 0;
}