#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct wv {
    ll w; int v;
};

int n, k, ac[101010], sum[101010];
vector<wv> adj[101010];
int ans = 0;

void input() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }

    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        ac[x] = 1;
    }
}

void dfs(int v, int prv) {
    int res = 0;
    if (ac[v]) {
        res = 1;
        sum[v]++;
    }
    
    int cnt = 0;
    for (auto& i : adj[v]) {
        if (i.v == prv) continue;
        dfs(i.v, v);
        
        if (sum[i.v]) cnt++;
        sum[v] += sum[i.v];
    }

    if (sum[v] < k) cnt++;

    if (cnt >= 2) res = 1;

    if (res) ans++;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    
    dfs(1, 0);

    cout << ans;

    return 0;
}