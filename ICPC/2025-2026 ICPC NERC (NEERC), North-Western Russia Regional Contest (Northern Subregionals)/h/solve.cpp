#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

ll pow2[60];
vector<ll> ans;

bool f(ll h, int sp) {
    if (h == 0) return 1;

    int k{};
    for (k = 2; (k - 2) * pow2[k] <= h; k++);
    k--;

    // cout << "k = " << k << ", h = " << h << ", sp = " << sp << '\n';

    if (k == 2) {
        if (h == 4) {
            if (sp >= 2) {
                ans.push_back(pow2[k]);
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    if (h < (k - 1) * pow2[k]) {
        if (k - 1 > sp) return 0;
        ans.push_back(pow2[k]);
        return 1;
    }/* else if (h == (k - 1) * pow2[k]) {
        if (k > sp) return 0;
        ans.push_back(pow2[k]);
        return 1;
    } */else {
        if (k <= sp) {
            ans.push_back(pow2[k]);
            return f(h - (k - 1) * pow2[k], sp - 1);
        } else if (k - 1 <= sp) {
            ans.push_back(pow2[k]);
            return f(h - (k - 1) * pow2[k] + 4, sp - 1);
        } else {
            return 0;
        }        
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    pow2[0] = 1;
    for (int i = 1; i < 60; i++) {
        pow2[i] = 2 * pow2[i - 1];
    }

    int n, sp;
    cin >> n >> sp;
    while (n--) {
        ll h; cin >> h;

        if (h % 4) {
            cout << -1 << '\n';
            continue;
        }

        ans.clear();
        if (f(h, sp)) {
            cout << sz(ans) << ' ';
            for (auto &i : ans) cout << i << ' ';
            cout << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
}

// if answer is {2^k}, (k-2) * 2^k <= h <= (k-1) * 2^k.
// - if h = (k-2) * 2^k => need (k - 2) space
