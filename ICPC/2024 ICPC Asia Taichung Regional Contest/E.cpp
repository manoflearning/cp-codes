#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int a, b;
    cin >> a >> b;

    int l = b - a;
    cout << 3 << '\n';
    cout << b - 3 * l << ' ' << b << ' ' << b;
}
