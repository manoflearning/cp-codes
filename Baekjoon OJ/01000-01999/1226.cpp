#include <bits/stdc++.h>
using namespace std;

int n, sum, lb, b[303];
vector<pair<int, int>> a;
int dp[101010], mx;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        sum += a[i].first;
        a[i].second = i + 1;
        b[i + 1] = a[i].first;
    }
    lb = sum / 2 + 1;

    sort(a.rbegin(), a.rend());

    dp[0] = n + 1;
    for (auto& i : a) {
        for (int j = lb - 1; j >= 0; j--) {
            if (dp[j] && !dp[j + i.first]) {
                dp[j + i.first] = i.second;
                if (lb <= j + i.first) mx = max(mx, j + i.first);
            }
        }
    }

    vector<int> ans;
    while (mx > 0) {
        ans.push_back(dp[mx]);
        mx -= b[dp[mx]];
    }

    cout << ans.size() << '\n';
    for (auto& i : ans)
        cout << i << ' ';
}