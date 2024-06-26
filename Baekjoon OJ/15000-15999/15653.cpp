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

struct yx {
	int y, x;
};

int n, m, dist[10005];
vt<string> a;

void input() {
	cin >> n >> m;
	a.resize(n);
	EACH(i, a) cin >> i;
}

int Hash(const vt<string>& a) {
	yx r = { 0, 0 }, b = { 0, 0 };
	FOR(y, n) {
		FOR(x, m) {
			if (a[y][x] == 'R') r.y = y, r.x = x;
			if (a[y][x] == 'B') b.y = y, b.x = x;
		}
	}

	return 100 * (10 * r.y + r.x) + (10 * b.y + b.x);
}

int isEnd(const vt<string>& a) {
	int isR = 0, isB = 0;
	FOR(y, n) {
		FOR(x, m) {
			if (a[y][x] == 'R') isR = 1;
			if (a[y][x] == 'B') isB = 1;
		}
	}
	return (!isR && isB);
}

int impos(const vt<string>& a) {
	int isB = 1;
	FOR(y, n) {
		FOR(x, m) {
			if (a[y][x] == 'B') isB = 0;
		}
	}
	return isB;
}

yx find(char c, const vt<string>& a) {
	FOR(y, n) {
		FOR(x, m) {
			if (a[y][x] == c) return { y, x };
		}
	}
}

void movy(yx i, int d, vt<string>& a) {
	FOR(y, i.y + d, d == 1 ? n : -1, d) {
		if (a[y][i.x] == 'O') {
			a[i.y][i.x] = '.';
			break;
		}
		if (a[y][i.x] != '.') {
			a[y - d][i.x] = a[i.y][i.x];
			if (y - d != i.y) a[i.y][i.x] = '.';
			break;
		}
	}
}

void movx(yx i, int d, vt<string>& a) {
	FOR(x, i.x + d, d == 1 ? m : -1, d) {
		if (a[i.y][x] == 'O') {
			a[i.y][i.x] = '.';
			break;
		}
		if (a[i.y][x] != '.') {
			a[i.y][x - d] = a[i.y][i.x];
			if (x - d != i.x) a[i.y][i.x] = '.';
			break;
		}
	}
}

vt<string> f0(vt<string> a) { // 상
	yx r = find('R', a), b = find('B', a);
	if (r.y <= b.y) {
		movy(r, -1, a);
		movy(b, -1, a);
	}
	else {
		movy(b, -1, a);
		movy(r, -1, a);
	}
	return a;
}
vt<string> f1(vt<string> a) { // 하
	yx r = find('R', a), b = find('B', a);
	if (r.y <= b.y) {
		movy(b, 1, a);
		movy(r, 1, a);
	}
	else {
		movy(r, 1, a);
		movy(b, 1, a);
	}
	return a;
}
vt<string> f2(vt<string> a) { // 좌
	yx r = find('R', a), b = find('B', a);
	if (r.x <= b.x) {
		movx(r, -1, a);
		movx(b, -1, a);
	}
	else {
		movx(b, -1, a);
		movx(r, -1, a);
	}
	return a;
}
vt<string> f3(vt<string> a) { // 우
	yx r = find('R', a), b = find('B', a);
	if (r.x <= b.x) {
		movx(b, 1, a);
		movx(r, 1, a);
	}
	else {
		movx(r, 1, a);
		movx(b, 1, a);
	}
	return a;
}

int bfs(vt<string> st) {
	memset(dist, -1, sizeof(dist));

	queue<vt<string>> q;

	q.push(st);
	dist[Hash(st)] = 0;

	while (q.size()) {
		vt<string> v = q.front();
		q.pop();
		
		if (isEnd(v)) return dist[Hash(v)];
		if (impos(v)) continue;
		
		vt<string> u0 = f0(v), u1 = f1(v), u2 = f2(v), u3 = f3(v);
		
		if (dist[Hash(u0)] == -1) {
			dist[Hash(u0)] = dist[Hash(v)] + 1;
			q.push(u0);
		}
		if (dist[Hash(u1)] == -1) {
			dist[Hash(u1)] = dist[Hash(v)] + 1;
			q.push(u1);
		}
		if (dist[Hash(u2)] == -1) {
			dist[Hash(u2)] = dist[Hash(v)] + 1;
			q.push(u2);
		}
		if (dist[Hash(u3)] == -1) {
			dist[Hash(u3)] = dist[Hash(v)] + 1;
			q.push(u3);
		}
	}

	return INF;
}

void solve() {
	input();

	int ans = bfs(a);

	if (ans == INF) cout << -1;
	else cout << ans;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}
