#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int MAXV = 20202;

int n, m;
vector<int> adj[MAXV], radj[MAXV];
int in[MAXV], out[MAXV], num, p[MAXV << 1];
int vi[MAXV];

int cnt, sccNum[MAXV];

vector<int> dag[MAXV], rdag[MAXV];
int ind[MAXV], outd[MAXV];

void init() {
    n = m = 0;
    num = cnt = 0;
    for (int i = 0; i < MAXV; i++) {
        adj[i].clear(); radj[i].clear();
        in[i] = out[i] = 0;
        p[i << 1] = p[i << 1 | 1] = vi[i] = 0;
        sccNum[i] = 0;
        dag[i].clear(); rdag[i].clear();
        ind[i] = outd[i] = 0;
    }
}

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
}

void dfs(int v) {
    in[v] = ++num;
    for (auto& i : radj[v]) {
        if (!in[i]) dfs(i);
    }
    out[v] = ++num;
    p[num] = v;
}

void flood(int v) {
    vi[v] = 1;
    sccNum[v] = cnt;
    for (auto& i : adj[v]) {
        if (!vi[i]) flood(i);
    }
}

void kosaraju() {
    for (int i = 1; i <= n; i++) {
        if (!in[i]) dfs(i);
    }

    for (int i = 2 * n; i >= 1; i--) {
        if (!p[i]) continue;
        if (vi[p[i]]) continue;
        cnt++;
        flood(p[i]);
    }
}

void buildDag() {
    for (int v = 1; v <= n; v++) {
        for (auto& u : adj[v]) {
            int V = sccNum[v], U = sccNum[u];
            if (V ^ U) {
                assert(V > U);
                dag[V].push_back(U);
                rdag[U].push_back(V);
                //outd[V]++, ind[U]++;
            }
        }
    }

    for (int v = 1; v <= cnt; v++) {
        sort(all(dag[v]));
        dag[v].erase(unique(all(dag[v])), dag[v].end());
        for (auto& u : dag[v]) {
            outd[v]++, ind[u]++;
        }

        sort(all(rdag[v]));
        rdag[v].erase(unique(all(rdag[v])), rdag[v].end());
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        kosaraju();

        if (cnt == 1) {
            cout << 0 << '\n';
            continue;
        }

        buildDag();

        int source = 0, sink = 0;
        for (int i = 1; i <= cnt; i++) {
            if (!ind[i]) source++;
            if (!outd[i]) sink++;
        }

        cout << max(source, sink) << '\n';
    }

    return 0;
}