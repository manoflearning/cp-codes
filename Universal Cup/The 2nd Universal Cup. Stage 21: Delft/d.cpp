#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int x; cin >> x;

    cout << 1 << '\n';

    if (x == 25) {
        cout << 50 << '\n';
        for (int i = 0; i < 50; i++)
            cout << 5 << ' ';
        return 0;
    }

    cout << 1 + 2 * x << '\n';
    cout << x << ' ';
    for (int i = 0; i < 2 * x; i++)
        cout << 1 << ' ';
}
