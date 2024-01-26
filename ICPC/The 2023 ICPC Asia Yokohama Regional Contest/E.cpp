#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;
const int MOD = 998'244'353;

int n, m;
vector<int> a, b, c;

set<int> adj[24];
int dist[24][24];
map<int, int> ord;

void input() {
    cin >> n >> m;
    a.resize(m);
    b.resize(m);
    c.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> c[i];
        a[i]--, b[i]--, c[i]--;

        if (ord.count(a[i]) && ord.count(b[i])) {
            if (ord[a[i]] > ord[b[i]]) swap(a[i], c[i]);
        }
        if (ord.count(b[i]) && ord.count(c[i])) {
            if (ord[b[i]] > ord[c[i]]) swap(a[i], c[i]);
        }
        if (ord.count(a[i]) && ord.count(c[i])) {
            if (ord[a[i]] > ord[c[i]]) swap(a[i], c[i]);
        }

        if (!ord.count(a[i])) ord[a[i]] = 3 * i + 1;
        if (!ord.count(b[i])) ord[b[i]] = 3 * i + 2;
        if (!ord.count(c[i])) ord[c[i]] = 3 * i + 3;

        adj[a[i]].insert(b[i]);
        adj[b[i]].insert(c[i]);
    }
}

bool isImpossible() {
    vector<int> ind(n);
    for (int v = 0; v < n; v++) {
        for (auto& i : adj[v]) ind[i]++;
    }

    queue<int> q;
    for (int v = 0; v < n; v++) {
        if (!ind[v]) q.push(v);
    }

    for (int i = 0; i < n; i++) {
        if (q.empty()) return 1;
        
        int v = q.front();
        q.pop();
        
        for (auto& i : adj[v]) {
            ind[i]--;
            cout << i << '\n';
            if (!ind[i]) q.push(i);
        }
    }

    return 0;
}

void floyd() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }

    for (int v = 0; v < n; v++)
        for (auto& i : adj[v]) dist[v][i] = 1;
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int vis[24];
vector<int> du;

void dfs(int v) {
    vis[v] = 1;
    du.push_back(v);
    for (auto& i : adj[v]) {
        if (!vis[i]) dfs(i);
    }
}

int prv[24], nxt[24];
ll dp[1 << 24];
ll ans = 1;

void solve() {
    vector<int> ind(n);
    for (int v = 0; v < n; v++) {
        for (auto& i : adj[v]) ind[i]++;
    }

    vector<int> siz;

    for (int v = 0; v < n; v++) {
        if (vis[v] || ind[v]) continue;

        du.clear();
        dfs(v);
        siz.push_back(sz(du));

        for (auto& i : du) {
            for (auto& j : du) {
                if (dist[i][j] > 0) {
                    prv[j] |= (1 << i);
                    nxt[i] |= (1 << j);
                }
            }
        }

        set<int> s;
        int en = 0;
        s.insert(0);
        for (auto& i : du) {
            for (auto& j : s) {
                s.insert(j | (1 << i));
                en = max(en, j | (1 << i));
            }
        }

        dp[0] = 1;
        for (auto& bit : s) {
            for (auto& v : du) {
                if (bit & (1 << v)) continue;
                if ((bit & prv[v]) != prv[v]) continue;
                if ((bit & nxt[v]) != 0) continue;
                int nbit = bit | (1 << v);
                dp[nbit] = (dp[nbit] + dp[bit]) % MOD;
            }
        }

        ans = (ans * dp[en] * (sz(du) >= 2 ? 2 : 1)) % MOD;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    if (isImpossible()) {
        cout << 0;
        return 0;
    }

    floyd();

    solve();

    cout << ans;
}