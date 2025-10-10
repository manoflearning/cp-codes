#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, d;
    cin >> x >> d;

    if (x * 2 <= d) {
        cout << "double it";
    } else {
        cout << "take it";
    }
}