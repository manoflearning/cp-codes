#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 1010101;

void solve_small(int n, int k, vector<int> &ans) {
    unordered_set<int> vis;
    for (int x = 1; x <= n; x++) {
        if (x == k) continue;

        if (vis.count(x)) continue;

        if (x < k) {
            int val = -1;
            for (int xx = x; xx >= 1; xx--) {
                if (vis.count(k - xx)) continue;
                val = xx;
                break;
            }
            assert(val != -1);

            vector<int> lazy_add;
            ans.push_back(val);
            lazy_add.push_back(val);
            for (int y : vis) {
                if (val + y <= n) {
                    lazy_add.push_back(val + y);
                }
            }
            for (auto &i : lazy_add) {
                vis.insert(i);
            }
        } else {
            vector<int> lazy_add;
            ans.push_back(x);
            lazy_add.push_back(x);
            for (int y : vis) {
                if (x + y <= n) {
                    lazy_add.push_back(x + y);
                }
            }
            for (auto &i : lazy_add) {
                vis.insert(i);
            }
        }
    }
}

bitset<N> vis;

void solve_large(int n, int k, vector<int> &ans) {
    vis.reset();

    vis[0] = 1;
    for (int x = 1; x <= n; x++) {
        if (vis[x]) continue;

        if (x == k) continue;

        if (x < k) {
            int val = -1;
            for (int xx = x; xx >= 1; xx--) {
                if (vis[k - xx]) continue;
                val = xx;
                break;
            }
            assert(val != -1);

            ans.push_back(val);
            vis |= (vis << val);
        } else {
            ans.push_back(x);
            vis |= (vis << x);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int tc; cin >> tc;
    while (tc--) {
        int n, k;
        cin >> n >> k;

        vector<int> ans;

        if (n <= (int)1e5) {
            solve_small(n, k, ans);
            // solve_large(n, k, ans);
        } else {
            solve_large(n, k, ans);
        }
        
        sort(all(ans));
        
        cout << sz(ans) << '\n';
        for (auto &i : ans) cout << i << ' ';
        cout << '\n';
    }
}
