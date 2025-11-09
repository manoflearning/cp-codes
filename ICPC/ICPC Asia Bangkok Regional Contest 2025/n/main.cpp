#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    int n, a, b;
    cin >> n >> a >> b;

    b = n - b - 1;
    if (a > b) swap(a, b);

    cout << b - a - 1;
}