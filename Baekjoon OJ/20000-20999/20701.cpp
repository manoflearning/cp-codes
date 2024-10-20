#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n, p[22], dep[22], mxd;
vector<int> t[22], dp[22], bydep[22];

void dfs(int v) {
    mxd = max(mxd, dep[v]);
    bydep[dep[v]].push_back(v);
    for (auto& i : t[v]) {
        dep[i] = dep[v] + 1;
        dfs(i);
    }
}

vector<int> sum(const vector<int>& x, const vector<int>& y) {
    if (x.empty()) return y;
    
    vector<int> ret, rx;

    for (int i = sz(x) - 1; i >= 0; i--) rx.push_back(x[i]);
    
    for (int i = 0; i < sz(y); i++) {
        if (i & 1) for (auto& j : rx) ret.push_back(j);
        else for (auto& j : x) ret.push_back(j);
        ret.push_back(y[i]);
    }

    if (sz(y) & 1) for (auto& j : rx) ret.push_back(j);
    else for (auto& j : x) ret.push_back(j);

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int v = 2; v <= n; v++) {
        cin >> p[v];
        t[p[v]].push_back(v);
    }

    dep[1] = 1;
    dfs(1);

    for (int d = mxd; d >= 1; d--) {
        for (auto& v : bydep[d]) {
            dp[v].push_back(v);
            if (t[v].empty()) continue;

            vector<int> res;
            for (auto& i : t[v]) {
                res = sum(res, dp[i]);
            }

            for (auto& i : res) 
                dp[v].push_back(i);
        }
    }

    cout << sz(dp[1]) - 1 << '\n';
    for (int i = 1; i < sz(dp[1]); i++)
        cout << dp[1][i] << ' ';
}