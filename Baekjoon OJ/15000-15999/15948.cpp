#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n, m, a[55];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; i++) cin >> a[i];
    
    vector<ll> ans;
    for (int i = 0; i < m; i++) {
        if (n & 1) {
            ans.push_back(n);
            n = (n + 1) / 2;
        }
        else {
            ans.push_back(n + (1ll << (m - i)) - 2);
            n = n / 2;
        }
    }

    for (int i = 0; i < m; i++)
        cout << ans[i] * a[i] << ' ';
}