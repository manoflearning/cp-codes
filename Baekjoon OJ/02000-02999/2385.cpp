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
    vector<string> a(n);
    for (auto& i : a) cin >> i;

    sort(a.begin(), a.end(), [&](const string& p1, const string& p2) {
        return p1 + p2 < p2 + p1;
    });

    string ans(1, '9' + 1);
    for (int i = 0; i < n; i++) {
        if (a[i][0] == '0') continue;
        string res = a[i];
        for (int j = 0; j < n; j++) {
            if (j != i) res += a[j];
        }
        ans = min(ans, res);
    }

    if ('9' < ans[0]) {
        cout << "INVALID";
        return 0;
    }

    cout << ans;
}