#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n, psum[32][101010];
ll a[101010];
vector<ll> arr[32];

void init() {
    for (int i = 0; i < 32; i++) {
        memset(psum[i], 0, sizeof(psum[i]));
        memset(a, 0, sizeof(a));
        arr[i].clear();
    }
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        for (int j = 31; j >= 0; j--) {
            if (a[i] & (1 << j)) {
                arr[j].push_back(i);
                psum[j][i]++;
            }
        }
    }
}

void buildPsum() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 31; j++) {
            psum[j][i] += psum[j][i - 1];
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

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        buildPsum();
        
        ll mx = 0;
        for (int v = 1; v <= n; v++)
            mx = max(mx, a[v]);

        ll ans = mx;

        for (int v = 1; v <= n; v++) {
            if (a[v] != mx) continue;

            int l = 1, r = n;
            ll res = mx;

            for (int i = 31; i >= 0; i--) {
                if (mx < (1 << i)) continue;
                if (a[v] & (1 << i)) continue;
                
                auto it = lower_bound(all(arr[i]), v);

                if (it != arr[i].end()) {
                    int idx = *it;
                    if (idx <= r && (psum[i + 1][idx] - psum[i + 1][v - 1]) & 1) {
                        r = idx; res |= (1 << i);
                    }
                }
                if (it != arr[i].begin()) {
                    it--;
                    int idx = *it;
                    if (l <= idx && (psum[i + 1][v] - psum[i + 1][idx - 1]) & 1) {
                        l = idx; res |= (1 << i);
                    }
                }
            }
            cout << l << ' ' << r << '\n';
            ans = max(ans, res);
        }

        cout << ans << '\n';
    }

    return 0;
}