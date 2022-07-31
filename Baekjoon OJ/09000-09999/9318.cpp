#pragma GCC optimize ("O3")
#pragma GCC target ("avx2")
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

const int MAX = 6060;

struct xy {
    int sx, sy, ex, ey;
};

int n, h;
ll dist[MAX];
int psum[MAX][MAX];
vt<xy> a;

void init() {
    FOR(h) {
        dist[i] = 0;
        FOR(j, h) {
            psum[i][j] = 0;
        }
    }
    n = h = 0;
    a.clear();
}

void input() {
    cin >> n;
    a.resize(n);
    EACH(i, a) cin >> i.sx >> i.sy >> i.ex >> i.ey;
}

void cc() {
    vt<pii> b;
    EACH(i, a) {
        b.push_back({ i.sx, 0 });
        b.push_back({ i.sy, 0 });
        b.push_back({ i.ex, 0 });
        b.push_back({ i.ey, 0 });
        b.push_back({ i.ex, 1 });
        b.push_back({ i.ey, 1 });
    }

    sort(all(b));
    b.erase(unique(all(b)), b.end());

    h = sz(b);

    EACH(i, a) {
        int tmp = lower_bound(all(b), (pii){ i.sx, 0 }) - b.begin();
        dist[tmp] = i.sx, i.sx = tmp;
        tmp = lower_bound(all(b), (pii){ i.sy, 0 }) - b.begin();
        dist[tmp] = i.sy, i.sy = tmp;
        tmp = lower_bound(all(b), (pii){ i.ex, 0 }) - b.begin();
        dist[tmp] = i.ex, i.ex = tmp;
        tmp = lower_bound(all(b), (pii){ i.ey, 0 }) - b.begin();
        dist[tmp] = i.ey, i.ey = tmp;
    }
}

ll f() {
    EACH(i, a) {
        psum[i.sy][i.sx]++;
        psum[i.sy][i.ex + 1]--;
        psum[i.ey + 1][i.sx]--;
        psum[i.ey + 1][i.ex + 1]++;
    }

    FOR(i, 1, h) {
        psum[i][0] += psum[i - 1][0];
        psum[0][i] += psum[0][i - 1];
    }

    ll ret = 0;

	FOR(i, 1, h) {
		FOR(j, 1, h) {
            psum[i][j] += psum[i][j - 1];
            psum[i][j] += psum[i - 1][j];
            psum[i][j] -= psum[i - 1][j - 1];

            if (psum[i - 1][j - 1]) {
                if (!psum[i][j - 1] || !psum[i - 1][j] || !psum[i][j]) continue;
                ret += (dist[i] - dist[i - 1]) * (dist[j] - dist[j - 1]); 
            }
		}
	}

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
	
	int tc; cin >> tc;

    FOR(tc) {
        input();

        cc();

        cout << f() << '\n';

        init();
    }

	return 0;
}