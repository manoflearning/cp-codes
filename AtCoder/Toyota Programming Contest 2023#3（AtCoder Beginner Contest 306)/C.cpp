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

int n, a[303030];
int cnt[101010], f[101010];
vector<int> ans;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    for (int i = 1; i <= 3 * n; i++) cin >> a[i];

    for (int i = 1; i <= 3 * n; i++) {
        cnt[a[i]]++;
        if (cnt[a[i]] == 2) f[a[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        ans.push_back(i);
    }

    sort(ans.begin(), ans.end(), [&](const int p1, const int p2) {
        return f[p1] < f[p2];
    });

    for (auto& i : ans)
        cout << i << ' ';

	return 0;
}