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

vector<int> p(1010, -1);

int find(int x) {
	if (p[x] < 0) return x;
	return p[x] = find(p[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	p[A] += p[B];
	p[B] = A;
}

int n, m, vi[1010];
vt<int> adj[1010];

void dfs(int now, vt<int>& a, vt<int>& b, int bit) {
    vi[now] = 1;
    if (!bit) a.push_back(now);
    else b.push_back(now);
    EACH(i, adj[now]) {
        if (!vi[i]) dfs(i, a, b, !bit);
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

    cin >> n >> m;
    FOR(m) {
        char op;
        int u, v;
        cin >> op >> u >> v;
        if (op == 'F') merge(u, v);
        if (op == 'E') {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    FOR(i, 1, n + 1) if (!vi[i]) {
        vt<int> a, b;
        dfs(1, a, b, 0);
        FOR(sz(a) - 1) merge(a[i], a[i + 1]);
        FOR(sz(b) - 1) merge(b[i], b[i + 1]);
    }

    memset(vi, 0, sizeof(vi));
    int ans = 0;
    FOR(i, 1, n + 1) {
        if (vi[find(i)]) continue;
        vi[find(i)] = 1;
        ans++;
    }

    cout << ans;

	return 0;
}

/*#define _USE_MATH_DEFINES
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
vt<int> adj[1010], adj2[1010];
int vi[1010], vi2[1010];

void dfs(int now) {
    vi[now] = 1;
    EACH(i, adj[now]) {
        if (!vi[i]) dfs(i);
    }
}

void dfs2(int now, vt<int>& a, vt<int>& b, int bit) {
    vi2[now] = 1;
    if (bit % 2 == 0) a.push_back(now);
    if (bit % 2 == 1) b.push_back(now);

    EACH(i, adj2[now]) {
        if (!vi2[i]) dfs2(i, a, b, !bit);
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

	cin >> n >> m;
    FOR(m) {
        char op;
        int u, v;
        cin >> op >> u >> v;
        if (op == 'F') {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        if (op == 'E') {
            adj2[u].push_back(v);
            adj2[v].push_back(u);
        }
    }

    FOR(i, 1, n + 1) {
        if (!vi2[i]) {
            vt<int> a, b;
            dfs2(i, a, b, 0);
            FOR(j, 1, sz(a)) {
                adj[a[0]].push_back(a[j]);
                adj[a[j]].push_back(a[0]);
            }
            FOR(j, 1, sz(b)) {
                adj[b[0]].push_back(b[j]);
                adj[b[j]].push_back(b[0]);
            }
        }
    }

    int ans = 0;
    FOR(i, 1, n + 1) {
        if (!vi[i]) { ans++; dfs(i); }
    }

    cout << ans;

	return 0;
}*/