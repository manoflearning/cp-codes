// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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

const int MAXS = 1010101;

int n, m;
string s;
void input() {
    cin >> n >> m;
    cin >> s;
}
vector<int> p; // p[i]: the radius of the palindrome at the current position i
void manacher() {
    // Preprocessing for determining even-length pelindromes
    n = sz(s);
    s.resize(n << 1 | 1);
    p.resize(n << 1 | 1);
    for (int i = n - 1; i >= 0; i--) {
        s[i << 1 | 1] = s[i];
        s[i << 1] = '#';
    }
    n <<= 1;
    s[n++] = '#';
    // Processing
    int r = -1, c = -1;
    // r: end of palindrome
    // c: center of palindrome
    for (int i = 0; i < n; i++) {
        if (i <= r) p[i] = min(r - i, p[c * 2 - i]);
        else p[i] = 0;
        while (1) {
            if (i - p[i] - 1 < 0 || i + p[i] + 1 >= n) break;
            if (s[i + p[i] + 1] != s[i - p[i] - 1]) break;
            p[i]++;
        }
        if (i + p[i] > r) {
            r = i + p[i], c = i;
        }
    }
}

const int MAXN = 1010101;  // limit for array size
struct Seg {  // 0-indexed
	int n;  // array size
	ll t[2 * MAXN];
	void build(int N) {
		n = N;
		// for (int i = 0; i < n; i++) cin >> t[n + i];
		// for (int i = n - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r) {  // sum on interval [l, r)
		ll ret = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret += t[l++];
			if (r & 1) ret += t[--r];
		}
		return ret;
	}
}seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    
    manacher();

    int ans = 0;

    seg.build(MAXN);
    vector<int> arr;
    for (int i = 1; i < n; i++) {
        int l = i / 2 - p[i] / 2;
        int r = i / 2 + p[i] / 2;

        if ((r - l + 1) % 2 != p[i] % 2) r--;

        if ((r - l + 1) - 2 >= m) {
            int diff = p[i] / 2 - m / 2;
            l += diff;
            r -= diff;
            if ((r - l + 1) < m) l--, r++;
        }

        // cout << p[i] << ' ' << i / 2 << ' ' << l << ' ' << r << '\n';

        if ((r - l + 1) >= m && !seg.query(l, r + 1)) {
            seg.modify(r, 1);
            ans++;
        }
    }

    cout << ans;
}