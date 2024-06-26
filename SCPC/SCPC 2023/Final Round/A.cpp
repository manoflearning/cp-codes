// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

int n;
vector<int> a;

void init() {}

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        ll sum = 0;
        for (auto& i : a) sum += i;

        int b1 = sum & 1, b2 = n & 1;

        if (b1 == b2) cout << "1st\n";
        else cout << "2nd\n";

        cout << flush;
    }
}