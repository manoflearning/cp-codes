#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second

const ll INF = 1e18;

int n, m, k;
struct wv {
    ll w; int v;
    bool operator<(const wv& rhs) const {
        return w > rhs.w;
    }
};
vector<wv> adj[101010];
vector<int> en;
int isEn[101010], deg[101010];

void input() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
    en.resize(k);
    for (auto& i : en) {
        cin >> i;
        isEn[i] = 1;
    }
}

ll dp[101010];
pair<ll, ll> mn[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    priority_queue<wv> pq;
    for (int v = 0; v < n; v++) {
        dp[v] = INF;
        mn[v].fr = mn[v].sc = INF;
        if (isEn[v]) {
            dp[v] = 0;
            pq.push({ dp[v], v });
        }
    }

    while (!pq.empty()) {
        ll w = pq.top().w;
        int v = pq.top().v;
        pq.pop();

        if (dp[v] < w) continue;

        for (auto& i : adj[v]) {
            ll nw = w + i.w;
            if (nw <= mn[i.v].fr) mn[i.v].sc = mn[i.v].fr, mn[i.v].fr = nw;
            else if (nw <= mn[i.v].sc) mn[i.v].sc = nw;
            deg[i.v]++;

            if (mn[i.v].sc < dp[i.v]) {
                dp[i.v] = mn[i.v].sc;
                pq.push({ dp[i.v], i.v });
            }
        }
    }

    //for (int v = 0; v < n; v++)
    //    cout << v << ' ' << dp[v] << '\n';

    cout << dp[0];
}