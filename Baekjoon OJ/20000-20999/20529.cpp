#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        map<string, int> mp;
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            mp[s]++;
        }

        vector<string> a;
        for (auto& i : mp) {
            int cnt = min(3, i.second);
            while (cnt--) {
                a.push_back(i.first);
            }
        }

        int ans = 100;
        for (int i = 0; i < a.size(); i++) {
            for (int j = i + 1; j < a.size(); j++) {
                for (int k = j + 1; k < a.size(); k++) {
                    int res = (a[i][0] != a[j][0]) + (a[i][1] != a[j][1]) + (a[i][2] != a[j][2]) + (a[i][3] != a[j][3]);
                    res += (a[i][0] != a[k][0]) + (a[i][1] != a[k][1]) + (a[i][2] != a[k][2]) + (a[i][3] != a[k][3]);
                    res += (a[j][0] != a[k][0]) + (a[j][1] != a[k][1]) + (a[j][2] != a[k][2]) + (a[j][3] != a[k][3]);
                    ans = min(ans, res);
                }
            }
        }

        cout << ans << '\n';
    }
}