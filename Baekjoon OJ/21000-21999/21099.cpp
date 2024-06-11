#include <bits/stdc++.h>
using namespace std;

int n, a[101010];
unordered_set<int> dp[5];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // sort(a + 1, a + 1 + n);

    dp[0].insert(0);
    for (int i = 1; i <= n; i++) {
        if (dp[3].count(a[i])) {
            cout << "Yes";
            return 0;
        }
        
        for (int j = 2; j >= 0; j--) {
            for (auto& k : dp[j]) {
                dp[j + 1].insert(k ^ a[i]);
            }
        }
    }

    if (dp[4].count(0)) cout << "Yes";
    else cout << "No";
}