#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n;
multiset<int> st;

vector<int> a;

inline int get_cnt(int x) {
    return st.count(x);
}
inline void add(int x) {
    st.insert(x);
}
inline void del(int x) {
    assert(st.count(x) > 0);
    st.erase(st.find(x));
}

void bt(int i) {
    if (i == n) {
        cout << "Yes\n";
        for (auto &i : a) cout << i << ' ';
        exit(0);
    }

    auto tmp = st;

    set<int> vis;
    int p = a.back();
    for (auto &x : tmp) {
        if (x % p || x / p > 100 || vis.count(x)) continue;
        vis.insert(x);

        int q = x / p;
        if (get_cnt(p * q) == 0) continue;

        a.push_back(q);
        del(p * q);
        
        bt(i + 1);

        a.pop_back();
        add(p * q);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        st.insert(x);
    }

    for (int p = 1; p <= 100; p++) {
        a.push_back(p);
        bt(1);
        a.pop_back();

        // for (int q = 1; q <= 100; q++) {
        //     if (get_cnt(p * q) > 0) {
        //         res.push_back(p);
        //         res.push_back(q);
        //         add(p * q);

        //         bt(2);

        //         res.pop_back();
        //         res.pop_back();
        //         del(p * q);
        //     }
        // }
    }

    cout << "No";
}
