#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<map<int, int>> mp(m);
    for (int i = 0; i < n; i++) {
        int acc = 0;
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            mp[j][acc] += 1;
            mp[j][acc + x] -= 1;
            acc += x;
        }
    }

    for (int j = 0; j < m; j++) {
        int ans = 0, psum = 0;
        for (auto [_, v] : mp[j]) {
            psum += v;
            ans = max(ans, psum);
        }
        cout << ans << ' ';
    }
}
