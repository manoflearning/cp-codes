#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

// Gauss-Jordan Elimination modulo p
vector<int> gauss_mod(vector<vector<int>> &a, int mod) {
  vector<int> inv(mod); // modulo inverse 전처리
  inv[1] = 1;
  for (int i = 2; i < mod; ++i)
    inv[i] = mod - (mod / i) * inv[mod % i] % mod;
  int n = a.size();
  int m = a[0].size();
  vector<int> w(m, -1); // i번째 열에 있는 pivot이 몇 번째 행에 있는지 저장
  for (int c = 0, r = 0; c < m && r < n; ++c) {
    int p = r; // pivot row
    for (int i = r; i < n; ++i)
      if (a[p][c] < a[i][c])
        p = i;
    if (a[p][c] == 0) continue; // free variable
    for (int j = 0; j < m; ++j)
      swap(a[p][j], a[r][j]);
    w[c] = r;
    int t = a[r][c];
    for (int j = 0; j < m; ++j)
      a[r][j] = a[r][j] * inv[t] % mod;
    for (int i = 0; i < n; ++i)
      if (i != r) {
        int t = a[i][c];
        for (int j = c; j < m; ++j)
          a[i][j] = (a[i][j] - a[r][j] * t % mod + mod) % mod;
      }
    ++r;
  }
  for (int i = 0; i < n; ++i) // existence of solution
    if (count(a[i].begin(), --a[i].end(), 0) == m - 1 && a[i][m - 1])
      return vector<int>(); // no solution
  vector<int> ans(m);
  for (int i = 0; i < m; ++i)
    if (~w[i]) ans[i] = a[w[i]][m - 1];
  return ans; // solution exist
}

int p, n;
string s;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cin >> p >> s;
        n = sz(s);

        vector<vector<int>> a(n, vector<int>(n + 1));
        for (int i = 0; i < n; i++) {
            a[i][0] = 1;
            for (int j = 0; j + 1 < n; j++) {
                a[i][j + 1] = (i + 1) * a[i][j] % p;
            }
            a[i][n] = (s[i] == '*' ? 0 : s[i] - 'a' + 1);
        }

        // DEBUG
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < n; j++) {
        //         cout << a[i][j] << ' ';
        //     }
        //     cout << '\n';
        // }
        // cout << '\n';

        vector<int> ans;
        for (int x = 0; x < p; x++) {
            auto tmp = a;
            // for (int i = 0; i < n; i++) {
            //     tmp[i][n - 1] -= x;
            //     tmp[i][n - 1] %= p;
            //     tmp[i][n - 1] = (tmp[i][n - 1] + p) % p;
            // }

            auto res = gauss_mod(tmp, p);
            if (!res.empty()) {
                for (auto &i : res) ans.push_back(i);
                ans.pop_back();
                break;
            }
        }

        for (auto &i : ans) cout << i << ' ';
        cout << '\n';
    }
}
