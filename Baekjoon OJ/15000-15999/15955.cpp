#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pli pair<ll, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

struct Query {
    int u, v; ll x;
    int idx;
    bool operator<(const Query& rhs) const {
        return x < rhs.x;
    }
};

struct Edge {
    ll len; int u, v;
    bool operator<(const Edge& rhs) const {
        return len < rhs.len;
    }
};

vector<int> p(252525, -1);

int find(int x) {
    if (p[x] < 0) return x;
    return p[x] = find(p[x]);
}

void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    p[U] += p[V];
    p[V] = U;
}

int n, m;
vector<pli> xx, yy;
vector<Query> q;
vector<string> ans;
vector<Edge> e;

void input() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        xx.push_back({ x, i + 1 });
        yy.push_back({ y, i + 1 });
    }

    q.resize(m);
    ans.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> q[i].u >> q[i].v >> q[i].x;
        q[i].idx = i;
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

    sort(xx.begin(), xx.end());
    sort(yy.begin(), yy.end());

    for (int i = 0; i + 1 < n; i++) {
        e.push_back({ xx[i + 1].fr - xx[i].fr, xx[i].sc, xx[i + 1].sc });
        e.push_back({ yy[i + 1].fr - yy[i].fr, yy[i].sc, yy[i + 1].sc });
    }

    sort(q.begin(), q.end());
    sort(e.begin(), e.end());

    int prv = 0;
    for (auto& i : q) {
        while (prv < sz(e) && e[prv].len <= i.x) {
            merge(e[prv].u, e[prv].v);
            prv++;
        }

        if (find(i.u) == find(i.v)) ans[i.idx] = "YES";
        else ans[i.idx] = "NO";
    }

    for (auto& i : ans)
        cout << i << '\n';

    return 0;
}