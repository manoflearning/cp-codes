#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, m, k;
int a[101010], ra[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        ra[a[i]]++;
    }

    priority_queue<ll> pq;
    for (int i = 1; i <= n; i++) {
        pq.push(ra[i]);
    }

    ll ans = 0;
    while (k-- && !pq.empty()) {
        ans += pq.top();
        pq.pop();
    }

    cout << ans;
}
