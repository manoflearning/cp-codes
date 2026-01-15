#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    set<pii> st;
    unordered_map<int, Tree<int>> mp;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        mp[ai].insert(i);
        st.insert({i, ai});
    }

    int q; cin >> q;
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;

        if (op == 1) {
            int k; cin >> k;

            auto &tree = mp[k];

            int res = 0;
            res += tree.order_of_key(r + 1);
            res -= tree.order_of_key(l);

            cout << res << '\n';
        } else {
            auto it = st.lower_bound({l, 0});

            vector<pii> dels;
            while (it != st.end() && it->first <= r) {
                dels.push_back(*(it++));
            }

            for (auto &i : dels) {
                st.erase(i);
                mp[i.second].erase(i.first);
            }
        }
    }
}
