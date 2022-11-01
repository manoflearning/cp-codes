#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int n, par[202020];
vector<int> chd[202020];
ll w[202020];
ll dp1[202020]; // dp1[v] = v를 팀장으로 하는 팀의 점수의 최댓값.
ll dp2[202020]; // dp2[v] = v의 어떤 자손 노드를 팀장으로 하고, 팀 dp1[v]와 노드가 겹치지 않는 팀의 점수의 최댓값.
ll dp3[202020]; // dp3[v] = v의 서브트리에서 만들 수 있는 팀의 점수의 최댓값.

ll ans = -INF;

void input() {
    cin >> n;
    for (int v = 1; v <= n; v++) {
        cin >> w[v] >> par[v];
        if (v != 1) chd[par[v]].push_back(v);
    }
}

void dfs(int v) {
    dp1[v] = w[v];
    dp2[v] = -INF;

    ll mx1 = -INF, mx2 = -INF;
    for (auto& i : chd[v]) {
        dfs(i);

        if (dp1[i] > 0) {
            dp1[v] += dp1[i];
            dp2[v] = max(dp2[v], dp2[i]);
        }
        else {
            dp2[v] = max(dp2[v], dp3[i]);
        }

        if (dp3[i] > mx1) {
            mx2 = mx1, mx1 = dp3[i];
        }
        else if (dp3[i] > mx2) {
            mx2 = dp3[i];
        }
    }

    dp3[v] = max(dp1[v], mx1);
    ans = max(ans, dp1[v] + dp2[v]);

    ans = max(ans, mx1 + mx2);
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(1);

    cout << ans;

    return 0;
}