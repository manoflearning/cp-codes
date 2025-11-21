#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    vector<int> a(3);
    cin >> a[0] >> a[1] >> a[2];

    sort(a.begin(), a.end());

    if (a[2] - a[0] < 10) cout << "final " << a[1];
    else cout << "check again";
}