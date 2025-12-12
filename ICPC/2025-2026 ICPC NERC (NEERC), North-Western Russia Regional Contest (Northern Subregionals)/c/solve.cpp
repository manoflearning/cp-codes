#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    ll n; cin >> n;

    constexpr ll MASK = (1 << 7) - 1;

    vector<int> ans;
    for (int i = 0; i < 5; i++) {
        ll val = (n & (MASK << (i * 7))) >> (i * 7);
        ans.push_back(val | (1 << 7));
    }
    while (sz(ans) >= 2 && ans.back() == (1 << 7)) ans.pop_back();
    ans.front() ^= (1 << 7);

    reverse(all(ans));

    for (auto &i : ans)
        cout << i << ' ';
}