#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAX = 1e6;
bool isPrime[MAX + 1];
vector<int> prime(1, 2);
void getPrime() {
  fill(isPrime + 2, isPrime + MAX + 1, 1);
  for (ll i = 4; i <= MAX; i += 2)
    isPrime[i] = 0;
  for (ll i = 3; i <= MAX; i += 2) {
    if (!isPrime[i]) continue;
    prime.push_back(i);
    for (ll j = i * i; j <= MAX; j += i * 2)
      isPrime[j] = 0;
  }
}

int flag; // array size
struct Seg {
  vector<ll> t;
  void build(int n) {
    t.clear();
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(flag << 1);
  }
  void add(int p, ll value) { // add value at position p
    for (t[p += flag - 1] += value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
  }
  ll kth(ll k, int n = 1) { // find the kth smallest number (1-indexed)
    assert(t[n] >= k);
    if (flag <= n) return n - flag + 1;
    if (k <= t[n << 1]) return kth(k, n << 1);
    else return kth(k - t[n << 1], n << 1 | 1);
  }
} seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    getPrime();

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        
        seg.build(n);

        for (int i = 3; i <= n; i++) seg.add(i, 1);

        vector<int> res;
        res.push_back(2);
        res.push_back(1);

        ll sum = 3, cnt = 2;
        while (sz(res) < n) {
            int turn = sz(res) + 1;

            int lb = seg.kth(1);
            int now_tg = *lower_bound(all(prime), (sum + lb + turn - 1) / turn);

            int l = 1, r = n - sz(res);
            while (l < r) {
                int mid = (l + r) >> 1;

                int x = seg.kth(mid);

                if ((sum + x + turn - 1) / turn >= now_tg) r = mid;
                else l = mid + 1; 
            }

            int x = seg.kth(l);

            sum += x;
            if (isPrime[(sum + turn - 1) / turn]) cnt++;
            res.push_back(x);
            seg.add(x, -1);

            if (turn / 3 - 1 > cnt) {
                assert(0);
            }
        }

        for (auto &i : res) cout << i << ' ';
        cout << '\n';
    }
}
