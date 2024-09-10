#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

ll n;
vector<pll> arr;
unordered_map<ll, ll> idx;
unordered_map<ll, ll> idx_rev;
vector<ll> ord;

void init() {
    arr.clear();
    idx.clear();
    idx_rev.clear();
    ord.clear();
}

void get_order() {
    set<ll> vis;

    priority_queue<ll> pq;
    pq.push(n);
    vis.insert(n);

    while (!pq.empty()) {
        ll v = pq.top();
        pq.pop();

        if (v <= 0) break;

        ord.push_back(v);

        if (v & 1) {
            if (!vis.count(v / 2)) {
                vis.insert(v / 2);
                pq.push(v / 2);
            }
            if (!vis.count(v / 2 + 1)) {
                vis.insert(v / 2 + 1);
                pq.push(v / 2 + 1);
            }
        }
        else {
            if (!vis.count(v / 2)) {
                vis.insert(v / 2);
                pq.push(v / 2);
            }
        }
    }

    reverse(all(ord));
}

void solve() {
    idx[0] = -1;
    for (auto x : ord) {
        if (x == 1) {
            idx_rev[-1] = 0;
            idx[x] = sz(arr);
            idx_rev[sz(arr)] = x;
            arr.push_back({ -1, -1 });
        } else if (x & 1) {
            idx[x] = sz(arr);
            idx_rev[sz(arr)] = x;
            arr.push_back({ idx[x / 2 + 1], idx[x / 2] });
        } else {
            idx[x] = sz(arr);
            idx_rev[sz(arr)] = x;
            arr.push_back({ idx[x / 2], idx[x / 2] });
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
    // for (n = 1e18; n >= 1e18 - 1e4; n--) {
        init();

        cin >> n;

        get_order();

        solve();

        assert(sz(arr) <= 125);

        cout << sz(arr) << '\n';
        for (int i = 0; i < sz(arr); i++) {
            assert(-1 <= arr[i].fr && arr[i].fr <= i - 1);
            assert(-1 <= arr[i].sc && arr[i].sc <= i - 1);
            assert(i == 0 || idx_rev[arr[i].fr] + idx_rev[arr[i].sc] == idx_rev[i]);
            cout << arr[i].fr << ' ' << arr[i].sc << '\n';
        }
        cout << sz(arr) - 1 << '\n';
    }
}
