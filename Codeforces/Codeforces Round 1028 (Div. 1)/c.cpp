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

int n, m, p;
vector<int> h;
vector<double> powp(M);

map<tuple<short, short, short>, double> dp_naive;

void init() {
    dp_naive.clear();
}

double naive(short turn, short min_h, short sum_h) {
    // base case
    if (min_h == 1 && sum_h == n) return 1;
    {
        int rem = ((sum_h - n - turn)) / (n - 1);
        if (rem > turn || (rem >= 0 && powp[rem] < 1e-8)) return 0;
    }
    if (turn == 0) return 0;

    // inductive step
    if (dp_naive.count({turn, min_h, sum_h})) return dp_naive[{turn, min_h, sum_h}];
    auto &ret = dp_naive[{turn, min_h, sum_h}];
    
    double op1 = naive(turn - 1, min_h, sum_h);

    double res1 = 0, res2 = 0;
    if (min_h >= 2 && sum_h >= 2 * n) {
        res1 = max(res1, naive(turn - 1, min_h - 1, sum_h - n));
    }
    res1 = max(res1, op1);

    if (sum_h > n * min_h) {
        if (sum_h >= n + 1)
            res2 = max(res2, naive(turn - 1, min_h, sum_h - 1));
    } else {
        if (min_h >= 2 && sum_h >= n + 1)
            res2 = max(res2, naive(turn - 1, min_h - 1, sum_h - 1));
    }
    res2 = max(res2, op1);

    return ret = res1 * p / 100 + res2 * (100 - p) / 100;
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

        cin >> n >> m >> p;
        h.resize(n);

        powp[0] = 1;
        for (int i = 1; i <= m; i++)
            powp[i] = powp[i - 1] * p / 100;
        
        int min_h = INF, sum_h = 0;
        for (auto &i : h) {
            cin >> i;
            min_h = min(min_h, i);
            sum_h += i;
        }

        cout << naive(m, min_h, sum_h) << '\n';
    }
}
