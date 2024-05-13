#pragma gcc optimize ("O3")
#pragma gcc optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int B = 59;

int N;
vector<ll> A;

void input() {
    cin >> N;
    A.resize(N);
    for (auto& i : A) cin >> i;
}

inline ll get_p2(ll b) { return 1ll << b; }
int get_msb(ll x) {
    for (int b = B; b >= 0; b--)
        if (get_p2(b) & x) return b;
    return -1;
}

ll naive() { // O(N^2logN)
    set<ll> st;
    st.insert(0);
    for (auto& x : A) {
        vector<ll> lazy_insert;
        for (auto& i : st) lazy_insert.push_back(i ^ x);
        for (auto& i : lazy_insert) st.insert(i);
    }

    auto it = st.end();
    return *(--it);
}

ll solve() {
    unordered_set<ll> st;
    st.insert(0);

    ll ret = 0;

    for (auto& x : A) {
        int msb = get_msb(x);

        vector<ll> lazy_add;
        for (auto& y : st) {
            ll z = x ^ y;

            if ((z | (get_p2(msb + 1) - 1)) > ret && !st.count(z)) lazy_add.push_back(z);

            ret = max(ret, z);
        }

        for (auto& i : lazy_add) {
            if ((i | (get_p2(msb + 1) - 1)) > ret) st.insert(i);
        }

        vector<ll> lazy_del;
        for (auto& y : st) {
            if ((y | (get_p2(msb + 1) - 1)) <= ret) lazy_del.push_back(y);
        }
        for (auto& i : lazy_del) st.erase(i);
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    sort(A.rbegin(), A.rend());

    // cout << naive();

    cout << solve();
}