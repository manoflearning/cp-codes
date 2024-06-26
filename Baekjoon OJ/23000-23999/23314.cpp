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

struct wv {
    ll w;
    int v, idx;
};

int n, m, q;
int dfsn[101010], dCnt;
vt<wv> adj[101010];
stack<int> stk;
vt<vt<int>> bcc;
vt<pair<pii, int>> edge;
map<pii, int> mp;

int aEdge[151515], bccNum[151515];
ll cost[151515];
multiset<ll> bccMx[151515];
ll sum = 0, sum2 = 0;

void input() {
	cin >> n >> m >> q;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ w, v, i });
		adj[v].push_back({ w, u, i });
        cost[i] = w;

        if (u > v) swap(u, v);
        mp.insert({ { u, v }, i });
	}
}

int dfs(int now, int prv) {
	int ret = dfsn[now] = ++dCnt;

	for (auto i : adj[now]) {
        int next = i.v;
		if (next == prv) continue;

		// If an edge { now, next } has not yet been visited, it puts an edge on the stack.
		if (dfsn[now] > dfsn[next]) stk.push(i.idx);
		// Back edge
		if (dfsn[next] != -1) ret = min(ret, dfsn[next]);
		// Tree edge
		else {
			int tmp = dfs(next, now);
			ret = min(ret, tmp);
            
            if (tmp > dfsn[now]) {
                aEdge[i.idx] = 1;
            }

			// if next cannot go to ancestor node of now, find BCC
			if (tmp >= dfsn[now]) {
				vt<int> nowBCC;
				while (true) {
					int t = stk.top();
					stk.pop();

					nowBCC.push_back(t);

					if (t == i.idx) break;
				}

				bcc.push_back(nowBCC);
			}
		}
	}

	return ret;
}

void getBCC() {
	memset(dfsn, -1, sizeof(dfsn));

	dfs(1, 0);
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

    getBCC();

    //
    FOR(i, m)
        sum += cost[i];

    FOR(i, sz(bcc)) {
        for (auto j : bcc[i]) {
            if (!aEdge[j]) {
                bccNum[j] = i;

                bccMx[i].insert(cost[j]);
            }
        }

        if (sz(bccMx[i]))
            sum2 += max(0ll, *bccMx[i].rbegin());
    }
    
    cout << sum - sum2 << '\n';

    FOR(q) {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        if (u > v) swap(u, v);
        int x = mp.find({ u, v })->sc;

        if (aEdge[x]) {
            sum -= cost[x];
            cost[x] = w;
            sum += cost[x];
        }
        else {
            int y = bccNum[x];

            sum -= cost[x];
            sum2 -= max(0ll, *bccMx[y].rbegin());
            
            auto it = bccMx[y].find(cost[x]);
            bccMx[y].erase(it);
            cost[x] = w;
            bccMx[y].insert(cost[x]);

            sum += cost[x];
            sum2 += max(0ll, *bccMx[y].rbegin());
        }
        
        cout << sum - sum2 << '\n';
    }

	return 0;
}