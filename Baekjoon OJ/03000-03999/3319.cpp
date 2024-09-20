#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;
const ll INF = 1e18;

struct Line { // f(x) = px + q, x >= s
    ll p, q; 
    double s;
    Line(): Line(1, 0) {}
    Line(ll sp, ll sq): p(sp), q(sq), s(0) {}
};
double cross(const Line& u, const Line& v) {
    return (double)(v.q - u.q) / (u.p - v.p);
}

int n;
struct Edge { ll w; int v; };
vector<vector<Edge>> adj(MAXN);
vector<vector<int>> chd(MAXN);
vector<ll> b(MAXN), a(MAXN);

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
    for (int i = 2; i <= n; i++)
        cin >> b[i] >> a[i];
}

vector<ll> pw(MAXN);
vector<int> par(MAXN);

void dfs(int v, int prv) {
    for (auto& i : adj[v]) {
        if (i.v == prv) continue;
        pw[i.v] = pw[v] + i.w;
        par[i.v] = v;
        chd[v].push_back(i.v);
        dfs(i.v, v);
    }
}

vector<ll> dp(MAXN);
vector<int> top(MAXN);
vector<Line> ch(MAXN);

void solve(int v) {
    if (v != 1) {
        Line g(-pw[par[v]], dp[par[v]]);

        top[v] = top[par[v]] + 1;
        while (top[v] > 1) {
            g.s = cross(ch[top[v] - 1], g);
            if (ch[top[v] - 1].s < g.s) break;
            --top[v];
        }

        ch[top[v]] = g;

        int l = 1, r = top[v];
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (a[v] < ch[mid].s) r = mid - 1;
            else l = mid;
        }

        int fpos = l;
        dp[v] += ch[fpos].p * a[v] + ch[fpos].q;
        dp[v] += pw[v] * a[v] + b[v];
    }

    for (auto& i : chd[v]) solve(i);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(1, 0);

    dp[1] = 0;
    top[1] = 1;
    solve(1);

    for (int v = 2; v <= n; v++)
        cout << v << ' ';
}
