#include <bits/stdc++.h>
using namespace std;

int n, sum, lb, b[303];
vector<pair<int, int>> a;
int dp[30303030], mx;

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
        b[i + 1] = a[i].first;
        a[i].second = i + 1;
    }
    lb = sum / 2 + 1;

    sort(a.rbegin(), a.rend());

    unordered_set<int> s;
    s.insert(0);
    for (auto& i : a) {
        unordered_set<int> tmp;
        for (auto& j : s) {
            if (dp[i.first + j]) continue;
            dp[i.first + j] = i.second;
            if (lb <= i.first + j) mx = max(mx, i.first + j);
            else tmp.insert(i.first + j);
        }
        for (auto& j : tmp) s.insert(j);
    }

    vector<int> ans;
    while (mx > 0) {
        ans.push_back(dp[mx]);
        mx -= b[dp[mx]];
    }

    cout << ans.size() << '\n';
    sort(ans.begin(), ans.end());
    for (auto& i : ans)
        cout << i << ' ';
}
