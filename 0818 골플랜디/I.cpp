/*
Author: Sabro <inhyuk04@gmail.com>
*/

// #include <atcoder/modint>
#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#define pb(x) push_back(x)
#define eb(a, b) emplace_back(a, b)
#define all(v) v.begin(), v.end()
#define fir first
#define sec second
#define FOREACH(x, v) for (auto &x : v)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rrep(i, a, b) for (int i = a; i > b; i--)
#define sz(x) ((int)x.size())
#define MEMSET(x, v) memset(x, v, sizeof(x))
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

#ifdef ONLINE_JUDGE
#define debug(x) ((void)0)
#else
#define debug(x) std::cout << "[Debug] " << #x << " is " << x << '\n'
#endif

using namespace std;
// using namespace atcoder;
// using mint = modint998244353;

const int MAX = 101010;

int N, K, A[MAX], k, maxn;
vector<int> adj[MAX];

void input() {
    FOREACH(a, adj) a.clear();
    cin >> N >> K;
    rep(i, 1, N + 1) {
        cin >> A[i];
    }
    maxn = A[1];
    rep(i, 1, N + 1) maxn = max(maxn, A[i]);
    int u, v;
    rep(i, 0, N - 1) {
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
}

ll recur(int x, const ll t, const int prev = -1){
    priority_queue<ll> pq;
    ll sum = A[x];

    FOREACH(next, adj[x]){
        if(next == prev) continue;
        ll res = recur(next, t, x);
        pq.push(res);
        sum += res;
    }

    while(!pq.empty() && sum > t){
        ll top = pq.top();
        pq.pop();
        sum -= top;
        k++;
    }

    return sum;
}

bool f(ll t){
    k = 0;
    recur(1, t);
    return k <= K;
}

void solve() {
    input();
    ll l = maxn, r = 1e18;
    while(l < r){
        ll mid = (l + r) >> 1;
        if(f(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    int tc = 1;
    cin >> tc;
    while (tc--)
        solve();
    
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

struct Dp {
    ll mx, mn1, mn2;
};

int n, k;
ll w[101010], wsum, siz[101010];
vt<int> adj[101010];
Dp dp[101010];

void init() {
    FOR(101010) dp[i] = { -1, -1, -1 };
}

void input() {
    cin >> n >> k;
    FOR(i, 1, n + 1) cin >> w[i];
    FOR(n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int v, int prv = -1) {
    siz[v] = 1;
    EACH(i, adj[v]) {
        if (i == prv) continue;
        dfs(i, v);
        siz[v] += siz[i];
    }
}

vt<int> res;

void dfs2(int v, int prv = -1) {
    res.push_back(v);
    EACH(i, adj[v]) {
        if (i == prv) continue;
        dfs2(i, v);
    }
}

Dp f(int v, int prv) {
    if (siz[v] == k + 1) {
        res.clear();
        dfs2(v, prv);

        sort(all(res));
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

        dfs(1);

        cout << f(1).mx << '\n';
	}

	return 0;
}*/