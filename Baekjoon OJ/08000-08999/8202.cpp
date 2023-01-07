// 그래프가 주어질 때, 노드 집합을 독립 집합 A과 완전 그래프 집합 B로 분할하는 방법의 수를 구하라.
// A에 속한 임의의 노드 u와 B에 속한 임의의 노드 v를 생각해보자.
// 1. deg[u] <= deg[v]이다.
// 2. sum(deg[v]) = sum(deg[u]) + |B| * (|B| - 1)
// (1, 2를 만족한다) iff (A는 독립 집합이고, B는 완전 그래프 집합이다)

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

ll binom(ll n, ll r) {
    r = min(r, n - r);

    ll ret = 1;
    for (ll i = 1; i <= r; i++) {
        ret *= n + 1 - i;
        ret /= i;
    }
    return ret;
}

int n, deg[5050], cnt[5050];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    for (int v = 1; v <= n; v++) {
        int cnt; cin >> cnt;
        while (cnt--) {
            int v; cin >> v;
            deg[v]++;
        }
    }

    ll sumA = 0, sumB = 0;
    for (int v = 1; v <= n; v++) {
        cnt[deg[v]]++;
        sumA += deg[v];
    }

    ll ans = 0;
    ll A = n, B = 0;
    for (int i = n - 1; i >= 0; i--) {
        int res = 0;
        for (int j = 0; j < cnt[i]; j++) {
            A--, B++;
            sumA -= i, sumB += i;
            if (sumA + B * (B - 1) == sumB && A && B) {
                ans += binom(cnt[i], j + 1);
            }
        }
    }

    cout << ans;

	return 0;
}