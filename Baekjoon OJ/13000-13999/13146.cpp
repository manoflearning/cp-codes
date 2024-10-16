#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>

const int INF = 1e9 + 7;

vector<int> uf(1010101, -1);
vector<int> L(1010101), R(1010101), MX(1010101);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    L[V] = min(L[V], L[U]);
    R[V] = max(R[V], R[U]);
    MX[v] = max(MX[V], MX[U]);
    uf[U] = V;
}

int n, a[1010101];

void input() {
    cin >> n;
    a[0] = a[n + 1] = INF;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        L[i] = R[i] = i;
        MX[i] = a[i];
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

    for (int i = 1; i < n; i++) {
        if (a[i] == a[i + 1]) merge(i, i + 1);
    }

    set<int> s;
    for (int i = 1; i <= n; i++) {
        s.insert(find(i));
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (auto& i : s)
        pq.push({ MX[i], i });

    long long ans = 0;
    while (!pq.empty()) {
        auto [ww, v] = pq.top();
        int w = MX[find(v)];
        pq.pop();

        if (w != ww) continue;

        int lw = a[L[find(v)] - 1] < w ? INF : a[L[find(v)] - 1];
        int rw = a[R[find(v)] + 1] < w ? INF : a[R[find(v)] + 1];

        if (lw != INF && lw <= rw) {
            ans += lw - w;
            w = lw;
            merge(v, L[find(v)] - 1);
        }
        if (rw != INF && lw >= rw) {
            ans += rw - w;
            merge(v, R[find(v)] + 1);
        }
    }

    cout << ans;
}