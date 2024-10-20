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

int n, k, l;
vector<ll> a, b;
ll psum[202020];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> k >> l;
    a.resize(n);
    for (auto& i : a) cin >> i;
    b.resize(k);
    for (auto& i : b) cin >> i;

    for (auto& i : b) {
        psum[i]++; 
        if (i + l < 202020) psum[i + l]--;
    }

    for (int i = 1; i < 202020; i++)
        psum[i] += psum[i - 1];

    vector<int> arr;
    for (int i = 1; i <= n; i++)
        arr.push_back(psum[i]);
    sort(arr.rbegin(), arr.rend());
    sort(a.rbegin(), a.rend());
    
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i] / (1ll << min(62, arr[i]));
    }

    cout << ans;

	return 0;
}