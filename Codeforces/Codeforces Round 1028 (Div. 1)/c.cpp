// sum(h[i]) <= 8000
// do op2 1 time,
// do op2 2 times,
// ...
// do op2 (min_h-1) times

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

const int N = 22;
const int M = 4040;
const int H = 404;
const double EPS = 1e-8;

vector<vector<bool>> vis(M, vector<bool>(M));
vector<vector<double>> binomDP(M, vector<double>(M));
double binom(int n, int r) {
  if (r < 0 || n < r) return 0;
  double &ret = binomDP[n][r];
  if (vis[n][r]) return ret;
  vis[n][r] = 1;

  if (n == 0) return ret = 1;
  if (n == 1) return ret = 1;
  return binom(n - 1, r - 1) + binom(n - 1, r);
}

vector<double> powp(M), pownp(M);

int n, m, p;
vector<int> h;

void init() {}

void input() {
    cin >> n >> m >> p;
    h.resize(n);
    for (auto &i : h) cin >> i;
}
                                       
int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cout << fixed;
    cout.precision(8);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        powp[0] = pownp[0] = 1;
        for (int i = 1; i <= m; i++) {
            powp[i] = powp[i - 1] * p / 100;
            pownp[i] = pownp[i - 1] * (100 - p) / 100;
        }

        int min_h = INF, sum_h = 0;
        for (auto &i : h) {
            min_h = min(min_h, i);
            sum_h += i;
        }
        
        double ans = 0;

        for (int x = 0; x <= min_h - 1; x++) {
            int y = sum_h - n * (x + 1);

            if (x < 0 || m < x) continue;
            if (y < 0 || m < y) continue;
            if (x + y < 0 || m < x + y) continue;

            for (int i = x; i <= m - y; i++) {
                double res = powp[i] * pownp[m - i] * binom(m, i);
                int p = i, q = m - i;
                res *= binom(p, x);
                res *= binom(q, y);
                cout << x << ' ' << y << ' ' << i << ' ' << res << '\n';
                ans += res;
            }
        }

        cout << ans << '\n';
    }
}
