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

int n, a[55][55], A[55 * 55], B[55 * 55];
vector<int> adj[55 * 55];
bool visited[55 * 55];
int ans;

void input() {
    cin >> n;
    FOR(i, 1, n + 1) {
        string s; cin >> s;
        FOR(j, 1, n + 1) {
            if (s[j - 1] == '.') a[i][j] = 0;
            if (s[j - 1] == 'o') a[i][j] = 1;
            if (s[j - 1] == 'x') a[i][j] = 2;
        }
    }
}

void buildGraph() {
    FOR(i, 1, n + 1) {
        FOR(j, 1, n + 1) {
            if (a[i][j] == 1) {
                FOR(k, 4) {
                    int ny = i + dy[k], nx = j + dx[k];
                    if (ny < 1 || n < ny || nx < 1 || n < nx) continue;
                    if (a[ny][nx] == 0) adj[50 * (i - 1) + (j - 1)].push_back(50 * (ny - 1) + (nx - 1));
                }
            }
            if (a[i][j] <= 1) ans++;
        }
    }
}

bool dfs(int a) {
	visited[a] = 1;
	for (int b : adj[a]) {
		if (B[b] == -1 || (!visited[B[b]] && dfs(B[b]))) {
			A[a] = b;
			B[b] = a;
			return 1;
		}
	}
	return 0;
}

int bipartiteMatch() {
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));

	int ret = 0;
	for (int i = 0; i < 55 * 55; i++) {
		memset(visited, 0, sizeof(visited));
		if (dfs(i)) ret++;
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

	input();
    
    buildGraph();
    
    int res = bipartiteMatch();
    //cout << ans << ' ' << res << '\n';
    cout << ans - res;

	return 0;
}