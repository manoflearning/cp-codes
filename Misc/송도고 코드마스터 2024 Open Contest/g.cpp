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
const ll INF = 1e18;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m;
vector<ll> a;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n >> m;
    a.resize(n);
    for (auto& i : a) cin >> i;

    sort(all(a));

    ll ans = 0;

    bool m_exist = 0;
    while (!a.empty() && a.back() == m) {
        a.pop_back();
        m_exist = 1;
    }

    while (sz(a) >= 3 && 2 * a[sz(a) - 3] >= m) {
        ans++;
        // int base = a[sz(a) - 3];
        // a[sz(a) - 1] += base;
        // a[sz(a) - 2] += base;
        // a[sz(a) - 3] += base;
        a.pop_back();
        a.pop_back();
        a.pop_back();
        // if (a.back() >= m) a.pop_back();
        // if (a.back() >= m) a.pop_back();
        // if (a.back() >= m) a.pop_back();
        m_exist = 1;
    }

    if (!m_exist) {
        ans++;
        a.pop_back();
        m_exist = 1;
    }

    ans += (sz(a) + 1) / 2;

    cout << ans;
}
