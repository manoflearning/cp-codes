#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int MOD = 1'699'741'697;
constexpr int N = 202020;
constexpr int INF = 1e9 + 7;

int n, k;
int l[N], r[N];
map<int, int> psum;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        if (k < r[i] - l[i] + 1) ans++;
        else {
            int l_mod = l[i] % k;
            int r_mod = r[i] % k;
            if (r_mod < l_mod) {
                psum[0]++;
                psum[r_mod + 1]--;
                psum[l_mod]++;
                psum[k]--;
            } else {
                psum[l_mod]++;
                psum[r_mod + 1]--;
            }
        }
    }

    int mx = 0, acc = 0;
    for (auto &[_, v] : psum) {
        acc += v;
        mx = max(mx, acc);
    }
    ans += mx;

    cout << ans;
}
