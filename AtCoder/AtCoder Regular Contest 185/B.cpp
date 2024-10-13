// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
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

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
        int n; cin >> n;
        vector<ll> a(n);
        for (auto& i : a) cin >> i;

        // int j = 0;
        // for (int i = 0; i + 1 < n; i++) {
        //     if (a[i] <= a[i + 1]) continue;
            
        //     ll diff = a[i] - a[i + 1];

        //     while (j < i) {
        //         if (a[j] == a[j + 1]) {
        //             j++; continue;
        //         }

        //         ll x = min(a[j + 1] - a[j], diff);
        //         a[j] += x;

        //     }
        // }

        ll add_cnt = 0, ssum = 0;
        for (int i = n - 2; i >= 0; i--) {
            ssum += a[i + 1];

            ll lb = ssum / (n - i - 1);

            if (a[i] > lb) {
                ll diff = a[i] - lb;
                add_cnt += diff;
                a[i] -= diff;
            }
            else {
                ll diff = lb - a[i];
                ll x = min(diff, add_cnt);
                add_cnt -= x;
                a[i] += x;
            }

            // cout << "add_cnt: " << add_cnt << '\n';
            // for (int i = 0; i < n; i++) {
            //     cout << a[i] << ' ';
            // }
            // cout << '\n';
        }

        cout << (add_cnt == 0 ? "Yes" : "No") << '\n';

        // vector<ll> psum(n);
        // for (int i = 0; i < n; i++) {
        //     psum[i] = a[i] + (i > 0 ? psum[i - 1] : 0);
        // }

        // bool ans = 1;
        // for (int i = 0; i + 1 < n; i++) {
        //     ll lx = (psum[i] + i) / (i + 1);
        //     ll rx = (psum[n - 1] - psum[i] + n - i - 2) / (n - i - 1);
        //     if (lx > rx) {
        //         ans = 0;
        //         break;
        //     }
        // }

        // cout << (ans ? "Yes" : "No") << '\n';
	}
}
