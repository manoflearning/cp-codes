#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 262626;
const ll INF = 1e18;

int n;
ll w[MAXN];
int x[MAXN], y[MAXN];
vector<pair<int, ll>> bydep[33];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
}

void construct_x(int n, int nl, int nr) {
    int mid = (nl + nr) >> 1;
    x[n] = mid;
    if (nl < nr) {
        construct_x(n << 1, nl, mid - 1);
        construct_x(n << 1 | 1, mid + 1, nr);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    construct_x(1, 1, n);

    for (int i = n; i >= 1; i--) {
        if ((i << 1 | 1) <= n) {
            y[i] = y[i << 1 | 1] + 1;
        }
        bydep[y[i]].push_back({ x[i], w[i] });
    }

    ll ans = -INF;
    for (int i = 0; !bydep[i].empty(); i++) {
        for (int j = i; !bydep[j].empty(); j++) {
            vector<pair<int, ll>> arr;
            for (int k = i; k <= j; k++) {
                for (auto& u : bydep[k]) arr.push_back(u);
            }
            sort(arr.begin(), arr.end());

            ll mn = 0;
            vector<ll> psum(sz(arr));
            psum[0] = arr[0].second;
            ans = max(ans, psum[0]);
            for (int i = 1; i < sz(arr); i++) {
                mn = min(mn, psum[i - 1]);
                psum[i] = psum[i - 1] + arr[i].second;
                ans = max(ans, psum[i] - mn);
            }
        }
    }
    
    cout << ans;
}
