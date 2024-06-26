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
const ll INF = 1e18;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXV = 666;

int N, M, st = 0, en = MAXV - 1;
ll c[MAXV][MAXV], f[MAXV][MAXV];
ll d[MAXV][MAXV], prv[MAXV];
vector<int> adj[MAXV];
ll mFlow, mCost;

ll a[MAXV], h[MAXV], l[MAXV], mxa = -1;

void input() {
	cin >> N;
    FOR(N) { cin >> a[i + 1]; mxa = max(mxa, a[i + 1]); }
    FOR(N) cin >> h[i + 1];
    FOR(N) cin >> l[i + 1];
}

void buildGraph() {
    FOR(i, 1, N + 1) {
        adj[st].push_back(i);
        adj[i].push_back(st);
        if (a[i] == mxa) c[st][i] = l[i];
        else c[st][i] = l[i] - 1;
        d[st][i] = h[i];
        d[i][st] = -h[i];
    }
    FOR(i, 1, N + 1) {
        FOR(j, 1, N + 1) {
            if (a[i] > a[j]) {
                int LL = i, RR = j + N;
                adj[LL].push_back(RR);
                adj[RR].push_back(LL);
                c[LL][RR] = 1;
                d[LL][RR] = -(a[i] ^ a[j]);
                d[RR][LL] = (a[i] ^ a[j]);
            }
        }
    }
    FOR(i, 1, N + 1) {
        adj[i + N].push_back(en);
        adj[en].push_back(i + N);
        c[i + N][en] = 1;
        d[i + N][en] = h[i];
        d[en][i + N] = -h[i];
    }
}

void flow() {
	ll block = INF;
	for (int i = en; i != st; i = prv[i]) {
		block = min(block, c[prv[i]][i] - f[prv[i]][i]);
	}
	for (int i = en; i != st; i = prv[i]) {
		mCost += d[prv[i]][i] * block;
		f[prv[i]][i] += block;
		f[i][prv[i]] -= block;
	}
	mFlow += block;
}

void spfa() {
	memset(prv, -1, sizeof(prv));
	vector<ll> dist(MAXV + 5, INF);
	vector<bool> inQ(MAXV + 5);

	queue<int> q;
	q.push(st);
	dist[st] = 0, inQ[st] = true;

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		inQ[now] = false;

		for (int next : adj[now]) {
			if (dist[now] + d[now][next] < dist[next] && c[now][next] - f[now][next] > 0) {
				dist[next] = dist[now] + d[now][next];
				prv[next] = now;
				if (!inQ[next]) {
					inQ[next] = true;
					q.push(next);
				}
			}
		}
	}
}

void mcmf() {
	while (true) {
		spfa();

		if (prv[en] == -1) break;
		
		flow();
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

	mcmf();

	cout << -mCost;
	
	return 0;
}