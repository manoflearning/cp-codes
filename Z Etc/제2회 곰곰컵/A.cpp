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
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        string res;
        for (int j = 2; j < s.size(); j++) {
            res.push_back(s[j]);
        }

        if (stoi(res) <= 90) ans++;
    }

    cout << ans;

    return 0;
}