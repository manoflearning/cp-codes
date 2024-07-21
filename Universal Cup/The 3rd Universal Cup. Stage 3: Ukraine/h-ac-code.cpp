#include <map>
#include <set>
#include <array>
#include <cmath>
#include <deque>
#include <bitset>
#include <random>
#include <string>
#include <vector>
#include <cassert>
#include <complex>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

const int MOD = 998244353;

int add(int a, int b) {
  if (a + b < MOD)
    return a + b;
  return a + b - MOD;
}

int sub(int a, int b) {
  if (a >= b)
    return a - b;
  return a + MOD - b;
}

int mul(int a, int b) {
  return a * 1ll * b % MOD;
}

int pw(int a, int n) {
  int ans = 1;
  while (n) {
    if (n & 1)
      ans = mul(ans, a);
    n >>= 1;
    a = mul(a, a);
  }
  return ans;
}

const int G1 = 3;

void fft(vector<int>& A, bool inv = false) {
  int k = 0;
  while ((1 << k) < (int)A.size())
    ++k;
  int N = 1 << k;
  static vector<int> rev;
  static vector<uint32_t> power = {0, 1};
  rev.resize(N);
  for (int i = 0; i < N; ++i) {
    rev[i] = rev[i / 2] / 2 + ((i & 1) << (k - 1));
    if (i < rev[i]) swap(A[i], A[rev[i]]);
  }

  static auto mul = [](uint32_t a, uint32_t b) {
    return (uint64_t(a) * b) % MOD;
  };

  static vector<uint32_t> A1;
  A1.resize(N);
  for (int i = 0; i < N; ++i)
    A1[i] = A[i];
  for (int l = 1, t = 0; l < N; l *= 2, ++t) {
    if ((int) power.size() == l) {
      power.resize(2 * l);
      uint32_t w = pw(G1, (MOD - 1) / 2 / l);
      for (int i = l; i < 2 * l; ++i) {
        power[i] = power[i / 2];
        if (i & 1) power[i] = mul(power[i], w);
      }
    }
    if ((k - t - 1) & 3) {
      for (int i = 0; i < N; i += 2 * l) {
        for (int j = 0; j < l; ++j) {
          uint32_t x = A1[i + j], y = mul(power[j + l], A1[i + j + l]);
          A1[i + j] = x + y;
          A1[i + j + l] = x + MOD - y;
        }
      }
    } else {
      for (int i = 0; i < N; i += 2 * l) {
        for (int j = 0; j < l; ++j) {
          uint32_t x = A1[i + j], y = mul(power[j + l], A1[i + j + l]);
          A1[i + j] = (uint64_t(x) + y) % MOD;
          A1[i + j + l] = (uint64_t(x) + MOD - y) % MOD;
        }
      }
    }
  }

  for (int i = 0; i < N; ++i)
    A[i] = A1[i];

  if (inv) {
    reverse(A.begin() + 1, A.end());
    int anti = pw(N, MOD - 2);
    for (int i = 0; i < N; ++i)
      A[i] = mul(A[i], anti);
  }
}

vector<int> operator*(vector<int> a, vector<int> b) {
  int k = 1;
  while (k < int(a.size()) + int(b.size()) - 1)
    k *= 2;
  a.resize(k);
  b.resize(k);
  fft(a);
  fft(b);
  for (int i = 0; i < k; ++i)
    a[i] = mul(a[i], b[i]);
  fft(a, true);
  return a;
  /*vector<int> ans(a.size() + b.size() - 1);
  
  for (int i = 0; i < a.size(); ++i) {
    for (int j = 0; j < b.size(); ++j)
      ans[i + j] = add(ans[i + j], mul(a[i], b[j]));
  }
  return ans;*/
}

const int MAXN = 200'200;

int type[MAXN]; // 0: S, 1: F
vector<pair<int, int>> G[MAXN];
// u, dir
// 0: out, 1: in

int dp[MAXN][2];

vector<int> tmp[MAXN];


vector<int> combine(const vector<pair<int, int>>& vals) {
  if (vals.empty())
    return {1};
  int n = vals.size();
  for (int i = 0; i < n; ++i) {
    tmp[i].resize(2);
    tmp[i][0] = vals[i].first;
    tmp[i][1] = vals[i].second;
  }
  for (int l = 1; l < n; l *= 2) {
    for (int i = 0; i + l < n; i += 2 * l)
      tmp[i] = tmp[i] * tmp[i + l];
  }
  return tmp[0];
}

void dfs(int v, int p, int dir) {
  vector<pair<int, int>> child_in;
  vector<pair<int, int>> child_out;
  for (auto [u, d] : G[v]) {
    if (u == p)
      continue;
    dfs(u, v, d ^ 1);
    if (d == 0)
      child_out.emplace_back(dp[u][0], dp[u][1]);
    else
      child_in.emplace_back(dp[u][0], dp[u][1]);
  }
  vector<int> total_in = combine(child_in);
  vector<int> total_out = combine(child_out);
  /*cout << v << " total_in: ";
  for (int x : total_in)
    cout << x << ',';
  cout << " total_out: ";
  for (int x : total_out)
    cout << x << ',';
  cout << '\n';*/
  vector<int> kek(5);
  // from -2 to 2
  for (int b = -2; b <= 2; ++b) {
    for (int x = 0; x < total_in.size(); ++x) {
      int y = x - b;
      if (0 <= y && y < total_out.size())
        kek[2 + b] = add(kek[2 + b], mul(total_in[x], total_out[y]));
    }
  }
  vector<int> pos_b;
  pos_b.emplace_back(0);
  if (type[v] == 0)
    pos_b.emplace_back(-1);
  else
    pos_b.emplace_back(1);
  int up_edge_bal = dir == 0 ? -1 : 1;
  for (int take = 0; take < 2; ++take) {
    for (int b : pos_b) {
      int real_bal = b - take * up_edge_bal;
      dp[v][take] = add(dp[v][take], kek[2 + real_bal]);
    }
  }
  //cout << v << ' ' << dp[v][0] << ' ' << dp[v][1] << '\n';
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    char c;
    cin >> c;
    type[i] = c == 'S' ? 0 : 1;
  }
  for (int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    G[a].emplace_back(b, 0);
    G[b].emplace_back(a, 1);
  }
  dfs(0, -1, 0);
  cout << dp[0][0] << '\n';
  return 0;
}
