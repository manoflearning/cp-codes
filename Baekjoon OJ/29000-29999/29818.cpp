#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
struct Assignment {
    ll T, D, P;
};
vector<Assignment> a;
pair<ll, ll> dp[1 << 20];

pair<ll, ll> f(int bit) {
    auto& ret = dp[bit];
    if (ret.first != -1) return ret;
    if (bit == (1 << n) - 1) return ret = { 0, 0 };

    ll time = 0;
    for (int i = 0; i < n; i++) {
        if ((1 << i) & bit) time += a[i].T;
    }

    ret = { 0, 0 };
    for (int i = 0; i < n; i++) {
        if ((1 << i) & bit) continue;
        
        ll add = -1;
        if (time + a[i].T <= a[i].D) add = a[i].P;
        else if (time + a[i].T <= a[i].D + 24) add = a[i].P / 2;
        else add = 0;

        auto res = f(bit | (1 << i));
        res.first += add;
        res.second += a[i].T;

        if (ret.first < res.first || (ret.first == res.first && ret.second > res.second)) {
            ret = res;
        }
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.T >> i.D >> i.P;
    }

    for (int i = 0; i < (1 << 20); i++) {
        dp[i] = { -1, -1 };
    }

    auto ans = f(0);
    cout << ans.first << ' ' << ans.second;
}