#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        vector<int> lm(k + 1, INF), rm(k + 1, -INF);
        for (int i = 0; i < n; i++) {
            lm[a[i]] = min(lm[a[i]], i);
            rm[a[i]] = max(rm[a[i]], i);
        }

        int lb = 0;
        for (int i = 1; i <= k; i++) {
            lb = max(lb, rm[i] - lm[i]);
        }

        vector<int> ord(k);
        iota(all(ord), 1);
        sort(all(ord), [&](int i, int j) {
            return rm[i] < rm[j];
        });

        int lo = lb, hi = n;
        while (lo < hi) {
            const int mid = (lo + hi) >> 1;

            bool yes = 1;

            priority_queue<pii, vector<pii>, greater<>> pq;
            int j = 0;
            for (int i = 0; i < n; i++) {
                while (j < k && rm[ord[j]] - mid <= i) {
                    pq.push({lm[ord[j]] + mid, ord[j]});
                    j++;
                }

                while (!pq.empty() && pq.top().first < i) pq.pop();

                if (a[i] == 0) {
                    if (pq.empty()) { yes = 0; break; }
                    else {
                        auto now = pq.top();
                        pq.pop();
                        pq.push({min(now.first, i + mid), now.second});
                    }
                }
            }

            if (yes) hi = mid;
            else lo = mid + 1;
        }

        vector<int> ans = a;
        priority_queue<pii, vector<pii>, greater<>> pq;
        int j = 0;
        for (int i = 0; i < n; i++) {
            while (j < k && rm[ord[j]] - lo <= i) {
                pq.push({lm[ord[j]] + lo, ord[j]});
                j++;
            }

            while (!pq.empty() && pq.top().first < i) pq.pop();

            if (ans[i] == 0) {
                assert(!pq.empty());

                auto now = pq.top();
                pq.pop();

                ans[i] = now.second;
                pq.push({min(now.first, i + lo), now.second});
            }
        }

        for (auto &i : ans) cout << i << ' ';
        cout << '\n';
    }
}
