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
const int dy[] = { 1, 1, -1, -1 };
const int dx[] = { 1, -1, 1, -1 };

struct yx {
    int y, x;
};

int n, m;
vt<string> a;
int dist[505][505];

void init() {
    FOR(505) FOR(j, 505) dist[i][j] = INF;
}

int add(int ny, int nx, int i) {
    if (i == 0) {
        if (a[ny - 1][nx - 1] == '\\') return 0;
        else return 1;
    }
    else if (i == 1) {
        if (a[ny - 1][nx] == '\\') return 1;
        else return 0;
    }
    else if (i == 2) {
        if (a[ny][nx - 1] == '\\') return 1;
        else return 0;
    }
    else if (i == 3) {
        if (a[ny][nx] == '\\') return 0;
        else return 1;
    }
    return 0;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    init();

	cin >> n >> m;
    a.resize(n);
    EACH(i, a) cin >> i;

    if (abs(n - m) & 1) {
        cout << "NO SOLUTION";
        return 0;
    }

    deque<yx> dq;
    dq.push_back({ 0, 0 });
    dist[0][0] = 0;

    while (sz(dq)) {
        int y = dq.front().y, x = dq.front().x;
        ll d = dist[y][x];
        dq.pop_front();

        FOR(i, 4) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 0 || n < ny || nx < 0 || m < nx) continue;
            ll nd = add(ny, nx, i);
            if (dist[ny][nx] <= d + nd) continue;
            
            if (nd) dq.push_back({ ny, nx });
            else dq.push_front({ ny, nx });
            dist[ny][nx] = d + nd;
        }
    }

    cout << dist[n][m];

	return 0;
}