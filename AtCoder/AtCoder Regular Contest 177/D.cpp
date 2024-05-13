// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 998244353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct UF {
    vector<int> uf;
    void init(int N) {
        uf.clear();
        uf.resize(N + 1, -1);
    }
    int find(int v) {
        if (uf[v] < 0) return v;
        return uf[v] = find(uf[v]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[U] += uf[V];
        uf[V] = U;
    }
}uf;

int N
ll H, X[202020]; // the heights of all poles are equal

int chunk[202020];
ll ans[202020];

void input() {
    cin >> N >> H;
    for (int i = 1; i <= N; i++) cin >> X[i];
}

void build_chunk() {
    vector<int> ord(N);
    iota(all(ord), 1);
    sort(all(ord), [](int p1, int p2) {
        return X[p1] < X[p2];
    });

    uf.init(N);
    for (int i = 0; i + 1 < sz(ord); i++) {
        int u = ord[i], v = ord[i + 1];
        if (X[u] + H > X[v]) uf.merge(u, v);
    }

    for (int i = 1; i <= N; i++) chunk[i] = uf.find(i);
}

// if it ends in time t_i:
// * all the poles in one side (suppose left) are already fallen:
//   * for each chunk k, there exists pole j s.t. t_j < t_i
//     * if max(X[k]) + H > X[i]: k must be fallen to the opposite dir
//       * for p := max_p(X[p]) (i.e., rightmost pole p in the chunk k), t_p < t_i is true
//       * |possible cases| = 1
//     * if max(X[k]) + H <= X[i]: the dir doesn't matter
//       * if the leftmost pole p satisfies t_p < t_i, |possible cases|++
//       * if the rightmost pole p satisfies t_p < t_i, |possible cases|++
//       * for all the adjacent (p, q) satisfies t_p < t_i, t_q < t_i, |possible cases|++
// * all the poles in one side (suppose right) are not fallen yet:
//   * for all the poles j in the side, t_i < t_j

// to modify X[i] := 10^9 - X[i], we can handle the reverse cases

void solve() {
    vector<int> ord(N);
    iota(all(ord), 1);
    sort(all(ord), [](int p1, int p2) {
        return X[p1] < X[p2];
    });

    vector<ll> l_cases(N + 1, 1), chunk_cnt(N + 1, 1), l_tot(N + 1);
    for (int i = 1; i < sz(ord); i++) {
        int v = ord[i], prv = ord[i - 1];
        if (chunk[prv] != chunk[v]) {
            l_cases[v] = 2 * l_cases[prv] % MOD;
            chunk_cnt[v] = 1 + chunk_cnt[prv];
        }
        else {
            l_cases[v] = l_cases[prv];
            chunk_cnt[v] = chunk_cnt[prv];
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

    input();

    build_chunk();

    // (1) left chunks are already fallen
    // (2) right chunks are not fallen yet
    solve(); 

    // (1) left chunks are not fallen yet
    // (2) right chunks are already fallen
    for (int i = 1; i <= N; i++)
        X[i] = (int)(1e9) - X[i];
    
    solve();

    // print answer
    for (int i = 1; i <= N; i++)
        cout << ans[i] << ' ';
}