#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto &i : a) cin >> i;
        
        map<int, int> mp;
        for (auto &i : a) mp[i]++;

        int ans = 0;

        int state = 0;
        // 0: x+1 not determined
        // 1: x+1 determined
        for (auto &[x, y]: mp) {
            if (state == 0) {
                if (y >= 4) ans = 1;

                if (y >= 2 && mp.count(x + 1)) state = 1;
                else state = 0;
            } else if (state == 1) {
                if (y >= 2) ans = 1;
                
                if (y >= 1 && mp.count(x + 1)) state = 1;
                else state = 0;
            }
        }

        cout << (ans ? "Yes" : "No") << '\n';
    }
}
