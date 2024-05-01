#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second
#define PI_M_2 3.14159265358979323846264338327950288

int N;
ll x[1010], y[1010], r[1010];

struct Edge {
    double w;
    int u, v;
    bool operator<(const Edge& rhs) const {
        return w < rhs.w;
    }
};
vector<Edge> edge;

vector<int> uf(1010, -1);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    uf[U] += uf[V];
    uf[V] = U;
}

void input() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> x[i] >> y[i] >> r[i];
    }
}

double weight(int i, int j) {
    ll val1 = (x[i] - x[j]) * (x[i] - x[j]);
    val1 += (y[i] - y[j]) * (y[i] - y[j]);
    ll val2 = (r[i] + r[j]) * (r[i] + r[j]);
    if (val1 <= val2) return 0;

    double ret = 0;
    ret += 2 * sqrt((double)val1 - (r[i] - r[j]) * (r[i] - r[j]));
    double cos_theta = abs(r[i] - r[j]) / sqrt(val1);
    double theta = acos(cos_theta);

    ret += (2 * PI_M_2 - 2 * theta) * max(r[i], r[j]);
    ret += 2 * theta * min(r[i], r[j]);

    return ret;
}

void build_graph() {
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            double w = weight(i, j);
            edge.push_back({ w, i, j });
        }
    }
}

double ans = 0;
void solve() {
    sort(edge.begin(), edge.end());

    for (auto& i : edge) {
        if (find(i.u) == find(i.v)) continue;
        merge(i.u, i.v);
        ans += i.w;
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

    build_graph();

    solve();

    cout << fixed;
    cout.precision(7);
    cout << ans;
}