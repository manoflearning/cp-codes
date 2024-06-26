#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

const ll INF = 1e18;

vector<ll> uf(50505, -1);
ll find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int x, int y) {
    ll X = find(x), Y = find(y);
    if (X == Y) return;
    uf[X] += uf[Y];
    uf[Y] = X;
}

int n;
struct Node {
    ll x, y, w, h;
};
Node a[50505];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].w >> a[i].h;
        uf[i] = -(a[i].w * a[i].h);
    }
}

map<ll, vector<pair<pll, int>>> mp;

void solve() {
    for (auto& it : mp) {
        vector<pair<pll, int>> arr = it.sc;
        sort(arr.begin(), arr.end());

        int st = 0;
        for (int i = 0; i < arr.size(); i++) {
            pair<pll, int> du = { { arr[i].fr.sc + 1, -INF }, -1 };
            int j = lower_bound(arr.begin(), arr.end(), du) - arr.begin();
            for (int k = max(st, i + 1); k < j; k++) {
                merge(arr[i].sc, arr[k].sc);
            }
            st = j;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int i = 1; i <= n; i++) {
        mp[a[i].y].push_back({ { a[i].x, a[i].x + a[i].w }, i });
        mp[a[i].y + a[i].h].push_back({ { a[i].x, a[i].x + a[i].w }, i });
    }

    solve();

    mp.clear();
    for (int i = 1; i <= n; i++) {
        mp[a[i].x].push_back({ { a[i].y, a[i].y + a[i].h }, i });
        mp[a[i].x + a[i].w].push_back({ { a[i].y, a[i].y + a[i].h }, i });
    }

    solve();

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, -uf[find(i)]);
    }

    cout << ans;
}