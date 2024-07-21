#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    vector<ll> a(n);
    for (auto& i : a) cin >> i;

    // sort(all(a));

    priority_queue<ll, vector<ll>, greater<ll>> pq;

    for (auto& i : a) pq.push(i);

    ll ans = 0;

    ll now = pq.top();
    pq.pop();
    while (!pq.empty()) {
        vector<ll> nxt;

        nxt.push_back(pq.top());
        pq.pop();

        while (!pq.empty() && pq.top() / now == nxt[0] / now) {
            nxt.push_back(pq.top());
            pq.pop();
        }

        ans += nxt.back() / now;
        now = nxt.back();

        if (sz(nxt) > 1 && !pq.empty()) {
            if (pq.top() / nxt[0] > pq.top() / nxt.back() + 1) ans++;
        }
    }

    cout << ans;
}