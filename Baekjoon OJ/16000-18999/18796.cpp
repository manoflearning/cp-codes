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

struct point {
    ll x, y;
};

int n, m;
vt<point> a, b;

void input() {
	cin >> n >> m;
    a.resize(n + 1);
    b.resize(m + 1);
	// x = index, y = A_i or B_i
    FOR(n + 1) {
		a[i].x = i;
		cin >> a[i].y;
	}
    FOR(m + 1) {
		b[i].x = i;
		cin >> b[i].y;
	}
}

ll ccw(point a, point b, point c) {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

void convexHull(vt<point>& p) { // monotone chain으로 불필요한 점 판별
	vt<int> st;
	st.push_back(0);
	st.push_back(1);

	// 아래껍질 구하기
	FOR(i, 2, sz(p)) {
		while (sz(st) >= 2) {
			int first = st.back();
			st.pop_back();
			int second = st.back();
			if (ccw(p[second], p[first], p[i]) > 0) { // 불필요한 점 판별
				st.push_back(first);
				break;
			}
		}
		st.push_back(i);
	}

	// st 배열에 불필요한 점들은 남아있지 않다. 따라서 남은 점들을 활용하여 문제를 해결할 수 있다.
	vt<point> x;
	EACH(i, st) x.push_back(p[i]);

	p = x;
}

ll f() {
	ll ret = 0;
	// 투 포인터
	for (int i = 0, j = 0; i < sz(a) - 1 || j < sz(b) - 1; ) {
		if (j == sz(b) - 1) ret += (a[i + 1].x - a[i].x) * b[j].y, i++;
		else if (i == sz(a) - 1) ret += (b[j + 1].x - b[j].x) * a[i].y, j++;
		else {
			ll la = a[i + 1].x - a[i].x, lb = b[j + 1].x - b[j].x;
			ll va = a[i + 1].y - a[i].y, vb = b[j + 1].y - b[j].y;

			// 그리디하게 경로 찾기
			// if (va * lb > vb * la), 왼쪽 아래 모서리를 지날 일이 없음
			// else, 오른쪽 위 모서리를 지날 일이 없음
			if (va * lb > vb * la) ret += (b[j + 1].x - b[j].x) * a[i].y, j++;
			else ret += (a[i + 1].x - a[i].x) * b[j].y, i++;
		}
	}
	// 문제의 정답 반환
	return ret;
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

	// 두 배열 a, b에서 불필요한 점들 제거
	convexHull(a);
	convexHull(b);

	// 투 포인터로 정답 계산해서 출력
	cout << f();

	return 0;
}