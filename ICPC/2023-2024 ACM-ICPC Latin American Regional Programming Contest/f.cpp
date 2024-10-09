#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pli pair<ll, int>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

vector<ll> get(ll n, ll x) {
    vector<ll> ret;
    while (n > 0) {
        ret.push_back(n % x);
        n /= x;
    }
    return ret;
}

bool is_palin(vector<ll>& a) {
    for (int i = 0; i < sz(a); i++) {
        if (a[i] != a[sz(a) - i - 1]) return 0;
    }
    return 1;
}

void solve(ll n) {
    if (n == 2) {
        cout << "*" << '\n';
        return;
    }

    vector<ll> ans;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0 && n / i > 2) {
            auto res = get(n, n / i - 1);
            if (is_palin(res)) {
                ans.push_back(n / i - 1);
            }
            else {
                // assert(0);
                // cout << "fuck " << n / i - 1 << '\n';
            }
        }
    }

    for (int i = 2; i <= min(1'000'000ll, n - 1); i++) {
        auto res = get(n, i);
        if (is_palin(res)) {
            ans.push_back(i);
        }
    }

    sort(all(ans));
    ans.erase(unique(all(ans)), ans.end());

    for (auto& i : ans) cout << i << ' ';
    // cout << '\n';

    if (ans.empty()) {
        cout << "*" << '\n';
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll n; cin >> n;
    solve(n);
    // for (ll n = 2; n <= 100; n++) {
    //     cout << "n = " << n << '\n';
    //     solve(n);
    // }
}
