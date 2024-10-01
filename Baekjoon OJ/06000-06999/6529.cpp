#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

struct Painting {
    ll x1, y1, x2, y2;
};

int n;
ll w, h;
vector<Painting> p;
ll wp, hp;

vector<ll> xx, yy;

ll px[444], py[444];
ll a[444][444], psum[444][444];

int ansx = INF, ansy = INF;

void init() {
    p.clear();
    xx.clear();
    yy.clear();
    memset(px, 0, sizeof(px));
    memset(py, 0, sizeof(py));
    memset(a, 0, sizeof(a));
    memset(psum, 0, sizeof(psum));
    ansx = ansy = INF;
}

void input() {
    cin >> n >> w >> h;
    p.resize(n);
    for (auto& i : p) {
        cin >> i.x1 >> i.y1 >> i.x2 >> i.y2;
    }
    cin >> wp >> hp;
}

void coor_comp() {
    xx.push_back(-1);
    yy.push_back(-1);

    xx.push_back(0);
    xx.push_back(w);
    yy.push_back(0);
    yy.push_back(h);
    for (auto& i : p) {
        xx.push_back(i.x1);
        xx.push_back(i.x2);
        yy.push_back(i.y1);
        yy.push_back(i.y2);
    }

    sort(all(xx));
    xx.erase(unique(all(xx)), xx.end());
    sort(all(yy));
    yy.erase(unique(all(yy)), yy.end());

    for (auto& i : p) {
        i.x1 = lower_bound(all(xx), i.x1) - xx.begin();
        i.x2 = lower_bound(all(xx), i.x2) - xx.begin();
        i.y1 = lower_bound(all(yy), i.y1) - yy.begin();
        i.y2 = lower_bound(all(yy), i.y2) - yy.begin();
    }
}

void build_psum() {
    for (int i = 1; i < sz(xx); i++) px[i] = xx[i];
    for (int i = 1; i < sz(yy); i++) py[i] = yy[i];

    for (auto& i : p) {
        a[i.x1][i.y1]++;
        a[i.x1][i.y2]--;
        a[i.x2][i.y1]--;
        a[i.x2][i.y2]++;
    }

    for (int i = 1; i < sz(xx); i++) {
        for (int j = 1; j < sz(yy); j++) {
            a[i][j] += a[i][j - 1];
            a[i][j] += a[i - 1][j];
            a[i][j] -= a[i - 1][j - 1];

            psum[i][j] += a[i][j];
            psum[i][j] += psum[i - 1][j];
            psum[i][j] += psum[i][j - 1];
            psum[i][j] -= psum[i - 1][j - 1];
        }
    }
}

inline ll sumx(int x1, int x2) { return px[x2] - px[x1]; }
inline ll sumy(int y1, int y2) { return py[y2] - py[y1]; }

inline ll sum(int x1, int y1, int x2, int y2) {
    ll ret = 0;
    ret += psum[x2 - 1][y2 - 1];
    ret -= psum[x1 - 1][y2 - 1];
    ret -= psum[x2 - 1][y1 - 1];
    ret += psum[x1 - 1][y1 - 1];
    return ret;
}

void solve() {
    for (int x = 1; x < sz(xx); x++) {
        for (int y = 1; y < sz(yy); y++) {
            int l = x + 1, r = sz(xx) - 1;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (sumx(x, mid) < wp) l = mid + 1;
                else r = mid;
            }
            int x2 = l;

            l = y + 1, r = sz(yy) - 1;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (sumy(y, mid) < hp) l = mid + 1;
                else r = mid;
            }
            int y2 = l;

            if (sumx(x, x2) < wp || sumy(y, y2) < hp) continue;
            if (sum(x, y, x2, y2) > 0) continue;

            if (y < ansy || (y == ansy && x < ansx)) {
                ansy = y, ansx = x;
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        coor_comp();

        build_psum();

        solve();

        if (ansx == INF) cout << "Fail!\n";
        else cout << xx[ansx] << ' ' << yy[ansy] << '\n';
    }
}
