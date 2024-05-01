// number of edges = N - 1
// 

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int N, K, M;
int C[101010];
struct Edge {
    int X, Y; ll W;
    bool operator<(const Edge& rhs) const {
        return W < rhs.W;
    }
};
vector<Edge> e;

vector<int> uf(101010, -1);
vector<unordered_map<int, ll>> mps(101010);

ll ans[101010];

int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}

void merge(int u, int v, ll w) {
    int U = find(u), V = find(v);

    if (U == V) return;

    if (sz(mps[U]) > sz(mps[V])) {
        swap(U, V);
        swap(u, v);
    }

    // mps[U][C[u]] += 1;
    // mps[V][C[v]] += 1;

    for (auto& i : mps[U]) ans[i.fr] += i.sc * mps[V][i.fr] * w;
    for (auto& i : mps[U]) mps[V][i.fr] += i.sc;
    mps[U].clear();

    uf[U] = V;
}

void input() {
    cin >> N >> K >> M;
    for (int i = 1; i <= N; i++) cin >> C[i];
    e.resize(M);
    for (auto& i : e)
        cin >> i.X >> i.Y >> i.W;
}

void solve() {
    sort(e.rbegin(), e.rend());

    for (int v = 1; v <= N; v++)
        mps[v][C[v]] = 1;

    for (auto& i : e) {
        if (find(i.X) == find(i.Y)) continue;
        merge(i.X, i.Y, i.W);
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

    solve();

    for (int i = 1; i <= K; i++)
        cout << ans[i] << '\n';
}