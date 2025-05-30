#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

struct Edge {
    int op, v;
};

int n, m;
vector<Edge> adj[10101];
int imp = 0, vi[10101];
int team[10101], acnt, bcnt;

vector<int> a;
int sum = 0, dp[10101];

void init() {
    for (int i = 0; i < 10101; i++) {
        adj[i].clear();
        vi[i] = team[i] = 0;
    }
    imp = 0;

    a.clear();
    sum = 0;
    memset(dp, 0, sizeof(dp));
}

void dfs(int v, int t) {
    vi[v] = 1;
    team[v] = t;
    
    if (t == 1) acnt++;
    else bcnt++;

    for (auto& i : adj[v]) {
        int nt = 0;
        if (i.op == 1) nt = t;
        else nt = (t == 1 ? 2 : 1);

        if (vi[i.v]) {
            if (team[i.v] != nt) imp = 1;
        }
        else dfs(i.v, nt);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    int tc = 5;
    while (tc--) {
        init();

        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int op, u, v;
            cin >> op >> u >> v;
            adj[u].push_back({ op, v });
            adj[v].push_back({ op, u });
        }

        for (int i = 1; i <= n; i++) {
            if (!vi[i]) {
                acnt = bcnt = 0;
                dfs(i, 1);
                a.push_back(abs(acnt - bcnt));
                sum += abs(acnt - bcnt);
            }
        }
        

        if (imp) {
            cout << -1 << '\n';
            continue;
        }
        
        dp[0] = 1;
        for (int i = 0; i < sz(a); i++) {
            for (int j = sum; j >= 0; j--) {
                if (dp[j]) {
                    dp[j + a[i]] = 1;
                }
            }
        }
        
        int ans = 1e9 + 7;
        for (int i = 0; i <= sum; i++) {
            if (dp[i]) {
                ans = min(ans, abs(i - (sum - i)));
            }
        }

        cout << ans << '\n';
    }

    return 0;
}