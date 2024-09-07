// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
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

int n;
vector<ll> a(n);

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
    
    int ans = 0;
    auto prv = a;
    while (1) {
        ans++;

        auto now = prv;
        for (int i = 0; i < n; i++) {
            int res = 0;
            for (int j = i + 1; j < n; j++) {
                if (prv[i] < prv[j]) res++;
            }
            now[i] = res;
        }

        if (now == prv) break;
        prv = now;
    }
    cout << ans;
}
