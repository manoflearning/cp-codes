#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int N = 202020;

struct uf {
    vector<int> uf;
    void build(int n) {
        uf.resize(n + 1, -1);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return;
        uf[u] = v;
    }
} uf;

int n, m;
struct Edge {
    int u, v; ll w;
    bool operator<(const Edge &rhs) const {
        return w < rhs.w;
    }
};
vector<Edge> e;

ll acc_w = 0;

vector<int> adj[N];
int cnt_unassigned = 0;
void get_complement_component() {
    list<int> rem;
    for (int i = 1; i <= n; i++) rem.push_back(i);

    vector<bool> blk(n + 1);
    queue<int> qu;
    while (!rem.empty()) {
        int s = rem.front();
        rem.pop_front();
        qu.push(s);

        while (!qu.empty()) {
            int v = qu.front(); qu.pop();

            for (int u : adj[v]) blk[u] = 1;

            for (auto it = rem.begin(); it != rem.end(); ) {
                int u = *it;
                if (!blk[u]) {
                    if (uf.find(u) != uf.find(v)) {
                        cnt_unassigned++;
                        uf.merge(u, v);
                    }
                    qu.push(u);
                    it = rem.erase(it);
                } else it++;
            }

            for (int u : adj[v]) blk[u] = 0;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    e.resize(m);
    for (auto &i : e) {
        cin >> i.u >> i.v >> i.w;
        acc_w ^= i.w;
        adj[i.u].push_back(i.v);
        adj[i.v].push_back(i.u);
    }

    for (int v = 1; v <= n; v++) {
        sort(all(adj[v]));
    }

    uf.build(n);
    
    get_complement_component();

    sort(all(e));

    ll ans = 0;
    if ((ll)n * (n - 1) / 2 - m - 1 < cnt_unassigned) {
        ll opt = acc_w;
        for (auto &i : e) {
            if (uf.find(i.u) == uf.find(i.v)) {
                opt = min(opt, i.w);
                break;
            }
        }
        ans += opt;
    }

    for (auto &i : e) {
        if (uf.find(i.u) == uf.find(i.v)) continue;
        ans += i.w;
        uf.merge(i.u, i.v);
    }

    cout << ans;
}
