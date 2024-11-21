#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll l, h;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> l >> h;

    if (l & 1) cout << h;
    else cout << h / 2 * 2;
}
