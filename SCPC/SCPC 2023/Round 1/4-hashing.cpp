#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
// 아래 코드 중 해싱(라빈-카프 알고리즘)과 관련된 부분들은 장난감(SCPC 2023 Round1 3번 문제)의 제 코드를 참고했습니다.
// 저의 장난감 문제의 1~6번째 제출 코드와 유사합니다.
// 해싱(라빈-카프 알고리즘)과 관련된 부분들의 예시:
// void preprocessing() {
//     dexp1[0] = dexp2[0] = dexp3[0] = 1;
//     for (int i = 1; i < MAXN; i++) {
//         dexp1[i] = d * dexp1[i - 1] % MOD1;
//         dexp2[i] = d * dexp2[i - 1] % MOD2;
//         dexp3[i] = d * dexp3[i - 1] % MOD3;
//     }
// }

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

const ll MOD1 = 39490691390373532ll;
const ll MOD2 = 41852965814676956ll; // 4185296581467695669ll;
const int MAXN = 252525;
const int d = 26;

vector<ll> dexp1(MAXN), dexp2(MAXN);
void preprocessing() {
    dexp1[0] = dexp2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        dexp1[i] = d * dexp1[i - 1] % MOD1;
        dexp2[i] = d * dexp2[i - 1] % MOD2;
    }
}

// 제 레퍼런스 코드를 복사/붙여넣기 후 변형했습니다.
// 출처 : https://github.com/manoflearning/CP-Reference-Codes/blob/master/Reference%20Codes/1.%20Data%20Structure/Segment%20Tree/Iterative%20Segment%20Tree.cpp
struct Seg {  // 0-indexed
	int n;  // array size
	int t[505050];
	void build(int N) {
		n = N;
		for (int i = 0; i < n; i++) t[n + i] = INF;
		for (int i = n - 1; i >= 1; i--) t[i] = INF;
	}
	void modify(int p, int value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	int query(int l, int r) {  // sum on interval [l, r)
		int ret = INF;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, t[l++]);
			if (r & 1) ret = min(ret, t[--r]);
		}
		return ret;
	}
}seg;

int n, m;
vector<int> a(MAXN), b(MAXN), dp(MAXN);

vector<ll> pa1(MAXN), pa2(MAXN);
vector<ll> pb1(MAXN), pb2(MAXN);

void init() {}

void input() {
    string r, p;
    cin >> r >> p;

    n = sz(r), m = sz(p);
    
    for (int i = 0; i < n; i++) a[i] = r[i] - 'a';
    for (int i = 0; i < m; i++) b[i] = p[i] - 'a';
}

void buildPsum() {
    ll x1 = 0, x2 = 0;
    for (int i = 0; i < n; i++) {
        x1 = (x1 + a[i] * dexp1[i]) % MOD1;
        pa1[i] = x1;
        x2 = (x2 + a[i] * dexp2[i]) % MOD2;
        pa2[i] = x2;
    }

    x1 = 0, x2 = 0;
    for (int i = 0; i < m; i++) {
        x1 = (x1 + b[i] * dexp1[i]) % MOD1;
        pb1[i] = x1;
        x2 = (x2 + b[i] * dexp2[i]) % MOD2;
        pb2[i] = x2;
    }
}

int f() {
    for (int i = 0; i <= n; i++) dp[i] = INF;

    seg.build(n + 1);

    dp[n] = 0;
    seg.modify(n, dp[n]);

    for (int i = n - 1; i >= 0; i--) {
        int l = i - 1, r = min(n - 1, i + m - 1);
        while (l < r) {
            int mid = (l + r + 1) >> 1;

            int isSame = 1;
            ll hash1 = (i == 0 ? pa1[mid] : (pa1[mid] - pa1[i - 1] + MOD1) % MOD1);
            ll hash2 = (i == 0 ? pa2[mid] : (pa2[mid] - pa2[i - 1] + MOD2) % MOD2);

            if (hash1 != (__int128_t)pb1[mid - i] * dexp1[i] % MOD1) isSame = 0;
            if (hash2 != (__int128_t)pb2[mid - i] * dexp2[i] % MOD2) isSame = 0;

            if (isSame) l = mid;
            else r = mid - 1;
        }
        dp[i] = min(dp[i], 1 + seg.query(i + 1, l + 2));
        if (dp[i] != INF) seg.modify(i, dp[i]);
    }

    return dp[0] == INF ? -1 : dp[0];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    preprocessing();

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        buildPsum();

        cout << f() << '\n';
        
        cout << flush;
    }
}