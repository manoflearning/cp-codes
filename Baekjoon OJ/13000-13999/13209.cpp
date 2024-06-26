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
ll wmx, w[101010];
vt<int> adj[101010];

void init() {
    wmx = 0;
    FOR(101010) {
        w[i] = 0;
        adj[i].clear();
    }
}

void input() {
    cin >> n >> k;
    FOR(i, 1, n + 1) {
        cin >> w[i];
        wmx = max(wmx, w[i]);
    }
    FOR(n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

int ccnt;

ll f(int v, int prv, ll rb) {
    ll sum = w[v];
    priority_queue<ll> pq;

    EACH(i, adj[v]) {
        if (i == prv) continue;
        ll res = f(i, v, rb);
        sum += res;
        pq.push(res);
    }

    while (sz(pq) && sum > rb) {
        sum -= pq.top();
        pq.pop();
        ccnt++;
    }

    return sum;
}

bool isPos(ll rb) {
    ccnt = 0;
    f(1, 0, rb);
    if (ccnt <= k) return 1;
    else return 0;
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

        ll l = wmx, r = 1e14;
        while (l < r) {
            ll mid = (l + r) >> 1;
            if (isPos(mid)) r = mid;
            else l = mid + 1;
        }

        cout << l << '\n';
	}

	return 0;
}