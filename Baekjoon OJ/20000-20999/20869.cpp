#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-7;
const double INF = 1e18;

struct Edge { double w; int v; };

int n, m;
vector<vector<Edge>> adj(101010), tmp;

int vi[101010];
double dp[101010];

void init() {
    for (int i = 0; i < 101010; i++) {
        vi[i] = dp[i] = 0;
    }
}

double f(int v) {
    double& ret = dp[v];
    if (vi[v]) return ret;
    if (v == n) return ret = 0;
    vi[v] = 1;
    ret = -INF;
    for (auto& i : adj[v]) {
        ret = max(ret, i.w + f(i.v));
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ (double)w, v });
    }

    double l = 1, r = 2 * 1e6;
    while (r - l > EPS) {
        init();

        double mid = (l + r) / 2;
        tmp = adj;
        for (int v = 1; v <= n; v++) {
            for (auto& i : adj[v]) i.w -= mid;
        }
        //cout << mid << ' ' << f(1) << '\n';
        if (f(1) >= 0) l = mid;
        else r = mid;

        adj = tmp;
    }
    cout << fixed;
    cout.precision(6);
    cout << l;
}