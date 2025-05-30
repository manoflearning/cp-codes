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

const int MAX = 101010;

int n, b, st;
int a[MAX], psum[MAX], cnt[MAX << 1];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> b;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[i] = (x > b ? 1 : (x < b ? -1 : 0));
        psum[i] = a[i] + psum[i - 1];
        if (x == b) st = i;
    }

    for (int i = 0; i < st; i++) {
        cnt[psum[i] + MAX]++;
    }

    ll ans = 0;
    for (int i = st; i <= n; i++) {
        ans += cnt[psum[i] + MAX];
    }

    cout << ans;

	return 0;
}