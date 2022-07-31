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
const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
const int dx[] = { 1, 0, -1, 0, 1, -1, 1, -1 };

struct Point {
    int x, y;
};

int k, num[1212][1212], pow2, coCnt;

void init() {
    FOR(pow2) FOR(j, pow2) num[i][j] = 0;
    coCnt = 0;
}

int findDir(const Point& sp, const Point& ep, const Point& pp) {
    int midx = (sp.x + ep.x) / 2;
    int midy = (sp.y + ep.y) / 2;

    int bit1 = (pp.x <= midx), bit2 = (pp.y <= midy);
    if (bit1 == 1 && bit2 == 1) return 0;
    if (bit1 == 0 && bit2 == 1) return 1;
    if (bit1 == 0 && bit2 == 0) return 2;
    if (bit1 == 1 && bit2 == 0) return 3;
    return 0;
}

/*void checkAdjacentColor(Point& p, vt<int>& res) {
    FOR(4) {
        int nx = p.x + dx[i], ny = p.y + dy[i];
        if (nx < 0 || pow2 <= nx || ny < 0 || pow2 <= ny) continue;
        if (num[nx][ny] == INF) continue;
        if (num[nx][ny] == 0) continue;
        res[num[nx][ny]] = 1;
    }
}

int coloring(vt<int>& res) {
    FOR(i, 1, 3) if (!res[i]) return i;
    return 0;
}*/

void recursion(const Point& sp, const Point& ep, const Point& pp) {
    if (ep.x - sp.x + 1 == 2) {
        vt<Point> p;
        FOR(i, sp.x, ep.x + 1) {
            FOR(j, sp.y, ep.y + 1) {
                if (i == pp.x && j == pp.y) continue;
                p.push_back({ i, j });
            }
        }

        //vt<int> res(4);
        //EACH(i, p) checkAdjacentColor(i, res);
        //int co = coloring(res);
        int co = (coCnt++ & 1 ? 1 : 2);
        EACH(i, p) num[i.x][i.y] = co;
        //assert(0 < co/* && co < 3*/);
    }
    else {
        int dir = findDir(sp, ep, pp);
    
        int midx = (sp.x + ep.x) / 2;
        int midy = (sp.y + ep.y) / 2;
        
        // 0 1
        // 3 2
        vt<Point> p = { { midx, midy }, { midx + 1, midy }, { midx + 1, midy + 1 }, { midx, midy + 1 } };

        FOR(4) if (dir != i)
            num[p[i].x][p[i].y] = 3;

        recursion(sp, { midx, midy }, (dir != 0 ? p[0] : pp));
        recursion({ midx + 1, sp.y }, { ep.x, midy }, (dir != 1 ? p[1] : pp));
        recursion({ midx + 1, midy + 1 }, ep, (dir != 2 ? p[2] : pp));
        recursion({ sp.x, midy + 1 }, { midx, ep.y }, (dir != 3 ? p[3] : pp));
    }
}

void print() {
    FOR(i, pow2) {
        FOR(j, pow2) {
            if (num[i][j] == INF) {
                cout << '@';
                continue;
            }

            if (num[i][j] == 1) cout << 'a';
            if (num[i][j] == 2) cout << 'b';
            if (num[i][j] == 3) cout << 'c';
        }
        cout << '\n';
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

	int tc; 
    cin >> tc >> k;

    pow2 = 1;
    FOR(k) pow2 *= 2;

    while (tc--) {
        init();

        int xx, yy;
        cin >> xx >> yy;
        xx--, yy--;

        num[xx][yy] = INF;
        recursion({ 0, 0 }, { pow2 - 1, pow2 - 1 }, { xx, yy });

        print();
    }

	return 0;
}