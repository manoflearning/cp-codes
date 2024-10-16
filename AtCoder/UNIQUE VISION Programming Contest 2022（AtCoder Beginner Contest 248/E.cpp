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

int n, k;
vt<point> a;
int visited[299 * 300 + 299];

//ccw 알고리즘
ll ccw(point a, point b, point c) {
	//양수를 반환하면 ccw, 음수를 반환하면 cw, 0을 반환하면 a, b, c는 한 직선 위에 있다.
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
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

	cin >> n >> k;

    a.resize(n);
    EACH(i, a) cin >> i.x >> i.y;

    if (k == 1) {
        cout << "Infinity";
        return 0;
    }

    ll ans = 0;

    FOR(i, n) {
        FOR(j, i + 1, n) {
            if (visited[i * 300 + j]) continue;

            int cnt = 2;

            set<int> s;
            s.insert(i);
            s.insert(j);

            FOR(k, n) {
                if (k == i || k == j) continue;
                if (ccw(a[i], a[j], a[k]) == 0) {
                    cnt++;
                    s.insert(k);
                }
            }
            
            if (cnt >= k) ans++;
            
            EACH(x1, s) {
                EACH(x2, s) {
                    if (x1 == x2) continue;
                    visited[x1 * 300 + x2] = 1;
                }
            }
        }
    }

    cout << ans;

	return 0;
}