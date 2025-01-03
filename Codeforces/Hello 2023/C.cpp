//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const ll INF = 1e18 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m;
ll a[202020];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
		cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];

        vector<ll> psum(m + 1);
        for (int i = 1; i <= m; i++) {
            psum[i] = a[i] + psum[i - 1];
        }

        int ans = 0;

        priority_queue<ll> pq;
        
        if (a[m] > 0) pq.push(a[m]);
        for (int i = m - 1; i >= 1; i--) {
            if (psum[i] < psum[m]) {
                ans++;
                psum[m] -= pq.top() * 2;
                pq.pop();
            }
            if (a[i] > 0) pq.push(a[i]);
        }

        while (sz(pq)) pq.pop();

        ll mn = psum[m], sum = psum[m];
        for (int i = m + 1; i <= n; i++) {
            sum += a[i];
            if (a[i] < 0) pq.push(-a[i]);
            while (sum < mn) {
                ans++;
                sum += 2 * pq.top();
                pq.pop();
            }
        }

        cout << ans << '\n';
	}

	return 0;
}