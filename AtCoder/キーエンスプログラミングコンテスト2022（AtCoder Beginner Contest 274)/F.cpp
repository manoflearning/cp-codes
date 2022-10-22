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

#define pdd pair<double, double>

struct Fish {
	int w, x, v;
};

int n, len;
vt<Fish> fishes;
map<pair<pdd, pdd>, int> mp;

int f(double tl, double tr, double dl, double dr) {

}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> len;
	fishes.resize(n);
	EACH(i, fishes)
		cin >> i.w >> i.x >> i.v;

	int ans = 0;
	FOR(n) {
		FOR(j, i + 1, n) {
			int x1 = fishes[i].x, v1 = fishes[i].v;
			int x2 = fishes[j].x, v2 = fishes[j].v;
			
			double l = 0, r = INF;
			while (r - l > EPS) {
				double m1 = (2 * l + r) / 3;
				double m2 = (l + 2 * r) / 3;
				
				double res1 = abs((x1 + m1 * v1) - (x2 + m1 * v2));
				double res2 = abs((x1 + m2 * v1) - (x2 + m2 * v2));

				if (res1 > res2) l = m1;
				else r = m2;
			}
			
			
		}
	}

	return 0;
}