#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int N = 202020;
const int SUM_G = 202020;

int n;
ll g[N], r[N];
set<int> dp;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> g[i] >> r[i];

    ll p = r[1];
    for (int i = 2; i <= n; i++)
        p = gcd(p, r[i]);
    
    
}