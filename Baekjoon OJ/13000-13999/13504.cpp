#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n, psum[32][101010];
ll a[101010];
vector<ll> arr[32];

void init() {

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
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        buildPsum();

        ll ans = 0;
        for (int v = 1; v <= n; v++) {
            for (int i = 31; i >= 0; i--) {
                int idx = lower_bound(all(arr[i]), v) - arr[i].begin();
                if (idx == )
            }
        }
    }

    return 0;
}