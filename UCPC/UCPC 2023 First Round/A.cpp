#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int ans = 0;
    for (int i = 0; i < 10; i++) {
        int x; cin >> x;
        ans = (ans + x) % 4;
    }

    if (ans == 0) cout << "N";
    if (ans == 1) cout << "E";
    if (ans == 2) cout << "S";
    if (ans == 3) cout << "W";
}