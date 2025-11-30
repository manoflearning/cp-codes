#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 303030;

int n, par[N];
vector<int> chd[N];

int dp1[N], dp2[N], dp3[N];
// dp1[v] = v를 루트로 하는 서브트리에서 한쪽 끝을 v로 하는 최장경로의 길이
// dp2[v] = v를 루트로 하는 서브트리에서의 지름
// dp3[v] = v의 자손들을 제외한 나머지 정점들을 가지고 만들 수 있는 v를 한쪽 끝으로 하는 최장경로의 길이

// ans[v] = dp2[v] + dp3[v] + 1

void dfs1(int v) {
    int mx0 = 0, mx1 = -1;
    for (auto &i : chd[v]) {
        // dp3[i] = dp3[v] + 1;

        dfs1(i);

        if (dp1[i] + 1 >= mx0) {
            mx1 = mx0;
            mx0 = dp1[i] + 1;
        } else if (dp1[i] + 1 > mx1) {
            mx1 = dp1[i] + 1;
        }

        dp2[v] = max(dp2[v], dp2[i]);
    }
    dp1[v] = mx0;
    dp2[v] = max(dp2[v], mx0 + mx1);

    // cout << v << ' ' << dp1[v] << ' ' << dp2[v] << ' ' << dp3[v] << '\n';
}

void dfs2(int v) {
    int mx0 = 0, mx1 = 0;
    for (auto &i : chd[v]) {
        if (dp1[i] + 1 >= mx0) {
            mx1 = mx0;
            mx0 = dp1[i] + 1;
        } else if (dp1[i] + 1 > mx1) {
            mx1 = dp1[i] + 1;
        }
    }

    for (auto &i : chd[v]) {
        int &x = dp3[i];
        if (dp1[i] + 1 != mx0) x = max(mx0, dp3[v]) + 1;
        else x = max(mx1, dp3[v]) + 1;

        dfs2(i);
    }

    // cout << v << ' ' << dp1[v] << ' ' << dp2[v] << ' ' << dp3[v] << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 2; i <= n; i++) {
        cin >> par[i];
        chd[par[i]].push_back(i);
    }

    dfs1(1);
    dfs2(1);

    for (int i = 2; i <= n; i++) {
        cout << max(dp2[1], dp2[i] + dp3[i]) << '\n';
    }
}
