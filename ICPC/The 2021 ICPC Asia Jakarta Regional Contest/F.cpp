#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX = 1'000'000;

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

vector<int> uf(101010, -1);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    uf[V] += uf[U];
    uf[U] = V;
}

int n, a[101010];
struct Edge { int u, v; };
vector<Edge> e[MAX + 1];
int ans = 0;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] > 1) ans = 1;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        int g = gcd(a[u], a[v]);
        for (int x = 2; x * x <= g; x++) {
            if (g % x == 0) e[x].push_back({ u, v });
            while (g % x == 0) g /= x;
        }
        if (g > 1) e[g].push_back({ u, v });
    }
}

void solve() {
    for (int p = 2; p <= MAX; p++) {
        for (auto& i : e[p]) {
            merge(i.u, i.v);
            ans = max(ans, -uf[find(i.u)]);
        }

        for (auto& i : e[p])
            uf[i.u] = -1, uf[i.v] = -1;
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

    cout << ans;
}