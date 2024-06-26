#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;

int n, m;
vector<ll> w;
vector<int> t[101010];

void input() {
    cin >> n >> m;
    w.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
}

ll ans = 0;

void dfs(int v, int prv) {
	ll w_rem = 0;
	for (auto& i : t[v]) {
		if (i == prv) continue;
		dfs(i, v);
		w_rem = max(w_rem, w[i]);
	}

    ans += w_rem;
    w[v] = max(0ll, w[v] - w_rem);
    if (prv != -1) w[prv] = max(0ll, w[prv] - w_rem);
    else {
        ans += w[v];
        w[v] = 0;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(1, -1);

    cout << ans;
}