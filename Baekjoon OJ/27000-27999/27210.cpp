#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    int psum = 0, mn = 0, mx = 0;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        psum = (x == 1 ? 1 : -1) + psum;
        mn = min(mn, psum);
        mx = max(mx, psum);
    }
    cout << mx - mn;
}