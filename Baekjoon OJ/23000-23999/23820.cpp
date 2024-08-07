#include <bits/stdc++.h>
using namespace std;

int n, cnt[2020202], ans[2020202];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x; cnt[x] = 1;
    }

    if (!cnt[0]) { cout << 0; return 0; }

    vector<int> a;
    for (int i = 0; i < 2020202; i++)
        if (cnt[i]) a.push_back(i);

    for (auto& i : a) {
        for (auto& j : a) {
            if (2020202 <= i * j) break;
            ans[i * j] = 1;
        }
    }

    for (int i = 0; i < 2020202; i++)
        if (!ans[i]) { cout << i; return 0; }
}