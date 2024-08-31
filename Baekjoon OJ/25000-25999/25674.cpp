#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define ll long long

const ll LEN = 37037037;

ll to_range(char c, ll prv) {
    ll ret = 0;
    if (ret == prv) ret += LEN;
    for (char i = 'a'; i < c; i++) {
        ret += LEN;
        if (ret == prv) ret += LEN;
    }
    return ret;
}

ll get_range(ll x) {
    ll ret = 0;
    while (ret + LEN <= x) ret += LEN;
    return ret;
}

char from_range(ll x, ll prv) {
    char ret = 'a';
    while (x >= 0) {
        if (x == prv) x -= LEN;
        x -= LEN;
        if (x == prv) x -= LEN;
        if (x < 0) break;
        ret++;
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
    
    string op; cin >> op;

    if (op == "Alisa") {
        string s; cin >> s;

        int n; cin >> n;
        vector<ll> a(n);
        for (auto& i : a) cin >> i;

        vector<ll> ans;

        ll prv = 0;

        for (int idx = 0; idx < 15; idx++) {
            if (sz(s) <= idx) continue;
            int l = idx * 666, r = (idx + 1) * 666; // [l, r)

            ll lb = to_range(s[idx], prv);
            int cnt = 0;
            for (int i = l; i < r; i++) {
                if (lb <= a[i] && a[i] < lb + LEN) {
                    ans.push_back(a[i]);
                    cnt++;
                }
            }
            prv = lb;
        }

        cout << sz(ans) << '\n';
        for (auto& i : ans)
            cout << i << ' ';
    }
    else {
        int n; cin >> n;
        vector<ll> a(n);
        for (auto& i : a) cin >> i;

        string ans;

        ll prv = 0;
        for (auto& i : a) {
            if (prv <= i && i < prv + LEN) continue;

            ll lb = get_range(i);
            ans.push_back(from_range(lb, prv));
            prv = lb;
        }

        cout << ans;
    }
}

// 703703703
// 555555555
// 0
// 666666666
// 370370370