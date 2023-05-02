#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    int ans = 0;
    vector<int> co(n + 1);
    co[1] = ++ans;
    for (int i = 2; i <= n; i++) {
        if (co[i]) continue;
        co[i] = ++ans;
        for (int j = i * 2; j <= n; j += i) co[j] = ans;
    }
    cout << ans << '\n';
    for (int i = 1; i <= n; i++)
        cout << co[i] << ' ';
}