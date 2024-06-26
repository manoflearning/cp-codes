//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, vi[202020], ind[202020], same[202020];
vector<int> g[202020];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    for (int v = 1; v <= n; v++) {
        int u; cin >> u;
        if (u == v) {
            same[v] = 1;
            continue;
        }
        g[v].push_back(u);
        ind[u]++;
    }

    queue<int> q;
    for (int v = 1; v <= n; v++) {
        if (!ind[v]) q.push(v);
    }

    while (sz(q)) {
        int v = q.front();
        q.pop();
        vi[v] = 1;
        for (auto& i : g[v]) {
            ind[i]--;
            if (!ind[i]) q.push(i);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (same[i] || !vi[i]) {
            //cout << i << ' ';
            ans++;
        }
    }

    cout << ans;

	return 0;
}