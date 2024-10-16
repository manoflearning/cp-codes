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
const int dy[] = { 0, -1, 0, 1, 1, 1, -1, -1 };
const int dx[] = { -1, 0, 1, 0, 1, -1, 1, -1 };

const int MAXV = 2 * 4 * 102 * 102 + 100;

int n, m;
vt<vt<char>> a;
vt<int> adj[MAXV];
vt<int> ID[111][111];

void input() {
    cin >> n >> m;
    a.resize(n + 2, vt<char>(m + 2));
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            cin >> a[i][j];
        }
    }
}

inline int inv(int x) {
	// negative number -a indicates ¬a.
	return (x > 0) ? 2 * x : 2 * -x + 1;
}

void twoCnf(int a, int b) {
	// (a ∨ b) iff (¬a → b) iff (¬b → a)
	adj[inv(-a)].push_back(inv(b));
	adj[inv(-b)].push_back(inv(a));
}

int bit(int y, int x, int k) {
    while (1) {
        int ny = y + dy[k], nx = x + dx[k];
        if (ny < 0 || n + 1 < ny || nx < 0 || m + 1 < nx) break;
        if (a[ny][nx] == 'T') return 0;
        if (a[ny][nx] == '#') break;
        y = ny, x = nx;
    }
    return 1;
}

int bit2(int y, int x, int k) {
    int ret = 0;
    while (1) {
        int ny = y + dy[k], nx = x + dx[k];
        if (ny < 0 || n + 1 < ny || nx < 0 || m + 1 < nx) return 0;
        if (a[ny][nx] == 'T') break;
        if (a[ny][nx] == '#') return 0;
        y = ny, x = nx, ret++;
    }
    return ret + 1;
}

void buildGraph() {
    int val = 0;
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            ID[i][j].push_back(4 * (102 * i + j));
            ID[i][j].push_back(4 * (102 * i + j) + 1);
            ID[i][j].push_back(4 * (102 * i + j) + 2);
            ID[i][j].push_back(4 * (102 * i + j) + 3);
        }
    }

    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            if (a[i][j] == 'T') {
                const vt<int>& id = ID[i][j];

                FOR(k, 2) {
                    int b0 = bit(i, j, k), b1 = bit(i, j, k + 2);

                    if (b0 & b1) {
                        // (a != b) iff ((a ∨ b) ^ (¬a ∨ ¬b))
                        twoCnf(id[k], id[k + 2]);
                        twoCnf(-id[k], -id[k + 2]);
                    }
                    else if (b0) {
                        twoCnf(id[k], id[k]);
                        //twoCnf(-id[k + 2], -id[k + 2]);
                    }
                    else if (b1) {
                        twoCnf(id[k + 2], id[k + 2]);
                        //twoCnf(-id[k], -id[k]);
                    }
                }
            }
            if (a[i][j] == 'n') {
                vt<int> vi(4);
                FOR(k, 4) {
                    int res = bit2(i, j, k);
                    if (res) vi[k] = res;
                }

                if (vi[0] && vi[2]) vi[0] = vi[2] = 0;
                if (vi[1] && vi[3]) vi[1] = vi[3] = 0;

                vt<pii> dir;
                FOR(k, 4) {
                    if (vi[k]) dir.push_back({ vi[k], k });
                }

                if (sz(dir) == 1) {
                    int x = dir[0].fr, y = dir[0].sc;
                    int ii = i + x * dy[y], jj = j + x * dx[y];
                    int ny = y <= 1 ? y + 2 : y - 2;

                    twoCnf(ID[ii][jj][ny], ID[ii][jj][ny]);
                    //cout << a[ii][jj] << '\n';
                }
                if (sz(dir) == 2) {
                    int ii0 = i + dir[0].fr * dy[dir[0].sc], jj0 = j + dir[0].fr * dx[dir[0].sc];
                    int ny0 = dir[0].sc <= 1 ? dir[0].sc + 2 : dir[0].sc - 2;

                    int ii1 = i + dir[1].fr * dy[dir[1].sc], jj1 = j + dir[1].fr * dx[dir[1].sc];
                    int ny1 = dir[1].sc <= 1 ? dir[1].sc + 2 : dir[1].sc - 2;

                    twoCnf(ID[ii0][jj0][ny0], ID[ii1][jj1][ny1]);
                    //cout << a[ii0][jj0] << '\n';
                    //cout << a[ii1][jj1] << '\n';
                }
            }
        }
    }
}

int dfsn[MAXV], dCnt, sNum[MAXV], sCnt;
int finished[MAXV];
stack<int> stk;
pii p[MAXV];
int ans[111][111][4];

int dfs(int now) {
	int ret = dfsn[now] = ++dCnt;

	stk.push(now);

	for (int next : adj[now]) {
		if (dfsn[next] == -1) ret = min(ret, dfs(next));
		else if (!finished[next]) ret = min(ret, dfsn[next]);
	}

	if (ret >= dfsn[now]) {
		while (1) {
			int t = stk.top();
			stk.pop();

			sNum[t] = sCnt;
			finished[t] = 1;
			
			if (t == now) break;
		}
		sCnt++;
	}

	return ret;
}

void findValueOfEachVariable() {
	// order of scc is the reverse of the topological sort
	for (int v = 0; v < MAXV; v++) {
		p[v] = { sNum[v], v };
	}

	sort(p, p + MAXV);

	// determining true/false of each variable
	for (int i = MAXV - 1; i >= 0; i--) {
		int val = p[i].sc / 2;
        int d = val % 4, y = val / 4 / 102, x = val / 4 % 102;
		if (ans[y][x][d] == -1) 
			ans[y][x][d] = (p[i].sc & 1 ? 1 : 0);
	}
		
	FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            if (a[i][j] == 'T') {
                vt<int> val = { ans[i][j][0], ans[i][j][1], ans[i][j][2], ans[i][j][3] };
                
                if (val[0] && val[1]) cout << 1;
                else if (val[2] && val[3]) cout << 2;
                else if (val[1] && val[2]) cout << 3;
                else if (val[0] && val[1]) cout << 4;
                //cout << u << ' ' << v;
            }
            else cout << a[i][j];
        }
        cout << '\n';
    }
}

void init() {
    memset(dfsn, -1, sizeof(dfsn));
    memset(sNum, 0, sizeof(sNum));
    FOR(111) {
        FOR(j, 111) {
            FOR(k, 4) {
                ans[i][j][k] = -1;
            }
        }
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
	
	input();

    buildGraph();

    // finding scc
    init();

	for (int v = 0; v < MAXV; v++)
	    if (dfsn[v] == -1) dfs(v);
        
    findValueOfEachVariable();

	return 0;
}