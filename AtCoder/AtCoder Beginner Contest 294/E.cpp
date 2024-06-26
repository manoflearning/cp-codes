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

ll len, n1, n2;
vector<pll> a1, a2;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> len >> n1 >> n2;
    a1.resize(n1);
    a2.resize(n2);
    for (auto& i : a1) cin >> i.fr >> i.sc;
    for (auto& i : a2) cin >> i.fr >> i.sc;

    ll len1 = 0, len2 = 0;
    int idx1 = 0, idx2 = 0;
    ll ans = 0;
    while (idx1 < sz(a1) || idx2 < sz(a2)) {
        if (len1 < len2) {
            if (a1[idx1].fr == a2[idx2 - 1].fr) 
                ans += min(a1[idx1].sc, len2 - len1);
            len1 += a1[idx1].sc;
            idx1++;
        }
        else if (len1 > len2) {
            if (a1[idx1 - 1].fr == a2[idx2].fr) {
                ans += min(a2[idx2].sc, len1 - len2);
            }
            len2 += a2[idx2].sc;
            idx2++;
        }
        else if (len1 == len2) {
            if (a1[idx1].fr == a2[idx2].fr) {
                ans += min(a1[idx1].sc, a2[idx2].sc);
            }
            len1 += a1[idx1].sc;
            len2 += a2[idx2].sc;
            idx1++, idx2++;
        }
    }

    cout << ans;

	return 0;
}