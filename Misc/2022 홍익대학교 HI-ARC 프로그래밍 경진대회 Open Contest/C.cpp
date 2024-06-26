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

ll n, k, sy, sx;
bool b1 = 0, b2[8], b3 = 1;

bool check(ll y1, ll x1, ll y2, ll x2) {
    if (y1 == y2 || x1 == x2) return 1;
    if (abs(y1 - y2) == abs(x1 - x2)) return 1;
    return 0;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n >> k;

    cin >> sy >> sx;

    for (int i = 0; i < k; i++) {
        ll y, x;
        cin >> y >> x;

        for (int j = 0; j < 8; j++) {
            ll ny = sy + dy[j], nx = sx + dx[j];
            if (ny < 1 || n < ny || nx < 1 || n < nx) b2[j] = 1;
            if (check(ny, nx, y, x)) b2[j] = 1;
        }
        if (check(sy, sx, y, x)) b1 = 1;
    }

    for (int i =0 ; i < 8; i++) {
        if (!b2[i]) b3 = 0;
    }

    if (b1 && !b3) cout << "CHECK";
    else if (b1 && b3) cout << "CHECKMATE";
    else if (!b1 && b3) cout << "STALEMATE";
    else cout << "NONE";

	return 0;
}