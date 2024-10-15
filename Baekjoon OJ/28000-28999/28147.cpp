#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;

int n;
ll c[MAXN];
double p[MAXN];
int d[MAXN];

void input() {
    cin >> n;
    c[0] = 0, p[0] = 1, d[0] = -1;
    for (int i = 1; i <= n; i++)
        cin >> c[i] >> p[i] >> d[i];
}

struct UF {
    vector<int> uf, uf2;
    vector<ll> cc;
    vector<double> pp, avg;
    void build(int n) {
        uf.resize(n + 1, -1);
        uf2.resize(n + 1, -1);
        cc.resize(n + 1);
        pp.resize(n + 1);
        avg.resize(n + 1);

        for (int i = 0; i <= n; i++) {
            avg[i] = (1 - p[i]) * c[i];
            cc[i] = c[i];
            pp[i] = p[i];
        }
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    int find2(int x) {
        if (uf2[x] < 0) return x;
        return uf2[x] = find2(uf2[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        avg[U] = avg[U] + pp[U] * ((1 - pp[V]) * cc[U] + avg[V]);
        cc[U] += cc[V];
        pp[U] *= pp[V];
        uf[V] = U;

        int U2 = find2(u), V2 = find2(v);
        uf2[U2] = V2;
    }
}uf;

struct Node {
    ll cc;
    double pp, avg;
    int v;
    bool operator<(const Node& o) const {
        double res1 = avg + pp * ((1 - o.pp) * cc + o.avg);
        double res2 = o.avg + o.pp * ((1 - pp) * o.cc + avg);
        return res1 > res2;
    }
};

bool vis[MAXN];
int ans[MAXN];
void solve() {
    uf.build(n);
    priority_queue<Node> pq;
    for (int v = 1; v <= n; v++) {
        pq.push({ uf.cc[v], uf.pp[v], uf.avg[v], v });
    }

    while (!pq.empty()) {
        Node now = pq.top();
        pq.pop();

        if (uf.cc[now.v] != now.cc || vis[now.v]) continue;
        vis[now.v] = 1;

        int p = uf.find(d[now.v]);
        int p2 = uf.find2(d[now.v]);
        ans[p2] = now.v;
        uf.merge(p, now.v);

        if (p != 0) {
            pq.push({ uf.cc[p], uf.pp[p], uf.avg[p], p });
        }
    }
}

double get_val() {
    double ret = 0;

    double accp = 1;
    ll accc = 0;
    for (int i = 0; ans[i] != 0; i = ans[i]) {
        int v = ans[i];
        ret += accp * (1 - p[v]) * (accc + c[v]);

        accp *= p[v];
        accc += c[v];
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    for (int i = 0; ans[i] != 0; i = ans[i]) {
        cout << ans[i] << '\n';
    }

    // cout << uf.avg[uf.find(0)] << '\n';
    // cout << get_val() << '\n';
}

// p[i] -> c[i]
// (1 - p[i]) -> c[i]

// 어떤 최적해 가정
// u := opt[i], v := opt[i + 1]
// swap(u, v)

// (1 - p[u]) * c[u] + p[u] * (1 - p[v]) * (c[u] + c[v])
// >
// (1 - p[v]) * c[v] + p[v] * (1 - p[u]) * (c[u] + c[v])

// 0.1 * 10 + 0.9 * 0.5 * (10 + 100) + 0.9 * 0.5 * 0.9 * (10 + 100 + 200) + 0.9 * 0.5 * 0.1* 0.5 * (10 + 100 + 200 + 10)