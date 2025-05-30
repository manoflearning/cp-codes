// Divide and Conquer Optimization 
// Recurrence: DP[t][i] = min(DP[t - 1][j] + C[j][i]) (1 <= j < n)
// Condition: Let opt[t][i] be j with the smallest value of DP[t - 1][j] + C[j][i]. It must satisfy opt[t][i] <= opt[t][i + 1].
// BOJ 12766 AC Code
// https://www.acmicpc.net/problem/12766
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e18;
const int MAX = 5050;
int n, b, s, r;
ll w[MAX], dp[MAX][MAX], psum[MAX];
struct wv {
    ll w; int v;
    bool operator<(const wv& rhs) const {
		return w > rhs.w;
	}
};
vector<wv> adj[MAX], radj[MAX];
void input() {
    cin >> n >> b >> s >> r;
    for (int i = 0; i < r; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        adj[u].push_back({ d, v });
        radj[v].push_back({ d, u });
    }
}
vector<ll> dist(MAX, INF), rdist(MAX, INF);
void dijkstra() {
	priority_queue<wv> pq;
	pq.push({ 0, b + 1 });
	dist[b + 1] = 0;
	while (!pq.empty()) {
		int v = pq.top().v;
		ll w = pq.top().w;
		pq.pop();
		if (w > dist[v]) continue;
		for (auto& i : adj[v]) {
			if (dist[i.v] > w + i.w) {
				dist[i.v] = w + i.w;
				pq.push({ w + i.w, i.v });
			}
		}
	}
    pq.push({ 0, b + 1 });
    rdist[b + 1] = 0;
    while (!pq.empty()) {
		int v = pq.top().v;
		ll w = pq.top().w;
		pq.pop();
		if (w > rdist[v]) continue;
		for (auto& i : radj[v]) {
			if (rdist[i.v] > w + i.w) {
				rdist[i.v] = w + i.w;
				pq.push({ w + i.w, i.v });
			}
		}
	}
}
void f(int gr, int l, int r, int nl, int nr) {
    int mid = (l + r) >> 1, idx = -1;
    ll& res = dp[gr][mid];
    res = INF;
    for (int i = nl; i <= min(mid, nr); i++) {
        ll val = dp[gr - 1][i] + (mid - i - 1) * (psum[mid] - psum[i]);
        if (res > val) {
            res = val, idx = i;
        }
    }
    if (l < r) {
        f(gr, l, mid, nl, idx);
        f(gr, mid + 1, r, idx, nr);
    }
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	input();
    dijkstra();
    for (int i = 1; i <= b; i++) {
        w[i] = dist[i] + rdist[i];
    }
    sort(w + 1, w + 1 + b);
    for (int i = 1; i <= b; i++) {
        psum[i] = w[i] + psum[i - 1];
    }
    for (int i = 1; i <= b; i++) {
        dp[1][i] = (i - 1) * psum[i];
    }
    for (int i = 2; i <= s; i++) {
        f(i, i, b, 0, b);
    }
    cout << dp[s][b];
	return 0;
}