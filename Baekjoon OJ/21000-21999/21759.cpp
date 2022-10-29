#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, par[202020];
vector<int> chd[202020];
ll w[202020], dp[202020];

void init() {
    memset(dp, -1, sizeof(dp));
}

void input() {
    cin >> n;
    for (int v = 1; v <= n; v++) {
        cin >> w[v] >> par[v];
        if (par[v] > 0) 
            chd[par[v]].push_back(v);
    }
}

ll f(int v) {
    ll& ret = dp[v];
    if (ret != -1) return ret;
    if (chd[v].empty()) return ret = w[v];

    ret = w[v];
    for (auto& i : chd[v]) {
        ll res = f(i);
        
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    for (int v = 1; v <= n; v++) {

    }

    return 0;
}