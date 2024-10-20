#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second

const ll INF = 1e18;

int n, a[101010];
ll psum[101010], dp[101010];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        psum[i] = a[i] + psum[i - 1];
    }

    ll ans = INF;
    
    priority_queue<pair<ll, int>> q;
    q.push({ 0, 0 });
    
    int idx = 0;
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && -q.top().fr <= psum[i]) {
            idx = max(idx, q.top().sc);
            q.pop();
        }

        dp[i] = psum[i] - psum[idx];
        q.push({ -(dp[i] + psum[i]), i });
        ans = min(ans, max(dp[i], psum[n] - psum[i]));
    }

    cout << ans;

    return 0;
}