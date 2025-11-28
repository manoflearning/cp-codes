#include <bits/stdc++.h>
#include <bit>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

template <int m>
class modint {
  static_assert(m > 0, "Modulus must be positive");

public:
  static constexpr int mod() { return m; }
  constexpr modint(ll y = 0) : x(y >= 0 ? y % m : (y % m + m) % m) {}
  constexpr int val() const { return x; }
  constexpr modint &operator+=(const modint &r) {
    if ((x += r.x) >= m) x -= m;
    return *this;
  }
  constexpr modint &operator-=(const modint &r) {
    if ((x += m - r.x) >= m) x -= m;
    return *this;
  }
  constexpr modint &operator*=(const modint &r) {
    x = static_cast<int>(1LL * x * r.x % m);
    return *this;
  }
  constexpr modint &operator/=(const modint &r) { return *this *= r.inv(); }
  constexpr bool operator==(const modint &r) const { return x == r.x; }
  constexpr modint operator+() const { return *this; }
  constexpr modint operator-() const { return modint{-x}; }
  constexpr friend modint operator+(const modint &l, const modint &r) {
    return modint{l} += r;
  }
  constexpr friend modint operator-(const modint &l, const modint &r) {
    return modint{l} -= r;
  }
  constexpr friend modint operator*(const modint &l, const modint &r) {
    return modint{l} *= r;
  }
  constexpr friend modint operator/(const modint &l, const modint &r) {
    return modint{l} /= r;
  }
  constexpr modint inv() const {
    int a = x, b = m, u = 1, v = 0;
    while (b > 0) {
      int t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return modint{u};
  }
  constexpr modint pow(ll n) const {
    modint ret(1), mul(x);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  friend ostream &operator<<(ostream &os, const modint &r) {
    return os << r.x;
  }
  friend istream &operator>>(istream &is, modint &r) {
    ll t;
    is >> t;
    r = modint{t};
    return is;
  }

private:
  int x;
};

ll inv_mod(ll a, ll p) { // Find x such that ax = 1 (mod p).
  ll b = p, u = 1, v = 0;
  while (b) {
    ll t = a / b;
    a -= t * b;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  if (u < 0) u += p;
  return u;
}

constexpr int get_primitive_root(int mod) {
  if (mod == 167772161) return 3;
  if (mod == 469762049) return 3;
  if (mod == 754974721) return 11;
  if (mod == 998244353) return 3;
  if (mod == 1224736769) return 3;
}
template <typename mint>
void ntt(vector<mint> &a) {
  constexpr int mod = mint::mod();
  constexpr mint primitive_root = get_primitive_root(mod);

  const int n = sz(a);
  for (int m = n; m > 1; m >>= 1) {
    mint omega = primitive_root.pow((mod - 1) / m);
    for (int s = 0; s < n / m; ++s) {
      mint w = 1;
      for (int i = 0; i < m / 2; ++i) {
        mint l = a[s * m + i];
        mint r = a[s * m + i + m / 2];
        a[s * m + i] = l + r;
        a[s * m + i + m / 2] = (l - r) * w;
        w *= omega;
      }
    }
  }
}
template <typename mint>
void intt(vector<mint> &a) {
  constexpr int mod = mint::mod();
  constexpr mint primitive_root = get_primitive_root(mod);

  const int n = sz(a);
  for (int m = 2; m <= n; m <<= 1) {
    mint omega = primitive_root.pow((mod - 1) / m).inv();
    for (int s = 0; s < n / m; ++s) {
      mint w = 1;
      for (int i = 0; i < m / 2; ++i) {
        mint l = a[s * m + i];
        mint r = a[s * m + i + m / 2] * w;
        a[s * m + i] = l + r;
        a[s * m + i + m / 2] = l - r;
        w *= omega;
      }
    }
  }
}
template <typename mint>
vector<mint> convolution(vector<mint> a, vector<mint> b) {
  const int size = sz(a) + sz(b) - 1;
  int n = 1;
  while (n < size) n <<= 1;
  a.resize(n), b.resize(n);
  ntt(a), ntt(b);
  for (int i = 0; i < n; ++i) a[i] *= b[i];
  intt(a);
  a.resize(size);
  mint n_inv = mint(n).inv();
  for (int i = 0; i < size; ++i) a[i] *= n_inv;
  return a;
}
vector<ll> convolution_ll(const vector<ll> &a,
                          const vector<ll> &b) {
  static constexpr ll m0 = 167772161;
  static constexpr ll m1 = 469762049;
  static constexpr ll m2 = 754974721;
  static constexpr ll m01 = m0 * m1;
  static constexpr __int128_t m012 = (__int128_t)m01 * m2;

  static const ll inv_m0_mod_m1 = inv_mod(m0 % m1, m1);
  static const ll inv_m01_mod_m2 = inv_mod(m01 % m2, m2);

  using mint0 = modint<m0>;
  using mint1 = modint<m1>;
  using mint2 = modint<m2>;

  vector<mint0> a0(all(a)), b0(all(b));
  vector<mint1> a1(all(a)), b1(all(b));
  vector<mint2> a2(all(a)), b2(all(b));

  auto c0 = convolution(a0, b0);
  auto c1 = convolution(a1, b1);
  auto c2 = convolution(a2, b2);

  vector<ll> c(sz(c0));
  for (int i = 0; i < sz(c1); ++i) {
    ll r0 = c0[i].val();
    ll r1 = c1[i].val();
    ll r2 = c2[i].val();

    ll t1 = (r1 - r0) % m1;
    if (t1 < 0) t1 += m1;
    ll k1 = (ll)((__int128_t)t1 * inv_m0_mod_m1 % m1);
    __int128_t x01 = r0 + (__int128_t)m0 * k1;

    ll x01_mod_m2 = (ll)(x01 % m2);
    ll t2 = (r2 - x01_mod_m2) % m2;
    if (t2 < 0) t2 += m2;
    ll k2 = (ll)((__int128_t)t2 * inv_m01_mod_m2 % m2);
    __int128_t x = x01 + (__int128_t)m01 * k2;

    if (x >= m012 / 2) x -= m012;

    c[i] = (ll)x;
  }
  return c;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<ll> a(n + 1), b(m + 1);
    for (auto &i : a) cin >> i;
    for (auto &i : b) cin >> i;

    vector<ll> c = convolution_ll(a, b);

    ll ans = 0;
    for (auto &i : c) ans ^= i;

    cout << ans;
}