#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18 + 1e13;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    ll x;
    cin >> n >> x;

    vector<ll> a(n), b(n);
    for (auto &i : a) cin >> i;
    for (auto &i : b) cin >> i;

    ll l = 0, r = INF;
    while (l < r) {
        ll mid = (l + r + 1) >> 1;

        ll rem = x;
        for (int i = 0; i < n; i++) {
            ll cnt = max(0ll, (mid - a[i] + b[i] - 1) / b[i]);
            rem -= cnt;
            if (rem < 0) break;
        }

        if (rem >= 0) l = mid;
        else r = mid - 1;
    }

    struct node {
        ll w; int idx;
        bool operator<(const node &rhs) const {
            if (w ^ rhs.w) return w > rhs.w;
            return idx > rhs.idx;
        }
    };
    priority_queue<node> pq;

    for (int i = 0; i < n; i++) {
        ll cnt = max(0ll, (l - a[i] + b[i] - 1) / b[i]);
        a[i] += cnt * b[i];
        x -= cnt;
        pq.push({a[i], i});
    }

    while (x--) {
        auto [w, idx] = pq.top();
        pq.pop();

        a[idx] += b[idx];
        pq.push({a[idx], idx});
    }

    for (auto &i : a)
        cout << i << ' ';
}