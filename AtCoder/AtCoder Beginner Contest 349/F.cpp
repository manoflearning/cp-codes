#pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
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
const int MOD = 998244353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

// namespace miller_rabin{
//     ll mul(ll x, ll y, ll mod){ return (__int128_t) x * y % mod; }
// 	ll ipow(ll x, ll y, ll p){
// 		ll ret = 1, piv = x % p;
// 		while(y){
// 			if(y&1) ret = mul(ret, piv, p);
// 			piv = mul(piv, piv, p);
// 			y >>= 1;
// 		}
// 		return ret;
// 	}
// 	bool miller_rabin(ll x, ll a){
// 		if(x % a == 0) return 0;
// 		ll d = x - 1;
// 		while (1){
// 			ll tmp = ipow(a, d, x);
// 			if(d&1) return (tmp != 1 && tmp != x-1);
// 			else if(tmp == x-1) return 0;
// 			d >>= 1;
// 		}
// 	}
// 	bool isprime(ll x){
// 		for(auto &i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
// 			if(x == i) return 1;
// 			if(x > 40 && miller_rabin(x, i)) return 0;
// 		}
// 		if(x <= 40) return 0;
// 		return 1;
// 	}
// };
// namespace pollard_rho{
// 	ll f(ll x, ll n, ll c){
// 		return (c + miller_rabin::mul(x, x, n)) % n;
// 	}
// 	void rec(ll n, vector<ll> &v){
// 		if(n == 1) return;
// 		if(n % 2 == 0){
// 			v.push_back(2);
// 			rec(n/2, v);
// 			return;
// 		}
// 		if(miller_rabin::isprime(n)){
// 			v.push_back(n);
// 			return;
// 		}
// 		ll a, b, c;
// 		while(1){
// 			a = rand() % (n-2) + 2;
// 			b = a;
// 			c = rand() % 20 + 1;
// 			do{
// 				a = f(a, n, c);
// 				b = f(f(b, n, c), n, c);
// 			}while(gcd(abs(a-b), n) == 1);
// 			if(a != b) break;
// 		}
// 		ll x = gcd(abs(a-b), n);
// 		rec(x, v);
// 		rec(n/x, v);
// 	}
// 	vector<ll> factorize(ll n){
// 		vector<ll> ret;
// 		rec(n, ret);
// 		sort(ret.begin(), ret.end());
// 		return ret;
// 	}
// };

__int128_t lcm(ll x, ll y) {
    __int128_t X = x, Y = y;
    while (y) {
        ll tmp = x;
        x = y, y = tmp % y;
    }
    return (X * Y / x);
}

int n;
ll m, a[202020];
map<ll, int> mp;

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void solve() {
    mp[1] = 1;
    for (int i = 1; i <= n; i++) {
        vector<pair<ll, int>> lazy_vec;
        for (auto& [x, cnt] : mp) {
            __int128_t y = lcm(x, a[i]);
            if (m % y == 0) {
                lazy_vec.push_back({ (ll)y, cnt });
            }
        }

        for (auto& [x, cnt] : lazy_vec) {
            mp[x] = (mp[x] + cnt) % MOD;
        }
    }
}

// ll solve() {
//     vector<ll> m_fac = pollard_rho::factorize(m); // O(M^{1/4})
    
//     map<ll, int> m_cnt;
//     for (auto& i : m_fac) m_cnt[i]++;

//     map<ll, int> m_hash;
//     m_fac.erase(unique(all(m_fac)), m_fac.end());
//     for (int i = 0; i < sz(m_fac); i++) {
//         m_hash[m_fac[i]] = i;
//     }

//     map<ll, ll> res;
//     res[0] = 1;

//     for (int i = 1; i <= n; i++) {
//         ll x = a[i];
//         map<ll, int> x_cnt;
//         for (auto& j : pollard_rho::factorize(x)) x_cnt[j]++; // O(10^4)

//         ll n_bit = 0;
//         bool invalid = 0;
//         for (auto& [val, cnt] : x_cnt) {
//             if (!m_cnt.count(val) || (m_cnt.count(val) && m_cnt[val] < cnt)) { invalid = 1; break; }

//             if (m_cnt[val] == cnt) n_bit |= (1ll << m_hash[val]);
//         }

//         if (invalid) continue;
        
//         vector<pll> lazy_upd;
//         for (auto& [bit, cnt] : res) {
//             lazy_upd.push_back({ (bit | n_bit), cnt });
//         }

//         for (auto& [bit, cnt] : lazy_upd) {
//             res[bit] = (res[bit] + cnt);
//         }
//     }

//     return res[(1ll << sz(m_hash)) - 1];
// }

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    solve();

    cout << mp[m];
}