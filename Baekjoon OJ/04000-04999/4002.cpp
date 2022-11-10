#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define fr first
#define sc second

int n, par[101010], r;
ll m, w[101010], l[101010];
vector<int> chd[101010], dep[101010];

int in[101010], out[101010], cnt;
set<int> s;
int wbyin[101010];

pair<ll, int> dp[101010];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p >> w[i] >> l[i];
        if (p == 0) r = i;
        else {
            par[i] = p;
            chd[p].push_back(i);
        }
    }
}

void dfs(int v, int prv, int d) {
    in[v] = ++cnt;
    wbyin[in[v]] = w[v];
    s.insert(in[v]);

    dep[d].push_back(v);
    for (auto& i : chd[v]) {
        dfs(i, v, d + 1);
    }

    out[v] = cnt;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
    
    dfs(r, 0, 1);

    ll ans = 0;

    for (int d = n; d >= 1; d--) {
        for (int v : dep[d]) {
            auto& res = dp[v];

            res.fr += w[v], res.sc = 1;
            for (int i : chd[v]) {
                res.fr += dp[i].fr, res.sc += dp[i].sc;
            }

            if (res.fr > m) {
                vector<int> arr;

                ll lb = (m + res.sc - 1) / res.sc;

                auto it = s.lower_bound(in[v]);
                while (it != s.end() && *it <= out[v]) {
                    if (wbyin[*it] < lb) {
                        it++;
                        continue;
                    }
                    arr.push_back({ *it });
                    it++;
                }

                sort(arr.begin(), arr.end(), [&](int u, int v) {
                    return wbyin[u] > wbyin[v];
                });

                int idx = 0;
                while (res.fr > m) {
                    res.fr -= wbyin[arr[idx]], res.sc--;
                    s.erase(arr[idx]);
                    idx++;
                }
            }

            ans = max(ans, res.sc * l[v]);
        }
    }

    cout << ans;

	return 0;
}