// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
int x[1010], y[1010];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];

    for (int i = 1; i <= n; i++) {
        int mx = -1, idx = -1;
        for (int j = 1; j <= n; j++) {
            int res = (x[i] - x[j]) * (x[i] - x[j]) + 
            (y[i] - y[j]) * (y[i] - y[j]);
            if (mx < res) {
                idx = j;
                mx = res;
            }
        }
        cout << idx << '\n';
    }
}