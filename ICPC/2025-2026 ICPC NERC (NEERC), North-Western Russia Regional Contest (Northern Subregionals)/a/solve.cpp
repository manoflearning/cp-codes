#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 2020;
constexpr int V = 505;

struct instruction {
    bool add;
    int v;
    bool async;
};

int n;
instruction a[N];
bitset<N * V> ans;
int ssum[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int last_assign_idx = 0;
    set<int> async_assigns;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        char op; string s;
        cin >> op >> a[i].v >> s;
        a[i].add = (op == '+');
        a[i].async = (s == "async");

        if (!a[i].add) {
            last_assign_idx = i;
            if (a[i].async) {
                async_assigns.insert(a[i].v);
            }
        }
    }

    if (!last_assign_idx) {
        cout << 1;
        exit(0);
    }

    for (int i = n; i > last_assign_idx; i--) {
        ssum[i] = a[i].v + ssum[i + 1];
    }

    bitset<N * V> res{}, dp1{};//, base{};

    // base case (knapsack 1)
    // for (int x : async_assigns) {
    //     base[x] = 1;
    // }

    // inductive step (knapsack 1)
    for (int i = 1; i < last_assign_idx; i++) {
        if (a[i].add && a[i].async) {
            int x = a[i].v;
            dp1 |= (dp1 << x);
            dp1[x] = 1;
        }
    }
    for (int x : async_assigns) {
        res |= (dp1 << x);
        res[x] = 1;
    }

    ans |= (res << ssum[last_assign_idx + 1]);
    if (!a[last_assign_idx].async) {
        ans |= (dp1 << (a[last_assign_idx].v + ssum[last_assign_idx + 1]));
        ans[a[last_assign_idx].v + ssum[last_assign_idx + 1]] = 1;
    }
    
    // base case (knapsack 2)
    for (int i = last_assign_idx + 1; i <= n; i++) {
        if (a[i].async) {
            res |= (res << a[i].v);
            // res[a[i].v] = 1;
        }

        ans |= (res << ssum[i + 1]);
    }

    // for (int i = 0; i < 20; i++) {
    //     cout << ans[i];
    // }
    // cout << '\n';

    cout << ans.count();
}