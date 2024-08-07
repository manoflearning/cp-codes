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

vector<ll> a, p;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    for (ll x = 2; x <= 10000; x++) {
        int bit = 0;
        for (ll i = 2; i <= sqrt(x); i++) {
            if (x % i == 0) { bit = 1; break; }
        }
        if (!bit) p.push_back(x);
    }

    for (int i = 0; i + 1 < sz(p); i++) {
        a.push_back(p[i] * p[i + 1]);
    }

	int n; cin >> n;
    cout << *upper_bound(all(a), n);

	return 0;
}