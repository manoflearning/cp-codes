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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int dep[303030];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n; cin >> n;
    set<int> s;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int v; cin >> v;
        auto it = s.upper_bound(v);

        int l = -1, r = -1;
        if (it != s.end()) r = *it;
        if (it != s.begin()) l = *(--it);

        if (l == -1 && r == -1) dep[v] = 0;
        else if (l == -1) dep[v] = dep[r] + 1;
        else if (r == -1) dep[v] = dep[l] + 1;
        else {
            if (dep[l] < dep[r]) swap(l, r);
            dep[v] = dep[l] + 1;
        }

        ans += dep[v];
        s.insert(v);

        cout << ans << '\n';
    }

	return 0;
}