#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

bool valid(const vector<int> &b, const vector<int> &ans2) {
    int st = 0;
    for (int l : ans2) {
        if (l & 1) return 0;
        for (int i = st; i < st + l / 2; i++) {
            if (b[i] != b[i + l / 2]) return 0;
        }
        st += l;
    }
    if (st != sz(b)) return 0;
    return 1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        bool yes = 1;

        unordered_map<int, int> mp;
        for (auto &i : a) mp[i]++;
        for (auto &[_, v] : mp) yes &= !(v & 1);
        if (!yes) {
            cout << -1 << '\n';
            continue;
        }

        vector<int> b{a};

        vector<pii> ans1;
        vector<int> ans2;

        int st = 0;
        while (st < sz(b)) { // time: O(n^2)
            int i;
            for (i = st + 1; i < sz(b); i++) { // time: O(n)
                if (b[st] == b[i]) break;
            }
            assert(i < sz(b));

            vector<int> stk;
            while (sz(b) > i + 1) { // time: O(n)
                stk.push_back(b.back());
                b.pop_back();
            }

            for (int j = st + 1; j < i; j++) { // time: O(n)
                ans1.push_back({j - st + i - 1, b[j]});
                b.push_back(b[j]);
            }
            for (int j = i - 1; j > st; j--) b.push_back(b[j]);

            while (!stk.empty()) { // time: O(n)
                b.push_back(stk.back());
                stk.pop_back();
            }

            ans2.push_back(2 * (i - st));
            st += ans2.back();
        }

        cout << sz(ans1) << '\n';
        for (auto &i : ans1) cout << i.first + 1 << ' ' << i.second << '\n';
        cout << sz(ans2) << '\n';
        for (auto &i : ans2) cout << i << ' ';
        cout << '\n';
        
        // DEBUG
        // for (auto &i : b) cout << i << ' ';
        // cout << "\n\n";
        // cout.flush();
        // assert(sz(ans1) <= 2 * n * n);
        // assert(valid(b, ans2));
    }
}
