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

int n, k;
ll a[505050], b[505050], psum[505050], psum2[505050];
ll mxl[505050], mxr[505050], idxl[505050], idxr[505050];

ll sum(int l, int r) {
    if (l <= r) return psum[r] - psum[l - 1];
    else return psum[n] - (psum[l - 1] - psum[r]);
}
ll sum2(int l, int r) {
    if (l <= r) return psum2[r] - psum2[l - 1];
    else return psum2[n] - (psum2[l - 1] - psum2[r]);
}

bool crossed(int s, int e, int s2, int e2) {
    if (e2 == e || s2 == s) return 0;

    if (e2 < e) e2 += n;
    if (s2 < e) s2 += n;
    //cout << s << ' ' << e << ' ' << s2 << ' ' << e2 << '\n';
    //cout << !(e <= e2 && e2 < s2) << '\n';
    return !(e2 < s2);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        psum[i] = a[i] + psum[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        psum2[i] = b[i] + psum2[i - 1];
    }

    for (int i = 1; i <= n; i++) {
        if (!b[i]) continue;

        ll res = 0;
        idxr[i] = i;
        for (int j = (i == n ? 1 : i + 1); !b[j]; j = (j == n ? 1 : j + 1)) {
            res += a[j];
            if (mxr[i] < res) {
                mxr[i] = res;
                idxr[i] = j;
            }
        }
        res = 0;
        idxl[i] = i;
        for (int j = (i == 1 ? n : i - 1); !b[j]; j = (j == 1 ? n : j - 1)) {
            res += a[j];
            if (mxl[i] < res) {
                mxl[i] = res;
                idxl[i] = j;
            }
        }
    }

    ll ans = -1e18;
    int e = 1, cnt = 0; // [s, e)
    for (int s = 1; s <= n; s++) {
        if (!b[s]) continue;

        while (cnt < k) {
            if (b[e]) cnt++;
            e = (e == n ? 1 : e + 1);
        }

        int ee = (e == 1 ? n : e - 1);
        assert(sum2(s, ee) == k);
        
        ll res = sum(s, ee) + mxl[s] + mxr[ee];

        int e2 = idxr[ee], s2 = idxl[s];
        if (crossed(s, ee, s2, e2)) {
            res -= sum(s2, e2);
        }
        //cout << s << ' ' << ee << ' ' << s2 << ' ' << e2 << '\n';
        ans = max(ans, res);
        cnt--;
    }

    cout << ans;

	return 0;
}