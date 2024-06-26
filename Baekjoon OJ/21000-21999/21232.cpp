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

int n, deg[101010], b[1010][1010], v[1010][1010];
vt<pii> a, c;
set<pii> s;

pii find(int idx) {
    int y = a[idx].fr, x = a[idx].sc;
    FOR(4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || nx < 0) continue;
        if (!v[ny][nx]) return { ny, nx };
    }
}

void f(int x) {
    if (deg[x] == 3) {
        c[x] = find(x);
        s.insert({ c[x].fr, c[x].sc });
    }
    if (deg[x] == 4) {
        s.erase({ c[x].fr, c[x].sc });
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

	cin >> n;

    a.resize(n + 1);
    c.resize(n + 1);
    FOR(i, 1, n + 1) {
        int y, x;
        cin >> y >> x;
        a[i] = { y, x };
        b[y][x] = i;
    }

    set<pii> s;
    FOR(i, 1, n + 1) {
        int y = a[i].fr, x = a[i].sc;

        v[y][x] = 1;

        FOR(j, 4) {
            int ny = y + dy[j], nx = x + dx[j];
            if (ny < 0 || nx < 0) continue;
            
            int idx = b[ny][nx];
            if (idx) {
                deg[idx]++;
                f(idx);
            }
        }
        f(i);

        cout << sz(s) << '\n';
    }

	return 0;
}