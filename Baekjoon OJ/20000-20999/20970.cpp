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

int n, k;
vt<pii> a;
vt<int> e[202020], adj[202020];
int adj2[202020];

int v[202020], v2[202020], res, ans[202020];

void input() {
    cin >> n >> k;
    a.resize(k);
    FOR(k) {
        cin >> a[i].fr >> a[i].sc;
        e[a[i].fr].push_back(i);
        e[a[i].sc].push_back(i); 
    }
}

void f(int x) {
    EACH(i, adj[x]) {
        if (v[i]) continue;
        v[i] = 1;
        res++;
    }
}

void init(int x) {
    EACH(i, adj[x]) {
        v[i] = 0;
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

    FOR(i, 1, n + 1) {
        int now = i, t = 0;
        while (1) {
            adj[i].push_back(now);

            auto it = lower_bound(all(e[now]), t);
            if (it == e[now].end()) break;
            
            t = *it;
            if (now == a[t].fr) now = a[t].sc;
            else now = a[t].fr;

            t++;
        }

        adj2[i] = now;
    }

    FOR(i, 1, n + 1) {
        if (v2[i]) continue;

        f(i);
        for (int j = adj2[i]; j != i; j = adj2[j]) f(j);
        

        ans[i] = res;
        init(i);
        v2[i] = 1;
        for (int j = adj2[i]; j != i; j = adj2[j]) {
            init(j); v2[j] = 1; ans[j] = res;
        }
        res = 0;
    }

    FOR(i, 1, n + 1) 
        cout << ans[i] << '\n';

	return 0;
}