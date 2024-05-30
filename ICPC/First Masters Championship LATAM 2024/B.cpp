#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

ll l, r;
ll p10[19];

ll f(ll x) {
    if (x == 0) return x;

    string s = to_string(x);
    if (x == p10[sz(s) - 1] && x != 1) {
        x--;
        s = to_string(x);
    }

    int cnt9 = sz(s) / 2;

    ll ret = 0;
    ret += p10[cnt9] - 1;
    ret += x / p10[sz(s) / 2];

    string t = s;
    for (int i = 0; i < sz(t) / 2; i++) {
        t[sz(t) - i - 1] = t[i];
    }
    if (stoll(s) < stoll(t)) ret--;
    
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    p10[0] = 1;
    for (int i = 1; i <= 18; i++)
        p10[i] = 10 * p10[i - 1];

    int q; cin >> q;
    while (q--) {
        cin >> l >> r;
        cout << f(r) - f(l - 1) << '\n';
    }
}