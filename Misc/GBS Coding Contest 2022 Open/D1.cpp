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

	string s; cin >> s;

    ll ans = 0;
    for (int i = 0; i < sz(s); i++) {
        if (s[i] != 'A') continue;
        
        int imp = 0;
        ll cntA = 1, cntZ = 0;
        char lst = s[i];
        for (int j = i + 1; j < sz(s); j++) {
            if (!(s[j] == lst || s[j] == lst + 1)) break;

            i = j;

            lst = s[j];
            if (lst == 'A') cntA++;
            if (lst == 'Z') cntZ++;
        }
        
        ans += cntA * cntZ;
    }

    cout << ans;

    /*ll ans = 0;
    deque<int> idx[26];
    for (int x = 0; x < sz(s); x++) {
        idx[s[x] - 'A'].push_back(x);
        
        int bit = 0;
        for (int i = 0; i < 26; i++)
            if (idx[i].empty()) bit = 1;
        if (bit) continue;

        int lb = idx[0].front();
        for (int i = 0; i + 1 < 26; i++) {
            while (sz(idx[i + 1]) && idx[i].back() > idx[i + 1].front()) idx[i + 1].pop_front();
            if (idx[i + 1].empty()) {
                bit = 1;
                break;
            }
        }
        if (bit) continue;

        ans += sz(idx[0]) * sz(idx[25]);
    }

    cout << ans;*/

	return 0;
}