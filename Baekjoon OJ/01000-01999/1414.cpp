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

// Union find
vector<int> p(55, -1);

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

struct wv {
    ll w; int v;
};

struct wuv {
	ll w;
	int u, v;
	bool operator<(const wuv& rhs) const {
		return w < rhs.w;
	}
};

int n, vi[55];
vt<wv> adj[55];
vector<wuv> a;
int ans;

void dfs(int now) {
    vi[now] = 1;
    EACH(i, adj[now]) {
        if (!vi[i.v]) dfs(i.v);
    }
}

void makingMST() {
    sort(a.begin(), a.end());

	for (auto& i : a) {
		if (find(i.u) == find(i.v)) continue;
		merge(i.u, i.v);
        ans -= i.w;
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
    FOR(n) {
        string s; cin >> s;
        FOR(j, n) if (s[j] != '0') {
            int dist = ('a' <= s[j] && s[j] <= 'z' ? s[j] - 'a' + 1 : s[j] - 'A' + 27);
            
            adj[i + 1].push_back({ dist, j + 1 });
            adj[j + 1].push_back({ dist, i + 1 });
            a.push_back({ dist, i + 1, j + 1 });
            ans += dist;
        }
    }

    dfs(1);

    FOR(i, 1, n + 1) {
        if (!vi[i]) {
            cout << -1;
            return 0;
        }
    }

    makingMST();

    cout << ans;

	return 0;
}