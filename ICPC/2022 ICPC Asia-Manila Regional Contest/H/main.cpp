#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;
constexpr int N = 202020;

int n;
ll x;
ll a[N], b[N];

ll sum = 0;
bool pick1[N], pick2[N];
priority_queue<pair<ll, int>> pq_mx;
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq_pick1, pq_pick0;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> x;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    {
        vector<int> ord(n);
        iota(all(ord), 1);
        sort(all(ord), [&](int i, int j) {
            return a[i] < a[j];
        });

        for (auto &i : ord) {
            if (x < sum + a[i]) break;
            sum += a[i];
            pick1[i] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (pick1[i]) {
            pq_mx.push({a[i], i});
            pq_pick1.push({b[i] - a[i], i});
        } else {
            pq_pick0.push({b[i], i});
        }
    }

    while (!pq_pick1.empty() || !pq_pick0.empty()) {
        // DEBUG
        // cout << "sum = " << sum << '\n';
        // for (int i = 1; i <= n; i++) {
        //     cout << (pick2[i] ? 2 : pick1[i] ? 1 : 0);
        // }
        // cout << '\n';

        while (!pq_mx.empty() && !pick1[pq_mx.top().sc]) pq_mx.pop();
        while (!pq_pick1.empty() && !pick1[pq_pick1.top().sc]) pq_pick1.pop();

        ll diff_pick1 = (!pq_pick1.empty() ? pq_pick1.top().fr : INF);
        ll diff_pick0 = (!pq_pick0.empty() && !pq_mx.empty() ? pq_pick0.top().fr - pq_mx.top().fr : INF);

        if (x < sum + min(diff_pick1, diff_pick0)) break;

        if (diff_pick1 <= diff_pick0) {
            int idx = pq_pick1.top().sc;
            pq_pick1.pop();

            sum += diff_pick1;
            pick1[idx] = 0, pick2[idx] = 1;
        } else {
            int idx = pq_pick0.top().sc;
            pq_pick0.pop();
            
            int idx_mx = pq_mx.top().sc;
            pq_mx.pop();

            sum += diff_pick0;
            pick1[idx_mx] = 0, pick2[idx] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << (pick2[i] ? 2 : pick1[i] ? 1 : 0);
    }
}
