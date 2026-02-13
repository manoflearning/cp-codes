#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto &i : a) cin >> i;

        priority_queue<pii, vector<pii>, greater<pii>> pq;
        for (int i = 0; i < n; i++) pq.push({a[i], i});

        vector<bool> vis(n);

        int ans = 0;
        int fr{0}, sc{1};
        while (1) {
            while (fr < n && vis[fr]) fr++;
            while (sc < n && (vis[sc] || sc == fr)) sc++;

            if (fr == n && sc == n) break;

            if (fr < n && sc < n && a[fr] == a[sc]) {
                ans++;
                vis[fr] = vis[sc] = 1;
            } else {
                while (!pq.empty()) {
                    auto [_, idx] = pq.top();
                    pq.pop();

                    if (vis[idx]) continue;

                    ans++;
                    vis[idx] = 1;
                    break;
                }
            }
        }

        cout << ans << '\n';
    }
}