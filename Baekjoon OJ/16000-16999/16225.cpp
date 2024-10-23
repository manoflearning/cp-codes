#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 202020;

int n;
ll a[MAXN], b[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    vector<int> ord(n);
    iota(all(ord), 1);
    sort(all(ord), [&](int p1, int p2) {
        return b[p1] < b[p2];
    });

    ll ans = a[ord[0]];
    priority_queue<ll> pq;
    for (int i = 1; i + 1 < sz(ord); i += 2) {
        pq.push(a[ord[i]]);
        pq.push(a[ord[i + 1]]);
        ans += pq.top(); pq.pop();
    }

    cout << ans;
}
