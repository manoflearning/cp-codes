#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define pll pair<ll, ll>
#define fr first
#define sc second

struct wv { ll w; int v; };
struct Query { int idx; ll ub; };

int n, isLeaf[202020];
vector<wv> adj[202020], t[202020];
ll dp[202020], dep[202020];

int q;
vector<Query> query;
vector<ll> ans;

void dfs(int v, int prv, int d) {
    if (prv != 0 && sz(adj[v]) == 1) isLeaf[v] = 1;

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
priority_queue<pll> pq2;

int done = 0;
void add(int v) {
    if (isLeaf[v]) done = 1;

    for (auto& i : t[v]) {
        if (i.w == 1) add(i.v);
        else pq.push({ dp[i.v] + i.w - 1, dp[i.v], i.v });
    }
}

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
    for (int i = q - 1; i >= 1; i--) {
        query[i].ub = query[i].ub - query[i - 1].ub;
    }

    add(1);

    ll cnt = 0, curr = (sz(pq) ? pq.top().w : dp[1]), sum = 0;
    for (int i = 0; i < q; i++) {
        if (done) {
            ans[query[i].idx] = curr;
            continue;
        }

        sum += query[i].ub;

        while (sum > 0 && !done) {
            while (sz(pq) && pq.top().w == curr) {
                cnt++;
                pq2.push({ pq.top().lb, pq.top().v });
                pq.pop();
            }
            
            ll nxt = curr - sum / cnt;
            nxt = max(nxt, sz(pq) ? pq.top().w : 0);
            nxt = max(nxt, sz(pq2) ? pq2.top().fr : 0);

            if (nxt == curr) break;

            sum -= (curr - nxt) * cnt;
            curr = nxt;

            while (sz(pq2) && pq2.top().fr == curr) {
                cnt--;
                add(pq2.top().sc);
                pq2.pop();
            }
        }
        
        ans[query[i].idx] = curr;
    }

    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}