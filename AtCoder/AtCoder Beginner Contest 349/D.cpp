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

	ll s, e;
    cin >> s >> e;

    vector<pll> ans;
    while (s < e) {
        ll y = -1;
        for (int i = 60; i >= 0; i--) {
            ll x = (1ll << i);
            if (s % x == 0 && s + x <= e) {
                y = x;
                break;
            }
        }

        assert(y != -1);

        ans.push_back({ s, s + y });
        s += y;
    }

    cout << sz(ans) << '\n';
    for (auto& i : ans)
        cout << i.fr << ' ' << i.sc << '\n';
}