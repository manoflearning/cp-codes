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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

string s;
vector<int> a(3);
int cnt[101];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> s;
    cin >> a[0] >> a[1] >> a[2];
    
    sort(all(a));

    cnt[a[0]]++;
    cnt[a[1]]++;
    cnt[a[2]]++;

    int ans = 0;
    for (int i = 0; i < sz(s); i++) {
        if (s[i] == 'N') continue;

        int x = i + 1;
        if (x <= 6) {
            ans = max(ans, x * (cnt[x] + 2));
        }
        if (x == 7) {
            for (int j = 1; j <= 6; j++) {
                if (cnt[j] >= 2) 
                    ans = max(ans, j * 4);
            }
        }
        if (x == 8) {
            for (int j = 1; j <= 6; j++) {
                for (int k = 1; k <= 6; k++) {
                    /*for (int p = 1; p <= 6; p++) {
                        if (j == k || j == p || k == p) continue;
                        int sum = cnt[j] + cnt[k] + cnt[p];
                        if (sum >= 3 && cnt[j] <= 3 && cnt[k] <= 1 && cnt[p] <= 1) {
                            ans = max(ans, j * 3 + k + p);
                        }
                    }*/
                    if (j == k) continue;
                    if (cnt[j] == 3 && cnt[k] == 0) {
                        ans = max(ans, j * 3 + k * 2);
                    }
                    if (cnt[j] == 2 && cnt[k] == 1) {
                        ans = max(ans, j * 3 + k * 2);
                    }
                    if (cnt[j] == 1 && cnt[k] == 2) {
                        ans = max(ans, j * 3 + k * 2);
                    }
                }
            }
        }
        if (x == 9 || x == 10) {
            if (a[0] != a[1] && a[1] != a[2]) {
                if (a[0] == 1 && a[2] == 6) continue;
                ans = max(ans, 30);
            }
        }
        if (x == 11) {
            for (int j = 1; j <= 6; j++) {
                if (cnt[j] == 3) 
                    ans = max(ans, 50);
            }
        }
        if (x == 12) {
            ans = max(ans, a[0] + a[1] + a[2] + 12);
        }
    }

    cout << ans;

	return 0;
}