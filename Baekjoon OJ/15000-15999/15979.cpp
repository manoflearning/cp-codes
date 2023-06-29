#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    if (n == 0 && m == 0) cout << 0;
    else if (gcd(abs(n), abs(m)) == 1) cout << 1;
    else cout << 2;
}