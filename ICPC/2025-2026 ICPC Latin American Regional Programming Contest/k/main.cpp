#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;
constexpr ll dx[] = {1, -1, 1, -1};
constexpr ll dy[] = {1, 1, -1, -1};

int n, k;
struct point { ll x, y; };
vector<point> p;

ll case1(point mx, point mn, ll rem) {
    ll diffx = mx.x - mn.x + 1;
    ll diffy = mx.y - mn.y + 1;

    if (diffx > diffy) swap(diffx, diffy);

    if (diffx < diffy) {
        ll add = min(rem, diffy - diffx);
        diffx += add;
        rem -= add;
    }

    if (rem > 0) {
        diffx += rem / 2;
        diffy += rem / 2;
        diffy += (rem & 1);
    }
    return diffx * diffy;
}

ll case2(point mx, point mn) {
    ll ret = 0;
    for (const auto &i : p) {
        for (int d = 0; d < 4; d++) {
            point np = i;
            np.x += dx[d] * k;
            np.y += dy[d] * k;

            point nmx{max(mx.x, np.x), max(mx.y, np.y)};
            point nmn{min(mn.x, np.x), min(mn.y, np.y)};
            ret = max(ret, case1(nmx, nmn, 0));
        }
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;

    point mx{-INF, -INF}, mn{INF, INF};

    p.resize(n);
    for (auto &i : p) {
        cin >> i.x >> i.y;
        mx.x = max(mx.x, i.x);
        mx.y = max(mx.y, i.y);
        mn.x = min(mn.x, i.x);
        mn.y = min(mn.y, i.y);
    }

    if (n == 1) {
        cout << 1;
        return 0;
    }

    ll ans = 0;
    ans = max(ans, case1(mx, mn, k));
    ans = max(ans, case2(mx, mn));

    cout << ans;
}