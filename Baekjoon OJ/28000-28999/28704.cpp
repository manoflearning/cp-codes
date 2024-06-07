#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int N = 303030;

int n;
ll a[N], psum[N];
ll ans = 0;

inline ll sum(int l, int r) { return psum[r] - psum[l - 1]; }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n + 1; i++) {
        cin >> a[i];
        psum[i] = a[i] + psum[i - 1];
    }

    vector<int> idx_wo_1;
    idx_wo_1.push_back(0);
    for (int i = 1; i <= n; i++) {
        if (a[i] > 1) idx_wo_1.push_back(i);
    }
    idx_wo_1.push_back(n + 1);

    ans += n;

    for (int i = 1; i + 1 < sz(idx_wo_1); i++) {
        int idx_i = idx_wo_1[i];
        
        ll mul = a[idx_i];
        for (int j = i + 1; j + 1 < sz(idx_wo_1); j++) {
            int idx_j = idx_wo_1[j];

            mul *= a[idx_j];
            if (sum(1, n) < mul) break;

            ll add = sum(idx_i, idx_j);

            ll x = idx_i - idx_wo_1[i - 1] - 1;
            ll y = idx_wo_1[j + 1] - idx_j - 1;

            if (add <= mul && mul <= add + x + y) {
                if (x > y) swap(x, y);

                ll z = mul - add;

                ll k_mn = max(0ll, z - y), k_mx = min(x, z);
                ans += k_mx - k_mn + 1;
            }
        }
    }

    cout << ans;
}