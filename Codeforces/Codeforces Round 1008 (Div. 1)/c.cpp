#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998'244'353;
const int N = 202020;

namespace fft{
  using real_t = double; using cpx = complex<real_t>;
  void FFT(vector<cpx> &a, bool inv_fft = false){
    int N = a.size();
    vector<cpx> root(N/2);
    for(int i=1, j=0; i<N; i++){
      int bit = (N >> 1);
      while(j >= bit) j -= bit, bit >>= 1;
      j += bit;
      if(i < j) swap(a[i], a[j]);
    }
    real_t ang = 2 * acos(-1) / N * (inv_fft ? -1 : 1);
    for(int i=0; i<N/2; i++) root[i] = cpx(cos(ang * i), sin(ang * i));
    /*
    XOR Convolution : set roots[*] = 1.
    OR Convolution : set roots[*] = 1, and do following:
    if (!inv) a[j + k] = u + v, a[j + k + i/2] = u;
    else a[j + k] = v, a[j + k + i/2] = u - v;
    */
    for(int i=2; i<=N; i<<=1){
      int step = N / i;
      for(int j=0; j<N; j+=i) for(int k=0; k<i/2; k++){
        cpx u = a[j+k], v = a[j+k+i/2] * root[step * k];
        a[j+k] = u+v; a[j+k+i/2] = u-v;
      }
    }
    if(inv_fft) for(int i=0; i<N; i++) a[i] /= N; // skip for OR convolution.
  }
  vector<ll> multiply(const vector<ll> &_a, const vector<ll> &_b){
    vector<cpx> a(all(_a)), b(all(_b));
    int N = 2; while(N < a.size() + b.size()) N <<= 1;
    a.resize(N); b.resize(N);
    FFT(a); FFT(b);
    for(int i=0; i<N; i++) a[i] *= b[i];
    FFT(a, 1);
    vector<ll> ret(N);
    for(int i=0; i<N; i++) ret[i] = llround(a[i].real());
    return ret;
  }
  vector<ll> multiply_mod(const vector<ll> &a, const vector<ll> &b, const ull mod){
    int N = 2; while(N < a.size() + b.size()) N <<= 1;
    vector<cpx> v1(N), v2(N), r1(N), r2(N);
    for(int i=0; i<a.size(); i++) v1[i] = cpx(a[i] >> 15, a[i] & 32767);
    for(int i=0; i<b.size(); i++) v2[i] = cpx(b[i] >> 15, b[i] & 32767);
    FFT(v1); FFT(v2);
    for(int i=0; i<N; i++){
      int j = i ? N-i : i;
      cpx ans1 = (v1[i] + conj(v1[j])) * cpx(0.5, 0);
      cpx ans2 = (v1[i] - conj(v1[j])) * cpx(0, -0.5);
      cpx ans3 = (v2[i] + conj(v2[j])) * cpx(0.5, 0);
      cpx ans4 = (v2[i] - conj(v2[j])) * cpx(0, -0.5);
      r1[i] = (ans1 * ans3) + (ans1 * ans4) * cpx(0, 1);
      r2[i] = (ans2 * ans3) + (ans2 * ans4) * cpx(0, 1);
    }
    FFT(r1, true); FFT(r2, true);
    vector<ll> ret(N);
    for(int i=0; i<N; i++){
      ll av = llround(r1[i].real()) % mod;
      ll bv = ( llround(r1[i].imag()) + llround(r2[i].real()) ) % mod;
      ll cv = llround(r2[i].imag()) % mod;
      ret[i] = (av << 30) + (bv << 15) + cv;
      ret[i] %= mod; ret[i] += mod; ret[i] %= mod;
    }
    return ret;
  }
}

ll fac[N], inv[N], facInv[N];
ll binom(int n, int r) {
    return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

int n, q;
string s;

ll cnt0 = 0, cnt1 = 0;
ll ans = 0;
vector<int> qu;

void init() {
    cnt0 = 0, cnt1 = 0;
    ans = 0;
}

void input() {
    cin >> n >> q;
    cin >> s;
    qu.resize(q);
    for (auto &i : qu) { cin >> i; i--; }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // Preprocessing in O(N)
    fac[0] = fac[1] = inv[1] = 1;
    facInv[0] = facInv[1] = 1;
    for (int i = 2; i < N; i++) {
        fac[i] = i * fac[i - 1] % MOD;
        inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
        if (inv[i] < 0) inv[i] += MOD;
        facInv[i] = facInv[i - 1] * inv[i] % MOD;
    }

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        vector<ll> a(n + 1);
        for (int i = 0; i <= n; i++) {
            a[i] = binom(n, i);
        }

        vector<ll> b(2 * n + 1);
        for (ll l = -n; l <= n; l++) {
            ll x = (abs(l) / 2) * ((abs(l) + 1) / 2) % MOD;
            b[l + n] = x;
        }

        auto ans = fft::multiply_mod(a, b, MOD);
        for (auto &i : s) {
            cnt0 += (i == '0');
            cnt1 += (i == '1');
        }

        // DEBUG
        // for (auto &i : ans) cout << i << ' ';
        // cout << "\n\n";

        for (auto &i : qu) {
            if (s[i] == '0') {
                cnt0--; cnt1++; s[i] = '1';
            } else {
                cnt0++; cnt1--; s[i] = '0';
            }
            cout << (ans[cnt1 + n] % MOD + MOD) % MOD << '\n';
        }
    }
}

