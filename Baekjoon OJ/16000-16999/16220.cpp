#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    map<int, vector<int>> mp;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        mp[x].push_back(y);
    }
    
    priority_queue<int, vector<int>, greater<int>> pq;

    int ans = 0;
    for (auto& it : mp) {
        while (sz(pq) >= 2) {
            int x = pq.top(); pq.pop();
            int y = pq.top(); pq.pop();
            if (x < it.first) ans++;
            else {
                pq.push(x);
                pq.push(y);
                break;
            }
        }
        while (!pq.empty() && pq.top() < it.first) pq.pop();

        for (auto& i : it.second) pq.push(i);
    }

    while (sz(pq) >= 2) {
        pq.pop();
        pq.pop();
        ans++;
    }

    cout << ans;
}
