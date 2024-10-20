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

struct Edge {
	int v, num;
};

int n, m, k;
vt<Edge> adj[101010];

bool vi[101010][4][3], fi[101010][4][3], inf;
int dp[101010][4][3];
bool vi2[101010][4], fi2[101010][4];
int dp2[101010][4];

void init() {
    FOR(i, 1, n + 1) {
        adj[i].clear();
        FOR(j, 4) {
            FOR(k, 3) {
                vi[i][j][k] = fi[i][j][k] = 0;
                dp[i][j][k] = -1;
            }
            vi2[i][j] = fi2[i][j] = 0;
            dp2[i][j] = -1;
        }
    }
    n = m = k = inf = 0;
}

void input() {
	cin >> n >> m >> k;
	FOR(m) {
		int u, v; char c;
		cin >> u >> v >> c;
		adj[u].push_back({ v, c - 'A' });
	}
}

int dfs(int v, int prv, int cnt) {
    int& ret = dp[v][prv][cnt];
    if (ret != -1) return ret;
    ret = 1;

    vi[v][prv][cnt] = 1;
    
    EACH(i, adj[v]) {
        // 조건에 부합하는 글자
		if (prv <= 2) {
			if ((i.num - prv + 3) % 3 == 1) {
                if (!vi[i.v][i.num][cnt]) {
                    ret = max(ret, dfs(i.v, i.num, cnt) + 1);
                }
                else if (!fi[i.v][i.num][cnt]) inf = 1;
                else ret = ret = max(ret, dfs(i.v, i.num, cnt) + 1);
			}
		}
		else {
            if (!vi[i.v][i.num][cnt]) {
                ret = max(ret, dfs(i.v, i.num, cnt) + 1);
            }
            else if (!fi[i.v][i.num][cnt]) inf = 1;
            else ret = ret = max(ret, dfs(i.v, i.num, cnt) + 1);
		}

		// 글자 건너뛰기
        if (cnt > 0) {
            if (!vi[i.v][prv][cnt - 1]) {
                ret = max(ret, dfs(i.v, prv, cnt - 1)); 
            }
            else if (!fi[i.v][prv][cnt - 1]) inf = 1;
            else ret = max(ret, dfs(i.v, prv, cnt - 1));
        }
	}

    fi[v][prv][cnt] = 1;
    //cout << v << ' ' << prv << ' ' << cnt << '\n';
    //cout << ret << '\n';
    return ret;
}

int dfs2(int v, int prv) {
    int& ret = dp2[v][prv];
    if (ret != -1) return ret;
    ret = 1;

    vi2[v][prv] = 1;
    
    EACH(i, adj[v]) {
        // 조건에 부합하는 글자
		if (prv <= 2) {
			if ((i.num - prv + 3) % 3 == 1) {
                if (!vi2[i.v][i.num]) {
                    ret = max(ret, dfs2(i.v, i.num) + 1);
                }
                else if (!fi2[i.v][i.num]) inf = 1;
                else ret = max(ret, dfs2(i.v, i.num) + 1);
			}
		}
		else {
            if (!vi2[i.v][i.num]) {
                ret = max(ret, dfs2(i.v, i.num) + 1);
            }
            else if (fi2[i.v][i.num]) {
                ret = max(ret, dfs2(i.v, i.num) + 1);
            }
		}

		// 글자 건너뛰기
        if (!vi2[i.v][prv]) {
            ret = max(ret, dfs2(i.v, prv)); 
        }
        else if (fi2[i.v][prv]) {
            ret = max(ret, dfs2(i.v, prv)); 
        }
	}

    fi2[v][prv] = 1;

    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

    FOR(i, 1, 101010) {
        FOR(j, 4) {
            FOR(k, 3) dp[i][j][k] = -1;
            dp2[i][j] = -1;
        }
    }

	int tc; cin >> tc;
    FOR(tt, 1, tc + 1) {
        cout << "Case #" << tt << endl;

		input();

        int ans = 0;
        if (k > -1) {
            FOR(i, 1, n + 1) {
                ans = max(ans, dfs(i, 3, k) - 1);
            }
        }
        else {
            FOR(i, 1, n + 1) {
                ans = max(ans, dfs2(i, 3) - 1);
            }
        }

        if (inf) cout << -1 << endl;
        else cout << ans << endl;

        init();
    }

	return 0;
}