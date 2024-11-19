#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>

const int MAXN = 101010;
const int MAXQ = 101010;

int n, q, mod;
int a[MAXN];
struct Query {
    int l, r, idx;
};
Query b[MAXQ];
int psum[33][MAXN];

void input() {
    cin >> n >> q >> mod;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= q; i++) {
        cin >> b[i].l >> b[i].r;
        b[i].idx = i;
    }
}

void build_psum() {
    for (int i = 1; i <= n; i++) {
        psum[a[i] % mod][i]++;
        for (int j = 0; j < mod; j++) {
            psum[j][i] += psum[j][i - 1];
        }
    }
}

pair<pll, ll> egcd(ll a, ll b) {
  ll s = 0, olds = 1;
  ll t = 1, oldt = 0;
  ll r = b, oldr = a;
  while (r != 0) {
    ll q = oldr / r;
    ll tmp = oldr - q * r;
    oldr = r, r = tmp;
    tmp = olds - q * s;
    olds = s, s = tmp;
    tmp = oldt - q * t;
    oldt = t, t = tmp;
  }
  // a * olds + b * oldt = d
  // oldr = gcd(a, b)
  return {{olds, oldt}, oldr};
}
ll linearCongruence(ll a, ll b, ll n) { // Find x such that ax = b (mod n).
  pair<pll, ll> res = egcd(a, n);
  // ax + ny = b has a solution iff gcd(a,n) | b.
  if (b % res.second) return -1;
  return (res.first.first + n) % n;
}
ll modInv(ll a, ll p) { // Find x such that ax = 1 (mod p).
  pair<pll, ll> res = egcd(a, p);
  // Modular inverse exists iff gcd(a, p) = 1.
  if (res.second == 1) return (res.first.first + p) % p;
  else return -1;
}

int solve(int l, int r) {
    vector<int> cnt(mod);
    for (int i = 0; i < mod; i++)
        cnt[i] = psum[i][r] - psum[i][l - 1];
    
    for (int y = 1; y <= mod; y++) {
        int yinv = modInv(y % mod, mod);
        if (yinv == -1) continue;

        int target = (mod - 1) * yinv % mod;
        for (int i = 0; i < mod; i++) {
            if (cnt[i] >= 2) {
                if (i * i % mod == target) return y;
            }
            for (int j = i + 1; j < mod; j++) {
                if (cnt[i] && cnt[j]) {
                    if (i * j % mod == target) return y;
                }
            }
        }
    }
    return -1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    build_psum();

    for (int i = 1; i <= q; i++) {
        cout << solve(b[i].l, b[i].r) << '\n';
    }
}
