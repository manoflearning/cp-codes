#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    vector<int> a(n);
    for (auto& i : a) cin >> i;

    int ans = -1;
    for (int i = 1; i < n; i++)
        if (a[i] > a[0]) { ans = i + 1; break; }

    cout << ans;
}