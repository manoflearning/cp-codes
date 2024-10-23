#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

namespace miller_rabin {
ll mul(ll x, ll y, ll mod) { return (__int128_t)x * y % mod; }
ll ipow(ll x, ll y, ll p) {
  ll ret = 1, piv = x % p;
  while (y) {
    if (y & 1) ret = mul(ret, piv, p);
    piv = mul(piv, piv, p);
    y >>= 1;
  }
  return ret;
}
bool miller_rabin(ll x, ll a) {
  if (x % a == 0) return 0;
  ll d = x - 1;
  while (1) {
    ll tmp = ipow(a, d, x);
    if (d & 1) return (tmp != 1 && tmp != x - 1);
    else if (tmp == x - 1) return 0;
    d >>= 1;
  }
}
bool isprime(ll x) {
  for (auto &i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (x == i) return 1;
    if (x > 40 && miller_rabin(x, i)) return 0;
  }
  if (x <= 40) return 0;
  return 1;
}
}; // namespace miller_rabin
namespace pollard_rho {
ll f(ll x, ll n, ll c) {
  return (c + miller_rabin::mul(x, x, n)) % n;
}
void rec(ll n, vector<ll> &v) {
  if (n == 1) return;
  if (n % 2 == 0) {
    v.push_back(2);
    rec(n / 2, v);
    return;
  }
  if (miller_rabin::isprime(n)) {
    v.push_back(n);
    return;
  }
  ll a, b, c;
  while (1) {
    a = rand() % (n - 2) + 2;
    b = a;
    c = rand() % 20 + 1;
    do {
      a = f(a, n, c);
      b = f(f(b, n, c), n, c);
    } while (gcd(abs(a - b), n) == 1);
    if (a != b) break;
  }
  ll x = gcd(abs(a - b), n);
  rec(x, v);
  rec(n / x, v);
}
vector<ll> factorize(ll n) {
  vector<ll> ret;
  rec(n, ret);
  sort(ret.begin(), ret.end());
  return ret;
}
}; // namespace pollard_rho

ll poww(ll x, ll y, ll mod) {
    if (y == 0) return 1;
    if (y == 1) return x % mod;
    __int128_t res = poww(x, y / 2, mod);
    return res * res % mod * (y & 1 ? x : 1) % mod;
}
ll mul(ll x, ll y, ll mod) { return (__int128_t)x * y % mod; }
ll tonelli_shanks(ll n, ll p) {
	ll s = 0;
	ll q = p - 1;

	while ((q & 1) == 0) { q /= 2; ++s; }
	if (s == 1) {
		ll r = poww(n, (p + 1) / 4, p);
		if (mul(r, r, p) == n) return r;
		return 1;
	}
	
	ll z = 1;
	while (poww(++z, (p - 1) / 2, p) != p - 1);

	ll c = poww(z, q, p);
	ll r = poww(n, (q + 1) / 2, p);
	ll t = poww(n, q, p);
	ll m = s;
	while (t != 1) {
		ll tt = t;
		ll i = 0;
		while (tt != 1) {
			tt = mul(tt, tt, p);
			++i;
			if (i == m) {
			    return 1;
			}
		}
		ll b = poww(c, poww(2, m - i - 1, p - 1), p);
		ll b2 = mul(b, b, p);
		r = mul(r, b, p);
		t = mul(t, b2, p);
		c = b2;
		m = i;
	}
	if (mul(r, r, p) == n) return r;
	return 1;
}
tuple<ll, ll> cornacchia(ll n) {
	ll r1 = n;
    cout << "fuck 1\n";
	ll r2 = tonelli_shanks(r1 - 1, r1);
    cout << "fuck 2\n";
	while ((__int128_t)r1 * r1 >= n) {
		ll t = r1 % r2;
		r1 = r2;
		r2 = t;
	}
    cout << "fuck 3\n";
	ll x = r1, y = sqrt(n - r1 * r1);
	return {x, y};
}

int main() {
  #ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif

  cin.tie(NULL), cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  ll n; cin >> n;

  auto arr = pollard_rho::factorize(n);
  map<ll, int> mp;
  for (auto& i : arr) mp[i]++;

  bool odd = 0, odd_4k3 = 0;
  for (auto& [x, y] : mp) {
    if (y & 1) {
      odd = 1;
      if (x % 4 == 3) odd_4k3 = 1;
    }
  }

  if (!odd) {
    cout << 1 << '\n';
    cout << (ll)sqrt(n);
  }
  else if (!odd_4k3) {
    cout << 2 << '\n';
    ll ans1 = 1, ans2 = 1;
    for (auto& [x, y] : mp) {
      if (y & 1) ans2 *= poww(x, y, 4e18);
      else ans1 *= poww(x, y, 4e18);
    }
    // cout << ans1 << ' ' << ans2 << '\n';
    tuple<ll, ll> res = cornacchia(ans2);
    cout << get<0>(res) * ans1 << ' ' << get<1>(res) * ans2;
  }
  else {
    while (n % 4 == 0) n /= 4;
    if (n % 8 != 7) cout << 3;
    else cout << 4;
  }
}
