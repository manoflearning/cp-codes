#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

struct UF {
    vector<int> uf;
    void init(int n) {
        uf.clear();
        uf.resize(n + 1, -1);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[U] = V;
    }
}uf;

int N, M, K;
int par[101010], X[101010];
int A[101010], B[101010], C[101010];
int T[101010];
string ans[101010];

void input() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) cin >> par[i];
    for (int i = 1; i <= M; i++) cin >> X[i];
    for (int i = 1; i <= K; i++) {
        cin >> A[i] >> B[i] >> C[i];
    }
}

void solve() {
    for (int i = 1; i <= N; i++) T[i] = M;
    for (int i = 1; i <= M; i++)
        T[X[i]] = min(T[X[i]], i - 1);

    vector<int> ord_node(N), ord_query(K);
    iota(all(ord_node), 1);
    iota(all(ord_query), 1);
    sort(all(ord_node), [](int p1, int p2) { return T[p1] > T[p2]; });
    sort(all(ord_query), [](int p1, int p2) { return A[p1] > A[p2]; });

    uf.init(N);

    int i = 0;
    for (auto& q : ord_query) {
        while (i < sz(ord_node) && T[ord_node[i]] >= A[q]) {
            if (par[ord_node[i]] != -1)
                uf.merge(ord_node[i], par[ord_node[i]]);
            i++;
        }

        ans[q] = (uf.find(B[q]) == uf.find(C[q]) ? "Same Same;" : "No;");
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