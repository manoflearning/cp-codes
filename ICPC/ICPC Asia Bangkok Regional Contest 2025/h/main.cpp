#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;
constexpr int N = 50505;
constexpr int M = 505;

struct Seg {
    int n, t[200'000];
    void build() {
        n = 100'000;
        memset(t, 0, sizeof(t));
    }
    void modify(int p, int val) {
        p += n;
        if (val <= t[p]) return;
        t[p] = val;
        for (; p > 1; p >>= 1) {
            t[p >> 1] = max(t[p], t[p ^ 1]);
        }
    }
    int query(int l, int r) {
        int ret = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ret = max(ret, t[l++]);
            if (r & 1) ret = max(ret, t[--r]);
        }
        return ret;
    }
} seg;

int n, a[N];
int dp[N][M], opt[N][M], idxs[101010];
// dp[i][j] = a[i]를 마지막 원소로 하고 길이가 j인 수열의 마지막 diff의 최솟값

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dp[i][j] = INF;
        }
    }

    // base case    
    for (int i = 1; i <= n; i++) {
        dp[i][1] = 0;
    }
    
    // inductive step
    for (int k = 2; k < M; k++) {
        seg.build();

        bool is_updated = 0;

        for (int i = 1; i <= n; i++) {
            int val = seg.query(1, a[i]);

            if (val) {
                dp[i][k] = a[i] - val;
                opt[i][k] = idxs[val];
                is_updated = 1;
            }

            if (a[i] + dp[i][k - 1] < (int)1e5) {
                idxs[a[i]] = i;
                seg.modify(a[i] + dp[i][k - 1], a[i]);
            }
        }

        if (!is_updated) break;
    }

    int mx_i = -1, mx_k = -1;
    for (int k = M - 1; k >= 1; k--) {
        for (int i = 1; i <= n; i++) {
            if (dp[i][k] == INF) continue;
            mx_i = i, mx_k = k;

            k = 0; break;
        }
    }

    vector<int> ans;
    while (1) {
        ans.push_back(mx_i);
        if (mx_k == 1) break;
        mx_i = opt[mx_i][mx_k], mx_k--;
    }

    assert(!ans.empty());

    reverse(all(ans));

    cout << sz(ans) << '\n';
    for (auto &i : ans) {
        cout << i << ' ';
    }
}