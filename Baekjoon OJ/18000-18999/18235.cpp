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

int n, sx, sy;
int p2[22];
int vix[22][505050], viy[22][505050];

void dfsx(int v, int day) {
    vix[day][v] = 1;

    if (1 <= v - p2[day] && !vix[day + 1][v - p2[day]]) dfsx(v - p2[day], day + 1);
    if (v + p2[day] <= n && !vix[day + 1][v + p2[day]]) dfsx(v + p2[day], day + 1);
}

int dfsy(int v, int day) {
    viy[day][v] = 1;
    if (vix[day][v]) return day;

    int ret = INF;
    if (1 <= v - p2[day] && !viy[day + 1][v - p2[day]]) ret = min(ret, dfsy(v - p2[day], day + 1));
    if (v + p2[day] <= n && !viy[day + 1][v + p2[day]]) ret = min(ret, dfsy(v + p2[day], day + 1));
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
	
    p2[0] = 1;
    FOR(i, 1, 22) p2[i] = 2 * p2[i - 1];

	cin >> n >> sx >> sy;

    dfsx(sx, 0);

    int res = dfsy(sy, 0);
    if (res == INF) cout << -1;
    else cout << res;

	return 0;
}