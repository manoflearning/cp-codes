#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 33;

int n;
vector<ll> a(MAXN);
ll d;
vector<ll> s, e;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> d;

    if (n == 1) {
        if (a[1] <= d) cout << 3;
        else cout << 1;
        return 0;
    }

    int mid = n / 2;

    s.push_back(0);
    for (int i = 1; i <= mid; i++) {
        vector<ll> tmp1 = s, tmp2 = s, tmp3 = s;
        for (auto& j : tmp1) j -= a[i];
        for (auto& j : tmp3) j += a[i];
        vector<ll> tmp4;
        tmp4.resize(2 * sz(tmp1));
        merge(tmp1.begin(), tmp1.end(), tmp2.begin(), tmp2.end(), tmp4.begin());
        
        s.resize(3 * sz(tmp1));
        merge(tmp3.begin(), tmp3.end(), tmp4.begin(), tmp4.end(), s.begin());
    }
    reverse(s.begin(), s.end());

    e.push_back(0);
    for (int i = mid + 1; i <= n; i++) {
        vector<ll> tmp1 = e, tmp2 = e, tmp3 = e;
        for (auto& j : tmp1) j -= a[i];
        for (auto& j : tmp3) j += a[i];

        vector<ll> tmp4;
        tmp4.resize(2 * sz(tmp1));
        merge(tmp1.begin(), tmp1.end(), tmp2.begin(), tmp2.end(), tmp4.begin());
        
        e.resize(3 * sz(tmp1));
        merge(tmp3.begin(), tmp3.end(), tmp4.begin(), tmp4.end(), e.begin());
    }

    ll ans = 0;
    int pl = 0, pr = 0;
    for (auto x : s) {
        // -d <= x + y <= d
        ll lb = -d - x, ub = d - x; // [lb, ub]
        while (pl < sz(e) && e[pl] < lb) pl++;
        while (pr < sz(e) && e[pr] <= ub) pr++;
        ans += pr - pl;
    }

    cout << ans;
}
