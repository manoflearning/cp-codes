#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
typedef long long ll;

const int MAXN = 1'000'000;

bool isPrime[MAXN + 1];
vector<int> prime;

void get_prime() {
	fill(isPrime + 2, isPrime + MAXN + 1, 1);
	for (ll i = 4; i <= MAXN; i += 2) isPrime[i] = 0;
	for (ll i = 3; i <= MAXN; i += 2) {
		if (!isPrime[i]) continue;
		prime.push_back(i);
		for (ll j = i * i; j <= MAXN; j += i * 2)
			isPrime[j] = 0;
	}
}

typedef vector<ll> poly;

const ll w = 3;
const ll mod = 998244353;

ll pw(ll a, ll b){
    ll ret = 1;
    while(b){
        if(b & 1) ret = ret * a % mod;
        b >>= 1; a = a * a % mod;
    }
    return ret;
}

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
    ll ang = pw(w, (mod - 1) / n); if(inv) ang = pw(ang, mod - 2);
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
    ll t = pw(n, mod - 2);
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

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    get_prime();

    vector<ll> a((MAXN + 2) / 2), b((MAXN + 2) / 2);
    for (auto& p : prime) {
        a[(p + 1) / 2] = b[(p + 1) / 2] = 1;
    }

    vector<ll> c = multiply(a, b);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        if (n == 4) cout << 1 << '\n';
        else cout << (c[(n + 2) / 2] + 1) / 2 << '\n';
    }
}
