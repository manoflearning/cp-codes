#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 101010;
const int MAXK = 505;

int N, K;
vector<int> t[MAXN];

void input() {
    cin >> N >> K;
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
}

int dep[MAXN], par[MAXN];
vector<int> byDep[MAXN];

void dfs(int v, int prv) {
    dep[v] = dep[prv] + 1;
    par[v] = prv;
    byDep[dep[v]].push_back(v);
    for (auto& i : t[v]) {
        if (i != prv) dfs(i, v);
    }
}

vector<ll> dp[MAXN];
// dp[v][cnt] = v를 루트로 하는 서브트리에서 cnt개의 호텔을 배치했을 때 거리 합 최댓값

void solve() {
    for (int d = N; d >= 1; d--) {
        for (auto v : byDep[d]) {
            dp[v].resize(K + 1);

            int top = 0;
            for (auto u : t[v]) {
                if (u == par[v]) continue;

                vector<ll> tmp = dp[v];

                int lazyTopModify = top;
                for (int i = 0; i < sz(dp[u]); i++) {
                    for (int j = 0; j <= top && i + j < sz(dp[v]); j++) {
                        dp[v][i + j] = max(dp[v][i + j], tmp[j] + (K - i) * i + dp[u][i]);
                        lazyTopModify = max(lazyTopModify, i + j);
                    }
                }
                top = lazyTopModify;

                dp[u].clear();
                dp[u].shrink_to_fit();
            }

            top = min(top + 1, K);
            for (int i = top; i >= 1; i--) {
                dp[v][i] = max(dp[v][i], dp[v][i - 1]);
            }

            dp[v].resize(min(K + 1, top + 1));
            dp[v].shrink_to_fit();

            // for (int i = 0; i < sz(dp[v]); i++) {
            //     cout << v << ' ' << i << ' ' << dp[v][i] << '\n';
            // }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(1, 0);

    solve();

    // assert(K < sz(dp[1]));
    cout << dp[1][K];
}