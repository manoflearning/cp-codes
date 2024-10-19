#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

int n, k;
ll a[202020], b[202020];

void init() {

}

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        vector<int> ord(n);
        iota(all(ord), 1);
        sort(all(ord), [&](int p1, int p2) {
            return a[p1] < a[p2];
        });

        ll ans = INF;

        ll sum = 0;
        priority_queue<ll> pq;
        for (auto& i : ord) {
            sum += b[i];
            pq.push(b[i]);

            if (sz(pq) > k) {
                sum -= pq.top();
                pq.pop();
            }

            if (sz(pq) == k)
                ans = min(ans, sum * a[i]);
        }

        cout << ans << '\n';
    }
}
