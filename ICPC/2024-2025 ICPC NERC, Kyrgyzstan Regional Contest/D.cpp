#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXA = 2020202;
const int MAXN = 1010101;

vector<int> sp(MAXA + 1);
vector<ll> prime;
// Determine prime numbers between 1 and MAXN in O(MAXN)
void linearSieve() {
  for (int i = 2; i <= MAXA; i++) {
    if (!sp[i]) {
      prime.push_back(i);
      sp[i] = i;
    }
    for (auto j : prime) {
      if (i * j > MAXA) break;
      sp[i * j] = j;
      if (i % j == 0) break;
    }
  }
}
// factorization in O(log x)
vector<int> factorization(int x) {
  vector<int> ret;
  while (x > 1) {
    ret.push_back(sp[x]);
    x /= sp[x];
  }
  sort(all(ret));
  ret.erase(unique(all(ret)), ret.end());
  return ret;
}

vector<int> arr[MAXA];
vector<int> adj[MAXN];

int dp[MAXN], opt[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    linearSieve();

    int n; cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> ord(n);
    iota(all(ord), 1);

    sort(all(ord), [&](int p1, int p2) {
        return a[p1] < a[p2];
    });

    vector<bool> vis(MAXA);
    for (auto i : ord) {
        if (vis[a[i]]) continue;
        vis[a[i]] = 1;
        vector<int> ps = factorization(a[i]);
        for (auto j : ps) arr[j].push_back(i);
    }

    for (auto i : prime) {
        for (int j = 0; j + 1 < sz(arr[i]); j++) {
            adj[arr[i][j]].push_back(arr[i][j + 1]);
        }
    }

    for (auto i : ord) {
        if (dp[i] == 0) {
            dp[i] = 1;
            opt[i] = -1;
        }

        for (auto j : adj[i]) {
            if (dp[j] < dp[i] + 1) {
                dp[j] = dp[i] + 1;
                opt[j] = i;
            }
        }
    }

    int optp = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[optp] < dp[i]) optp = i;
    }

    cout << dp[optp] << '\n';
    vector<int> ans;
    while (optp != -1) {
        ans.push_back(optp);
        optp = opt[optp];
    }
    reverse(all(ans));
    for (auto i : ans) cout << i << ' ';
}
