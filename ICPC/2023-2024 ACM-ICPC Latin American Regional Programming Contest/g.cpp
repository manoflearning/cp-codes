#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;
const int MAXN = 101010;
const int MAXX = 121212;
const int MAXY = 121212;

const int BUF = 60606;

struct Box {
    ll x1, y1, x2, y2;
};

int n;
ll xx[MAXN], yy[MAXN], d[MAXN];
ll xp[MAXN], yp[MAXN];

set<pll> ps;

Box a[MAXN];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> xx[i] >> yy[i] >> d[i];

        if (d[i] == 0) {
            ps.insert({ xx[i], yy[i] });
            continue;
        }

        xp[i] = xx[i] - yy[i];
        yp[i] = xx[i] + yy[i];

        a[i].x1 = xp[i] - d[i] + BUF;
        a[i].x2 = xp[i] + d[i] + BUF;
        a[i].y1 = yp[i] - d[i] + BUF;
        a[i].y2 = yp[i] + d[i] + BUF;
    }
}

vector<pll> ans;

vector<pll> f_line() {
    vector<pll> ret;

    vector<int> cntx(MAXX);
    for (int i = 1; i <= n; i++) {
        cntx[a[i].x1]++;
        cntx[a[i].x2]++;
    }

    for (int x = 1; x < MAXX; x++) {
        if (cntx[x] != n) continue;

        vector<int> psum(MAXY);
        for (int i = 1; i <= n; i++) {
            if (a[i].x1 == x || a[i].x2 == x) {
                psum[a[i].y1]++;
                psum[a[i].y2 + 1]--;
            }
        }

        for (int y = 1; y < MAXY; y++) {
            psum[y] += psum[y - 1];

            if (psum[y] == n) {
                ret.push_back({ x, y });
            }
        }
    }

    return ret;
}

bool is_contain(pll a, pll b, pll c) {
    if (b > c) swap(b, c);
    if (a.fr == b.fr && a.fr == c.fr) {
        if (b.sc <= a.sc && a.sc <= c.sc) return 1;
        else return 0;
    }
    if (a.sc == b.sc && a.sc == c.sc) {
        if (b.fr <= a.fr && a.fr <= c.fr) return 1;
        else return 0;
    }
    return 0;
}

vector<pll> f_point() {
    vector<pll> ret;

    ll xlb = -INF, xub = INF;
    ll ylb = -INF, yub = INF;
    for (int i = 1; i <= n; i++) {
        xlb = max(xlb, a[i].x1);
        ylb = max(ylb, a[i].y1);
        xub = min(xub, a[i].x2);
        yub = min(yub, a[i].y2);
    }

    vector<pll> arr = {
        { xlb, ylb },
        { xlb, yub },
        { xub, ylb },
        { xub, yub },
    };

    for (auto& i : arr) {
        bool is_valid = 1;
        for (int j = 1; j <= n; j++) {
            bool bit = 0;
            bit |= (is_contain(i, { a[j].x1, a[j].y1 }, { a[j].x1, a[j].y2 }));
            bit |= (is_contain(i, { a[j].x1, a[j].y2 }, { a[j].x2, a[j].y2 }));
            bit |= (is_contain(i, { a[j].x2, a[j].y2 }, { a[j].x2, a[j].y1 }));
            bit |= (is_contain(i, { a[j].x2, a[j].y1 }, { a[j].x1, a[j].y1 }));
            if (!bit) {
                is_valid = 0;
                break;
            }
        }
        if (is_valid) {
            ret.push_back(i);
        }
    }

    if (xlb > xub || ylb > yub) return {};
    return ret;
}

void solve() {
    {
        auto res = f_line();
        for (auto& i : res) {
            ans.push_back(i);
        }

        res = f_point();
        for (auto& i : res) {
            ans.push_back(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        swap(a[i].x1, a[i].y1);
        swap(a[i].x2, a[i].y2);
    }

    {
        auto res = f_line();
        for (auto& i : res) {
            ans.push_back({ i.sc, i.fr });
        }
    }

    for (int i = 1; i <= n; i++) {
        swap(a[i].x1, a[i].y1);
        swap(a[i].x2, a[i].y2);
    }
}

vector<pll> tr(vector<pll>& arr) {
    vector<pll> ret;
    for (auto& i : arr) {
        if (abs(i.fr + i.sc) & 1) continue;
        if (abs(i.sc - i.fr) & 1) continue;

        ll x = (i.fr + i.sc - 2 * BUF) / 2;
        ll y = (i.sc - i.fr) / 2;
        ret.push_back({ x, y });
    }
    sort(all(ret));
    ret.erase(unique(all(ret)), ret.end());
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    if (!ps.empty()) {
        assert(sz(ps) == 1);
        cout << ps.begin()->fr << ' ' << ps.begin()->sc;
        exit(0);
    }

    if (n == 1) {
        vector<pll> arr;

        for (int x = a[1].x1; x <= a[1].x2; x++) {            
            arr.push_back({ x, a[1].y1 });
            arr.push_back({ x, a[1].y2 });
        }

        for (int y = a[1].y1; y <= a[1].y2; y++) {
            arr.push_back({ a[1].x1, y });
            arr.push_back({ a[1].x2, y });
        }

        arr = tr(arr);
        for (auto& i : arr)
            cout << i.fr << ' ' << i.sc << '\n';

        exit(0);
    }

    solve();

    ans = tr(ans);

    assert(!ans.empty());

    for (auto& i : ans)
        cout << i.fr << ' ' << i.sc << '\n';
}
