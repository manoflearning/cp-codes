#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

struct wv { ll w; int v; };
struct Query { int idx; ll ub; };

int n;
vector<wv> adj[202020], t[202020];
ll dp[202020], dep[202020];

int q;
vector<Query> query;
vector<ll> ans;

void dfs(int v, int prv, int d) {
    dep[v] = d;
    for (auto& i : adj[v]) {
        if (i.v == prv) continue;
        
        dfs(i.v, v, d + 1);
        dp[v] = max(dp[v], i.w + dp[i.v]);
        t[v].push_back(i);
    }
}

struct Node {
    ll w, lb; int v;
    bool operator<(const Node& rhs) const {
        return w < rhs.w;
    }
};

priority_queue<Node> pq;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }

    // initialize
    dfs(1, 0, 0);

    for (int v = 1; v <= n; v++) 
        dp[v] += dep[v];

    // offline query
    cin >> q;    
    query.resize(q);
    ans.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> query[i].ub;
        query[i].idx = i;
    }

    sort(query.begin(), query.end(), [&](const Query& lhs, const Query& rhs) {
        return lhs.ub < rhs.ub;
    });

    // solve
    for (auto& i : t[1]) {
        pq.push({ dp[i.v] + i.w - 1, dp[i.v], i.v });
    }

    ll done = -1;
    for (int i = 0; i < q; i++) {
        ll ub = query[i].ub;

        while (sz(pq) && ub > 0) {
            if (sz(pq) >= 2) {
                Node u = pq.top(); pq.pop();
                ll diff = min({ ub, u.w - pq.top().w - 1, u.w - u.lb });
                ub -= diff, u.w -= diff;
                
                if (u.w == u.lb) {
                    for (auto& j : t[u.v]) {
                        pq.push({ dp[j.v] + j.w - 1, dp[j.v], j.v });
                    }
                    if (t[u.v].empty()) done = max(done, u.w);
                }
                else pq.push(u);
            }
            else {
                Node u = pq.top(); pq.pop();
                ll diff = min(ub, u.w - u.lb);
                ub -= diff, u.w -= diff;

                if (u.w == u.lb) {
                    for (auto& j : t[u.v]) {
                        pq.push({ dp[j.v] + j.w - 1, dp[j.v], j.v });
                    }
                    if (t[u.v].empty()) done = max(done, u.w);
                }
                else pq.push(u);
            }
        }

        ans[query[i].idx] = max(sz(pq) ? pq.top().w : 0, done);
    }

    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}