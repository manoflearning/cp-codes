#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<int> vi(1010101);
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        vi[x] = 1;
    }

    ll ans = 0;
    for (int x = 1; x <= n; x++) {
        if (vi[x]) continue;
        int leadingOne = 0;
        for (int d = 20; d >= 0; d--) {
            if ((1 << d) & x) {
                leadingOne = (1 << d);
                break;
            }
        }
        ans += x - leadingOne;
    }
    ans *= 2;

    cout << ans;
}