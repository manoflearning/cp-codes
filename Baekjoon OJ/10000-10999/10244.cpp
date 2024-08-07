#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int n;
vector<int> a;
int dp[101010][101];
set<int> ans;

void init() {
    for (int i = 0; i < 101010; i++)
        memset(dp[i], 0, sizeof(dp[i]));
    ans.clear();
}

void input() {
    cin >> n;
    if (!n) exit(0);
    a.resize(n);
    for (auto& i : a) cin >> i;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {
        init();

        input();

        dp[0][a[0]] = 1;
        ans.insert(a[0]);
        for (int i = 1; i < n; i++) {
            dp[i][a[i]] = 1;
            ans.insert(a[i]);
            for (int j = 1; j <= 100; j++) {
                if (dp[i - 1][j]) {
                    int g = gcd(j, a[i]);
                    dp[i][g] = 1;
                    ans.insert(g);
                }
            }
        }

        cout << ans.size() << '\n';
    }
}