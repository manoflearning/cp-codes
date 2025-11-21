#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;
constexpr int N = 202020;
constexpr int M = 202020;

int n, m, k;
string s;

vector<vector<vector<int>>> f1(const vector<bool> &in) {
    vector<vector<vector<int>>> dp1(
        sz(in) + 1, 
        vector<vector<int>>(2, 
            vector<int>(sz(in) + 1, -INF)
        ));

    if (sz(in) == 1) {
        dp1[0][in[0]][0] = in[0];
        return dp1;
    }

    // base case
    dp1[1][in[1]][0] = in[0] + in[1];
    dp1[1][!in[1]][1] = !in[0] + !in[1];

    // inductive step
    for (int i = 2; i < sz(in); i++) {
        for (int b = 0; b < 2; b++) {
            for (int j = 0; j <= sz(in); j++) {
                if (dp1[i - 1][b][j] == -INF) continue;

                dp1[i][in[i]][j] = max(dp1[i][in[i]][j], dp1[i - 1][b][j] + in[i]);
                if (j + 1 <= sz(in))
                    dp1[i][!in[i]][j + 1] = max(dp1[i][!in[i]][j + 1], dp1[i - 1][b][j] + !in[i] + (b ? -1 : +1));
            }
        }
    }

    return dp1;
}

int solve() {
    vector<int> dp2(m + 1, -INF);
    dp2[0] = 0;

    for (int i = 0; i < k; i++) {
        vector<bool> in;
        for (int j = (i ? i : i + k); j < sz(s); j += k) {
            if (s[j - 1] != s[j]) {
                in.push_back(1);
            } else {
                in.push_back(0);
            }
        }

        if (in.empty())
            continue;

        vector<vector<vector<int>>> dp1 = f1(in);

        vector<int> nxt(m + 1, -INF);
        for (int x = 0; x <= m; x++) {
            for (int j = 0; j < sz(dp1); j++) {
                if (m < x + j) break;
                nxt[x + j] = max(nxt[x + j], dp2[x] + dp1[sz(in) - 1][0][j]);
                nxt[x + j] = max(nxt[x + j], dp2[x] + dp1[sz(in) - 1][1][j]);
            }
        }
        dp2 = nxt;
    }

    int ret = 0;
    for (int i = 0; i <= m; i++) {
        ret = max(ret, dp2[i]);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    string t; cin >> t;

    int ans = 0;
    s = "R" + t + "R";
    ans = max(ans, solve());
    s = "R" + t + "B";
    ans = max(ans, solve());
    s = "B" + t + "R";
    ans = max(ans, solve());
    s = "B" + t + "B";
    ans = max(ans, solve());
    cout << ans - 1;
}