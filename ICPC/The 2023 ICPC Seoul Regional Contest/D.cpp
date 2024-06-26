#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

pll cal(vector<pll> arr) {
    pll res1 = arr[0];
    pll res2 = {
        arr[1].fr * arr[2].sc,
        arr[1].sc * arr[2].fr
    };

    pll ret = {
        res1.fr * res2.sc + res1.sc * res2.fr,
        res1.sc * res2.sc
    };

    ll g = gcd(ret.fr, ret.sc);
    ret.fr /= g, ret.sc /= g;

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;

    vector<vector<pll>> stk(1);
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        if ('1' <= c && c <= '9') {
            stk.back().push_back({ c - '0', 1 });
        }
        else if (c == '(') {
            vector<pll> du;
            stk.push_back(du);
        }
        else if (c == ')') {
            if (sz(stk.back()) == 3) {
                pll val = cal(stk.back());
                stk.pop_back();
                stk.back().push_back(val);
            }
            else { cout << -1; return 0; }
        }
    }
    
    if (sz(stk) == 1 && sz(stk.back()) == 1) 
        cout << stk.back()[0].fr << ' ' << stk.back()[0].sc;
    else cout << -1;
}