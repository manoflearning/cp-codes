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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
		int n; cin >> n;
        vector<int> a(n);
        for (auto& i : a) cin >> i;

        if (n & 1) {
            cout << "NO\n";
            continue;
        }

        sort(all(a));

        vector<int> ans(n);
        int l = 0, r = n / 2;
        for (int i = 0; i < n; i++) {
            if (i & 1) ans[i] = a[r++];
            else ans[i] = a[l++];
        }

        int imp = 0;
        for (int i = 0; i < n; i++) {
            if (ans[(i + n - 1) % n] == ans[i]) { imp = 1; break; }
            if (ans[(i + 1) % n] == ans[i]) { imp = 1; break; }

            int b1 = (ans[(i + n - 1) % n] < ans[i]);
            int b2 = (ans[(i + 1) % n] < ans[i]);
            if (b1 != b2) imp = 1;
        }

        if (imp) cout << "NO\n";
        else {
            cout << "YES\n";
            for (auto& i : ans)
                cout << i << ' ';
            cout << '\n';
        }
	}

	return 0;
}