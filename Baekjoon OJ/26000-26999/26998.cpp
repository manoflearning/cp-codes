#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, w;
    cin >> n >> w;

    int ans = 0;
    vector<int> stk;
    for (int i = 0; i < n; i++) {
        int x, h;
        cin >> x >> h;

        while (!stk.empty() && stk.back() > h) {
            ans++;
            stk.pop_back();        
        }

        if (stk.empty()) {
            if (h > 0) stk.push_back(h);
        }
        else if (stk.back() < h) stk.push_back(h);
        else if (stk.back() == h) continue;
    }
    ans += stk.size();

    cout << ans;
}