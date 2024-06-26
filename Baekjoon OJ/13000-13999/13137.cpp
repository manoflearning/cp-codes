#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;
const int MAX = 404040;

int n;
vector<int> a;
int dp[MAX], myAns[MAX];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    dp[0] = 0, dp[1] = 1;
    myAns[0] = 0, myAns[1] = 1;
    for (int i = 2; i < MAX; i++) {
        int mx = -1;
        dp[i] = INF;
        for (auto& j : a) {
            if (i < j) break;
            mx = j;
            dp[i] = min(dp[i], 1 + dp[i - j]);
        }

        myAns[i] = i / mx + myAns[i % mx];

        if (myAns[i] != dp[i]) {
            cout << "No";
            return 0;
        }
    }

    cout << "Yes";
}