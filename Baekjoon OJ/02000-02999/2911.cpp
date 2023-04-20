#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(n);
    for (auto& i : a)
        cin >> i.first >> i.second;

    sort(a.begin(), a.end());

    int prv = 0;
    long long ans = 0;
    for (auto& i : a) {
        int x = i.second;
        if (prv > x) ans += prv - x;
        prv = x;
    }
    ans += prv;

    cout << ans;
}