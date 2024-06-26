#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

const ll INF = 1e15;

int n, k;
pll a[15];
ll w[15], sum[1 << 15], dp[1 << 15][15];

ll f(int bit, int x) {
    ll& ret = dp[bit][x];
    if (ret != -1) return ret;
    if (bit == 0) return ret = 0;
    if (x == k) return ret = INF;
    
    ret = INF;
    for (int subset = bit; subset > 0; subset = (subset - 1) & bit) {
        ret = min(ret, sum[subset] + f(bit - subset, x + 1));
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

    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> a[i].fr >> a[i].sc >> w[i];
    
    for (int i = 0; i < (1 << n); i++) {
        pll res = { 0, 0 };
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                res.fr = max(res.fr, a[j].fr);
                res.sc = max(res.sc, a[j].sc);
            }
        }
        for (int j = 0; j < n; j++)
            if (i & (1 << j)) sum[i] += (res.fr * res.sc - a[j].fr * a[j].sc) * w[j];
    }

    for (int i = 0; i < (1 << 15); i++)
        memset(dp[i], -1, sizeof(dp[i]));

    cout << f((1 << n) - 1, 0);
}