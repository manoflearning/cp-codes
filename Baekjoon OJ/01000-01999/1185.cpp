#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> uf(10101, -1);

int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}

void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    uf[U] = V;
}

struct Edge {
    ll w; int u, v;
    bool operator<(const Edge& rhs) const {
        return w < rhs.w;
    }
};

int n, p, deg[10101];
ll w[10101];
vector<Edge> e;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n >> p;
    for (int i = 1; i <= n; i++) cin >> w[i];

    e.resize(p);
    for (auto& i : e) {
        cin >> i.u >> i.v >> i.w;
        i.w = 2 * i.w + w[i.u] + w[i.v];
    }

    sort(e.begin(), e.end());

    ll ans = 0;
    for (auto& i : e) {
        if (find(i.u) == find(i.v)) continue;
        //cout << i.u << ' ' << i.v << ' ' << i.w << '\n';
        ans += i.w;
        merge(i.u, i.v);
        deg[i.u]++, deg[i.v]++;
    }

    ll mn = 1e18;
    for (int v = 1; v <= n; v++) {
        mn = min(mn, w[v]);
    }

    cout << ans + mn;

	return 0;
}