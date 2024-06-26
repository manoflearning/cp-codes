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

int n, m;
vt<string> a;
vt<vt<int>> dist;
vt<vt<pii>> prv;

void init() {
    n = m = 0;
    a.clear();
    dist.clear();
    prv.clear();
}

void input() {
    cin >> n >> m;

    a.resize(n);
    EACH(i, a) cin >> i;
}

bool near(int y, int x) {
    FOR(4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;

        if (a[ny][nx] == '#') return 1;
    }
    return 0;
}

void bfs01() {
    dist.resize(n, vt<int>(m, INF));
    prv.resize(n, vt<pii>(m, { -1, -1 }));

    deque<pair<pii, int>> dq;
    FOR(n) {
        if (near(i, 0)) continue;
        
        if (a[i][0] == '#') {
            dq.push_front({ { i, 0 }, 0 });
            dist[i][0] = 0;
        }
        else {
            dq.push_back({ { i, 0 }, 1 });
            dist[i][0] = 1;
        }
    }

    while (sz(dq)) {
        int y = dq.front().fr.fr, x = dq.front().fr.sc;
        int w = dq.front().sc;
        dq.pop_front();

        if (w > dist[y][x]) continue;

        FOR(i, 4, 8) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
            if (near(ny, nx)) continue;

            int nw = w + (a[ny][nx] == '#' ? 0 : 1);
            if (dist[ny][nx] > nw) {
                dist[ny][nx] = nw;
                if (a[ny][nx] == '#') dq.push_front({ { ny, nx }, nw });
                else dq.push_back({ { ny, nx }, nw });
                prv[ny][nx] = { y, x };
            }
        }
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
        init();

        input();

        bfs01();

        int idx = -1, mn = INF;
        FOR(n) {
            if (mn > dist[i][m - 1]) {
                mn = dist[i][m - 1];
                idx = i;
            }
        }

        if (mn == INF) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";

        int y = idx, x = m - 1;
        while (y != -1) {
            a[y][x] = '#';
            int tmpy = y, tmpx = x;
            y = prv[tmpy][tmpx].fr;
            x = prv[tmpy][tmpx].sc;
        }

        EACH(i, a)
            cout << i << '\n';
	}

	return 0;
}