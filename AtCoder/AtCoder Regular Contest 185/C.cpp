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

typedef vector<ll> poly;
 
ll pw(ll a, ll b, ll mod){
    ll ret = 1;
    while(b){
        if(b & 1) ret = ret * a % mod;
        b >>= 1; a = a * a % mod;
    }
    return ret;
}
 
template<ll mod, ll w>
class NTT{
public:
    void ntt(poly &f, bool inv = 0){
        int n = f.size(), j = 0;
        vector<ll> root(n >> 1);
        for(int i=1; i<n; i++){
            int bit = (n >> 1);
            while(j >= bit){
                j -= bit; bit >>= 1;
            }
            j += bit;
            if(i < j) swap(f[i], f[j]);
        }
        ll ang = pw(w, (mod - 1) / n, mod); if(inv) ang = pw(ang, mod - 2, mod);
        root[0] = 1; for(int i=1; i<(n >> 1); i++) root[i] = root[i-1] * ang % mod;
        for(int i=2; i<=n; i<<=1){
            int step = n / i;
            for(int j=0; j<n; j+=i){
                for(int k=0; k<(i >> 1); k++){
                    ll u = f[j | k], v = f[j | k | i >> 1] * root[step * k] % mod;
                    f[j | k] = (u + v) % mod;
                    f[j | k | i >> 1] = (u - v) % mod;
                    if(f[j | k | i >> 1] < 0) f[j | k | i >> 1] += mod;
                }
            }
        }
        ll t = pw(n, mod - 2, mod);
        if(inv) for(int i=0; i<n; i++) f[i] = f[i] * t % mod;
    }
    vector<ll> multiply(poly &_a, poly &_b){
        vector<ll> a(all(_a)), b(all(_b));
        int n = 2;
        while(n < a.size() + b.size()) n <<= 1;
        a.resize(n); b.resize(n);
        ntt(a); ntt(b);
        for(int i=0; i<n; i++) a[i] = a[i] * b[i] % mod;
        ntt(a, 1);
        return a;
    }
};
 
ll ext_gcd(ll a, ll b, ll &x, ll &y) { //ax + by = gcd(a, b)
  ll g = a; x = 1, y = 0;
  if (b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
  return g;
}
 
const ll m1 = 2281701377, m2 = 2483027969, m3 = 998244353;
NTT<m1, 3> ntt1;
NTT<m2, 3> ntt2;
NTT<m3, 3> ntt3;
 
ll f(const vector<ll> &a, ll mod){
    int sz = a.size();
    vector<ll> rmn(sz), lm(sz, 1);
    ll ans = 0, M = 1;
    vector<ll> m({m1, m2, m3}); //prime list
 
    for(int i=0; i<sz; i++){
        ll k = a[i] - rmn[i]; k %= m[i];
        if(k < 0) k += m[i];
        ll x, y;
        ext_gcd(lm[i], m[i], x, y);
        k *= x; k %= m[i];
        if(k < 0) k += m[i];
        ans += k * M % mod;
        ans %= mod;
        for(int t=i+1; t<sz; t++){
            rmn[t] += lm[t] * k;
            rmn[t] %= m[t];
            lm[t] *= m[i];
            lm[t] %= m[t];
        }
        M *= m[i]; M %= mod;
    }
    return ans;
}
 
poly multiply(poly& a, poly& b, ll mod){
    poly a1(a), a2(a), a3(a);
    poly b1(b), b2(b), b3(b);
    poly res1 = ntt1.multiply(a1, b1);
    poly res2 = ntt2.multiply(a2, b2);
    poly res3 = ntt3.multiply(a3, b3);
    poly ret(res1.size());
    for(int i=0; i<res1.size(); i++){
        ret[i] = f({res1[i], res2[i], res3[i]}, mod);
    }
    return ret;
}

const int MAXN = 1010101;

int n, X;
int a[MAXN];

vector<ll> cnt1;

int ans1, ans2, ans3;

int vis[1010101];
void get_ans23(int Y) {
    for (int i = 1; i <= n; i++) {
        if (i == ans1) continue;

        if (Y > a[i] && vis[Y - a[i]]) {
            ans2 = vis[Y - a[i]];
            ans3 = i;
            return;
        }

        vis[a[i]] = i;
    }

    assert(0);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n >> X;
    for (int i = 1; i <= n; i++) cin >> a[i];

    cnt1.resize(X + 1);
    for (int i = 1; i <= n; i++) {
        cnt1[a[i]]++;
    }

    vector<ll> arr1 = multiply(cnt1, cnt1, 4e18);
    arr1.resize(X + 1);

    for (int i = 1; i <= n; i++) {
        ll res = a[i] + a[i];
        if (2 * a[i] <= X) arr1[2 * a[i]]--;
    }
    for (auto& i : arr1) {
        assert(i % 2 == 0);
        i /= 2;
    }

    for (int i = 1; i <= n; i++) {
        int p = a[i], q = X - a[i];
        ll neg = 0;
        if (q <= p) neg = 0;
        else {
            if (p == q - p) neg = cnt1[q - p] - 1;
            else neg = cnt1[q - p];
        }

        if (arr1[q] - neg <= 0) continue;
        ans1 = i;
        get_ans23(q);
        break;
    }

    if (ans1 == 0) {
        cout << -1;
        exit(0);
    }

    if (ans1 > ans2) swap(ans1, ans2);
    if (ans2 > ans3) swap(ans2, ans3);
    if (ans1 > ans2) swap(ans1, ans2);

    cout << ans1 << ' ' << ans2 << ' ' << ans3 << '\n';
}
