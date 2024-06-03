#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, a[202020];
vector<int> t[202020];

void input() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int x; cin >> x;
        t[x].push_back(i);
    }
    for (int i = 1; i <= n; i++) cin >> a[i];
}

ll dp[202020][2];

ll f(int v, int bit) {
    ll& ret = dp[v][bit];
    if (ret != -1) return ret;

    ret = 0;
    if (bit == 0) {
        for (auto& i : t[v]) {
            ret += max(f(i, 0), f(i, 1));
        }
    }
    if (bit == 1) {
        ll sum = 0;
        for (auto& i : t[v]) {
            sum += max(f(i, 0), f(i, 1));
        }

        for (auto& i : t[v]) {
            if (f(i, 0) < f(i, 1)) {
                ll res = sum + f(i, 0) - f(i, 1) + a[v] * a[i];
                ret = max(ret, res);
            }
            else {
                ll res = sum + a[v] * a[i];
                ret = max(ret, res);
            }
        }
    }
    
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    memset(dp, -1, sizeof(dp));

    cout << max(f(1, 0), f(1, 1));
}