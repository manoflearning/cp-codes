#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;

int n, x;
ll k;
ll a[MAXN], b[MAXN];

void input() {
    cin >> n >> k >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
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

    int l = 0, r = 1e6;
    while (l < r) {
        int mid = (l + r) >> 1;

        vector<ll> costs;
        for (int i = 1; i <= n; i++) {
            if (a[i] > mid) {
                ll cost = (a[i] - mid) * b[i];
                costs.push_back(cost);
            }
        }

        sort(all(costs));

        ll sum = 0;
        for (int i = 0; i + x - 1 < sz(costs); i++) {
            sum += costs[i];
        }

        if (sum >= k) l = mid + 1;
        else r = mid;
    }

    cout << l;
}
