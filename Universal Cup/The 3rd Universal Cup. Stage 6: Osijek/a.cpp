#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXVAL = 1e9;
const int INF = 1e9 + 7;
const ll S = 5050;

vector<int> dp(S, INF);
vector<int> opt(S, -1);

vector<ll> ans;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

// void f(ll s, ll x, int co) {
//     if (gcd(s, x) == 1) {
//         ans.push_back(co * s);
//         return;
//     }

//     for (int d = 1; d < s; d++) {
//         if (gcd(s - d, x) == 1) {
//             ans.push_back(co * (s - d));
//             f(d, x, co);
//             return;
//         }
//         if (s + d <= MAXVAL && gcd(s + d, x) == 1) {
//             ans.push_back(co * (s + d));
//             f(d, x, -1 * co);
//             return;
//         }
//     }
// }

void print(const vector<ll>& ans) {
    cout << sz(ans) << '\n';
    for (auto& i : ans)
        cout << i << ' ';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll s, x;
    cin >> s >> x;

    // f(s, x, 1);

    // cout << sz(ans) << '\n';
    // for (auto& i : ans)
    //     cout << i << ' ';

    if (gcd(s, x) == 1) {
        cout << 1 << '\n' << s;
        exit(0);
    }

    for (ll d = 1; d < 5e6; d++) {
        ll p = d, q = d + s;
        if (gcd(p, x) == 1 && gcd(q, x) == 1) {
            cout << 2 << '\n';
            if (MAXVAL < q) cout << -p+x << ' ' << q-x;
            else cout << -p << ' ' << q;
            exit(0);
        }
    }

    for (ll d = 1; d < 5e6; d++) {
        ll p = d, q = d + s;
        if (p % 2 == 0 && gcd(p/2, x) == 1 && gcd(q, x) == 1) {
            cout << 3 << '\n';
            if (MAXVAL < q) cout << -p/2 << ' ' << -p/2+x << ' ' << q-x;
            else cout << -p/2 << ' ' << -p/2 << ' ' << q;
            exit(0);
        }
        if (q % 2 == 0 && gcd(p, x) == 1 && gcd(q/2, x) == 1) {
            cout << 3 << '\n';
            cout << -p << ' ' << q/2 << ' ' << q/2;
            exit(0);
        }
    }
}
