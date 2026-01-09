#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<pii> a(m);
        vector<int> ps(n + 2), ps1(n + 2), ps2(n + 2);
        int cnt0 = 0;
        for (int i = 0; i < m; i++) {
            cin >> a[i].fr >> a[i].sc;
            
            ps[a[i].fr]++, ps[a[i].sc + 1]--;
        }
        for (int i = 1; i <= n; i++) {
            ps[i] += ps[i - 1];
            // cout << ps[i] << ' ';
            cnt0 += ps[i] == 0;
            ps1[i] = (ps[i] == 1) + ps1[i - 1];
            ps2[i] = (ps[i] == 2) + ps2[i - 1];
        }
        // cout << '\n';

        sort(all(a));

        vector<vector<int>> ls(n + 1), rs(n + 1);
        for (int i = 0; i < m; i++) {
            ls[a[i].fr].push_back(i);
            rs[a[i].sc].push_back(i);
        }

        int ans = 0;

        set<int> st;
        for (int i = 1; i <= n; i++) {
            for (int x : ls[i]) st.insert(x);
            assert(sz(st) == ps[i]);

            if (ps[i] == 2) {
                auto it = st.begin();
                auto [l1, r1] = a[*(it++)];
                auto [l2, r2] = a[*it];
                if (pii{l1, r1} > pii{l2, r2}) {
                    swap(l1, l2);
                    swap(r1, r2);
                }
                int res = 0;
                res += ps1[max(r1, r2)] - ps1[l1 - 1];
                res += ps2[min(r1, r2)] - ps2[l2 - 1];
                ans = max(ans, res);
            }

            for (int x : rs[i]) st.erase(x);
        }

        multiset<int> l1s;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        int cnt1_1 = 0;
        for (const auto &[l2, r2] : a) {
            while (!pq.empty()) {
                const auto [r1, l1] = pq.top();
                if (r1 < l2) {
                    pq.pop();
                    l1s.erase(l1s.find(l1));
                    cnt1_1 = max(cnt1_1, ps1[r1] - ps1[l1 - 1]);
                } else break;
            }
            ans = max(ans, cnt1_1 + ps1[r2] - ps1[l2 - 1]);
            if (!l1s.empty()) ans = max(ans, ps1[r2] - ps1[*l1s.begin() - 1]);
            pq.push({r2, l2});
            l1s.insert(l2);
        }
        
        cout << ans + cnt0 << '\n';
    }
}