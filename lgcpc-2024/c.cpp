#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int N = 404, K = 808;
const int INF = 1e9 + 7;

int popcount(int bit) {
    int ret = 0;
    for (int i = 0; (1 << i) <= bit; i++) {
        if ((1 << i) & bit) ret++;
    }
    return ret;
}

int n, k;
int m[N][K];

int dp[33][1 << 15], pc[1 << 15];
int case12() {
    // initialize
    for (int i = 0; i < 33; i++) {
        for (int j = 0; j < (1 << 15); j++) {
            dp[i][j] = -INF;
            pc[j] = popcount(j);
        }
    }

    // base case
    dp[0][0] = 0;

    // inductive step
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < (1 << n); j++) {
            dp[i][j] = dp[i - 1][j];
        }

        vector<int> arr;
        for (int j = 0; j < n; j++) {
            if (m[j][i] == 1) arr.push_back(j);
        }

        for (int j = 0; j < (1 << n); j++) {
            if (dp[i - 1][j] < 0) continue;
            if (i + 1 < 2 * pc[j] + 2) continue;
            for (auto& p : arr) {
                if (j & (1 << p)) continue;
                dp[i][j | (1 << p)] = max(dp[i][j | (1 << p)], 1 + dp[i - 1][j]);
            }
        }
    }

    // get answer
    int ret = 0;
    for (int j = 0; j < (1 << n); j++) {
        ret = max(ret, dp[k - 1][j]);
    }
    return ret;
}

bool is_case_3() {
    if (n >= k) return 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (m[i][j] == 1) return 0;
        }
    }
    return 1;
}

int rcnt[N], ccnt[K];
int case3() {
    vector<vector<int>> arr;
    vector<int> cnt(n);
    for (int x = n; x < k; x++) {
        vector<int> tmp;
        for (int y = 0; y < n; y++) {
            if (m[y][x]) {
                tmp.push_back(y);
            }
            cnt[y] += m[y][x];
        }
        arr.push_back(tmp);
    }

    sort(arr.begin(), arr.end(), [&](const vector<int>& p1, const vector<int>& p2) {
        return sz(p1) < sz(p2);
    });

    for (auto& it : arr) {
        int opt = -1;
        for (auto& i : it) {
            if (opt == -1 || cnt[i] < cnt[opt]) {
                i = opt;
            }
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

    // input
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> m[i][j];
        }
    }

    if (is_case_3()) cout << case3();
    else if (n <= 15 && k <= 30) cout << case12();
    else cout << -1;
}

// observations:
// * time 2t => ans <= t
// * 