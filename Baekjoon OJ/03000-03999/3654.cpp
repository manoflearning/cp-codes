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

const int MAXV = 2 * (4 * 502 * 502 + 3) + 1 + 5;

int n, m, bCnt, wCnt;
vt<vt<char>> a;
vt<int> adj[MAXV];
vt<int> ID[505][505];
int isNO;

int dfsn[MAXV], dCnt, sNum[MAXV], sCnt;
int finished[MAXV];
stack<int> stk;

void init() {
    bCnt = wCnt = 0;
    a.clear();
    FOR(MAXV) adj[i].clear();
    FOR(505) {
        FOR(j, 505) {
            ID[i][j].clear();
        }
    }
    isNO = 0;

    memset(dfsn, -1, sizeof(dfsn));
    memset(sNum, 0, sizeof(sNum));
    dCnt = sCnt = 0;
	memset(finished, 0, sizeof(finished));
    while (sz(stk)) stk.pop();
}

void input() {
    cin >> n >> m;
    a.resize(n + 2, vt<char>(m + 2));
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            cin >> a[i][j];
            if (a[i][j] == 'B') bCnt++;
            if (a[i][j] == 'W') wCnt++;
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

void buildGraph() {
    int val = 0;
    FOR(i, 0, n + 2) {
        FOR(j, 0, m + 2) {
            /*if (a[i][j] == 'B') {
                ID[i][j].push_back(4 * val);
                ID[i][j].push_back(4 * val + 1);
                ID[i][j].push_back(4 * val + 2);
                ID[i][j].push_back(4 * val++ + 3);
            }*/
            ID[i][j].push_back(4 * val);
            ID[i][j].push_back(4 * val + 1);
            ID[i][j].push_back(4 * val + 2);
            ID[i][j].push_back(4 * val++ + 3);
        }
    }

    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            /*vt<int> id = {
                (i - 1) * 500 + (j - 1),
                (i - 1) * 500 + (j - 1) + 500 * 500,
                (i - 1) * 500 + j,
                i * 500 + (j - 1) + 500 * 500
            };*/

            if (a[i][j] == 'B') {
                const vt<int>& id = ID[i][j];

                FOR(k, 2) {
                    int b0 = (a[i + dy[k]][j + dx[k]] == 'W');
                    int b1 = (a[i + dy[k + 2]][j + dx[k + 2]] == 'W');

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
                    else isNO = 1;
                }
                /*FOR(p, 4) {
                    FOR(q, p + 1, 4) {
                        if (a[i + dy[p]][j + dx[p]] == 'B' && a[i + dy[q]][j + dx[q]] == 'B') {
                            twoCnf(id[p], -id[p]);
                            twoCnf(id[q], -id[q]);
                        }
                    }
                }*/
            }
            if (a[i][j] == 'W') {
                FOR(p, 4) {
                    /*if (a[i + dy[p]][j + dx[p]] != 'B') {
                        int np = (p <= 1 ? p + 2 : p - 2);
                        twoCnf(-ID[i + dy[p]][j + dx[p]][np], -ID[i + dy[p]][j + dx[p]][np]);
                    }*/
                    FOR(q, p + 1, 4) {
                        if (a[i + dy[p]][j + dx[p]] == 'B' && a[i + dy[q]][j + dx[q]] == 'B') {
                            int np = (p <= 1 ? p + 2 : p - 2), nq = (q <= 1 ? q + 2 : q - 2);
                            twoCnf(-ID[i + dy[p]][j + dx[p]][np], -ID[i + dy[q]][j + dx[q]][nq]);
                        }
                    }
                }
            }
        }
    }
}

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

int isSatisfiable() {
	// determining satisfiability 
	int isS = 1;
	for (int v = 0; v < MAXV; v += 2) {
		// if x and ¬x is in same scc, then the proposition is not satisfiable
		if (sNum[v] == sNum[v + 1]) {
			isS = 0; break;
		}
	}
	return isS;
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
        init();

        input();

        // edge case
        if (bCnt * 2 != wCnt) {
            cout << "NO\n";
            continue;
        }

        buildGraph();
        
        if (isNO) {
            cout << "NO\n";
            continue; 
        }

        // finding scc
	    for (int v = 0; v < MAXV; v++)
		    if (dfsn[v] == -1) dfs(v);
        
        if (isSatisfiable()) cout << "YES\n";
        else cout << "NO\n";
    }

	return 0;
}