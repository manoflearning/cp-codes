#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int MOD = 998244353;

ll p10[20];
int n;
ll a[202020];

int dec_idx(ll x) {
    int flag = 1, idx = 0;
    for (; flag <= x; flag *= 10, idx++);
    return idx;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    p10[0] = 1;
    for (int i = 1; i <= 15; i++)
        p10[i] = 10 * p10[i - 1] % MOD;

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    ll ans = 0, sum = 0;
    for (int i = n; i >= 1; i--) {
        ans = (ans + sum * a[i]) % MOD;
        ans = (ans + (i - 1) * a[i]) % MOD;
        sum = (sum + p10[dec_idx(a[i])]) % MOD;
    }

    cout << ans;
}