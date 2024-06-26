#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const ll INF = 1e18 + 7;

int n, m, st, en;
ll add, del;

vector<ll> a;
ll dp[101][505][2];

ll f(int idx, int now, int bit) {
    ll& ret = dp[idx][now][bit];
    if (ret != -1) return ret;
    if (now == sz(a)) {
        return ret = add * abs(idx - en);
    }

    ret = INF;

    int ladder = 0;
    for (int i = now; i < sz(a); i++) {
        if (a[i] == idx - 1 || a[i] == idx) {
            if (a[i] == idx - 1) {
                ret = min(ret, f(idx - 1, i + 1, 0));
                ret = min(ret, f(idx, i + 1, 0) + del);
            }
            if (a[i] == idx) {
                ret = min(ret, f(idx + 1, i + 1, 0));
                ret = min(ret, f(idx, i + 1, 0) + del);
            }
            ladder = 1;
            break;
        }
    }
    if (!ladder) ret = f(idx, sz(a), 0);

    if (bit) return ret;

    for (int i = 1; i <= n; i++) {
        ret = min(ret, f(i, now, 1) + abs(i - idx) * add);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 505; j++) {
            dp[i][j][0] = dp[i][j][1] = -1;
        }
    }

    cin >> n >> m >> st >> en;
    cin >> del >> add;

    a.resize(m);
    for (auto& i : a) cin >> i;
    
    cout << f(st, 0, 0);

    return 0;
}