#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

const ll INF = 1e18;

int x, n, v[101010];
ll ub, adj[111][111], w[111], mnw = INF;
ll psum[101010];

void input() {
    cin >> x >> n >> ub;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> adj[i][j];
        }
    }
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i <= x; i++) {
        cin >> v[i];
        mnw = min(mnw, w[v[i]]);
    }
}

void floyd() {
    //for (int i = 1; i <= n; i++) adj[i][i] = 0;
    for (int k = 1; k <= n; k++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
            }
        }
    }
}

void buildPsum() {
    v[0] = 1;
    for (int i = 1; i <= x; i++) {
        psum[i] = adj[v[i - 1]][v[i]] + psum[i - 1];
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    floyd();

    buildPsum();

    if (psum[x] + mnw <= ub) {
        cout << 0 << ' ' << psum[x] + mnw;
        return 0;
    }
    
    ll ans1 = INF, ans2 = INF;
    for (int st = 1; st < x; st++) {
        if (psum[st] + w[v[st]] <= ub && (x - st < ans1 || (x - st == ans1 && psum[st] + w[v[st]] < ans2))) {
            ans1 = x - st;
            ans2 = psum[st] + w[v[st]];
        }

        int l = st + 1, r = x;
        ll res = INF;
        while (l < r) {
            int mid = (l + r) >> 1;
            res = (psum[st] + w[v[st]]) + adj[v[st]][v[mid]] + (psum[x] - psum[mid]);
            if (res <= ub) r = mid;
            else l = mid + 1;
        }

        res = (psum[st] + w[v[st]]) + adj[v[st]][v[l]] + (psum[x] - psum[l]);
        
        ll cnt = l - st - 1;
        if (res <= ub && (cnt < ans1 || (cnt == ans1 && res < ans2))) {
            ans1 = cnt;
            ans2 = res;
        }
    }

    if (ans1 == INF) cout << -1;
    else cout << ans1 << ' ' << ans2;
}