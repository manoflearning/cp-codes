#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

int n;

ll get_mn_idx(const vector<int> &arr) {
    ll ret = -1;
    ll mn = INF;
    for (int i = 0; i < n; i++) {
        if (arr[i] <= mn) {
            mn = arr[i];
            ret = i;
        }
    }
    return ret;
}
ll get_mx_idx(const vector<int> &arr) {
    ll ret = -1;
    ll mx = -INF;
    for (int i = 0; i < n; i++) {
        if (mx < arr[i]) {
            mx = arr[i];
            ret = i;
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

    cin >> n;

    vector<int> s, t;
    s.resize(n);
    for (auto &i : s) cin >> i;

    t = s;
    sort(all(t));

    ll ans = INF;

    // 1. 0 operation
    if (s == t) ans = min(ans, 0ll);

    // 2. 1 operation
    // 2.1. [0, mn_idx]
    {
        auto tmp = s;
        ll mn_idx = get_mn_idx(tmp);
        sort(tmp.begin(), tmp.begin() + mn_idx + 1);
        if (tmp == t) ans = min(ans, (mn_idx + 1) * (mn_idx + 1));
    }
    // 2.2. [mx_idx, n - 1]
    {
        auto tmp = s;
        ll mx_idx = get_mx_idx(tmp);
        sort(tmp.begin() + mx_idx, tmp.begin() + n);
        if (tmp == t) ans = min(ans, (n - mx_idx) * (n - mx_idx));
    }

    // 3. 2 operations
    // 3.1. [0, mn_idx] -> [mx_idx, n - 1]
    {
        auto tmp = s;
        ll mn_idx = get_mn_idx(tmp);
        sort(tmp.begin(), tmp.begin() + mn_idx + 1);
        ll mx_idx = get_mx_idx(tmp);
        sort(tmp.begin() + mx_idx, tmp.begin() + n);
        if (tmp == t) ans = min(ans, (mn_idx + 1) * (mn_idx + 1) + (n - mx_idx) * (n - mx_idx));
    }
    // 3.2. [mx_idx, n - 1] -> [0, mn_idx]
    {
        auto tmp = s;
        ll mx_idx = get_mx_idx(tmp);
        sort(tmp.begin() + mx_idx, tmp.begin() + n);
        ll mn_idx = get_mn_idx(tmp);
        sort(tmp.begin(), tmp.begin() + mn_idx + 1);
        if (tmp == t) ans = min(ans, (mn_idx + 1) * (mn_idx + 1) + (n - mx_idx) * (n - mx_idx));
    }

    assert(ans == INF);

    cout << ans;
}
