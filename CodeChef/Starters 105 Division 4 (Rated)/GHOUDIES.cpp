#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n;
struct Edge { int v; char c; };
vector<vector<Edge>> t;
vector<int> dep, par;

vector<vector<int>> dp1, dp2;
string s;

int ans = 0;

void init() {
    t.clear();
    dep.clear();
    par.clear();
    dp1.clear();
    dp2.clear();
    s.clear();
    ans = 0;
}

void input() {
    cin >> n;
    t.resize(n + 1);
    dep.resize(n + 1);
    par.resize(n + 1);
    dp1.resize(n + 1);
    dp2.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v; char c;
        cin >> u >> v >> c;
        t[u].push_back({ v, c });
        t[v].push_back({ u, c });
    }
    cin >> s;
}

void dfs(int v, int prv) {
    par[v] = prv;
    dep[v] = dep[prv] + 1;
    for (auto& i : t[v]) {
        if (i.v == prv) continue;
        dfs(i.v, v);
    }
}

void bottomup() {
    vector<int> ord;
    for (int v = 1; v <= n; v++) 
        ord.push_back(v);
    
    sort(ord.begin(), ord.end(), [&](int p1, int p2) {
        return dep[p1] > dep[p2]; 
    });

    for (auto v : ord) {
        dp1[v].resize(sz(s));
        dp2[v].resize(sz(s));
        
        int res = 0;

        for (auto& e : t[v]) {
            if (e.v == par[v]) continue;

            vector<int> dp3 = dp1[e.v];
            vector<int> dp4 = dp2[e.v];

            for (int i = 0; i < sz(s); i++) {
                if (e.c == s[i]) {
                    dp3[i] = (i > 0 ? dp1[e.v][i - 1] + 1 : 1);
                }
                if (i > 0) dp3[i] = max(dp3[i], dp3[i - 1]);

                res = max(res, dp3[i] + (i + 1 < sz(s) ? dp2[v][i + 1] : 0));
            }
            for (int i = sz(s) - 1; i >= 0; i--) {
                if (e.c == s[i]) {
                    dp4[i] = (i + 1 < sz(s) ? dp2[e.v][i + 1] + 1 : 1);
                }
                if (i + 1 < sz(s)) dp4[i] = max(dp4[i], dp4[i + 1]);

                res = max(res, (0 < i ? dp1[v][i - 1] : 0) + dp4[i]);
            }

            for (int i = 0; i < sz(s); i++) {
                dp1[v][i] = max(dp1[v][i], dp3[i]);
                dp2[v][i] = max(dp2[v][i], dp4[i]);
            }

            dp1[e.v].clear();
            dp1[e.v].shrink_to_fit();
            dp2[e.v].clear();
            dp2[e.v].shrink_to_fit();
        }

        // cout << v << ' ' << res << '\n';
        ans = max(ans, res);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
	int tc; cin >> tc;
	while (tc--) {
	    init();
	    
	    input();
	    
	    dfs(1, 0);
	    
	    bottomup();

        cout << ans << '\n';
	}
}
