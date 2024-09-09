#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101010;

vector<int> dp[MAXN];

vector<int> f(int n) {
    auto& ret = dp[n];
    if (n == 1) return ret = { 1 };
    if (n == 2) return ret = { 1, 2 };
    
    if (n & 1) {
        vector<int> arr = f((n + 1) / 2);
        for (auto& i : arr) ret.push_back(i * 2 - 1);
        for (auto& i : arr) {
            if (i * 2 <= n)
                ret.push_back(i * 2);
        }
    } else {
        vector<int> arr = f(n / 2);
        for (auto& i : arr) ret.push_back(i * 2 - 1);
        for (auto& i : arr) ret.push_back(i * 2);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;

    vector<int> ans = f(n);
    for (auto& i : ans)
        cout << i << ' ';
}