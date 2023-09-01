// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

int X;
vector<int> ans;
int K;

void init() {
    ans.clear();
    K = 0;
}

void input() { cin >> X; }

void print() {
    cout << sz(ans) << ' ' << K << '\n';
    for (auto& i : ans) cout << i << ' ';
    cout << '\n';
}

void group2(ll rem) {
    if (rem == 0) return;
    if (rem == 1) {
        K += 1;
        ans.push_back(1);
        return;
    }

    ll tmp = rem;
    vector<ll> p;
    ll sum = 1;
    for (int i = 2; i <= sqrt(tmp); i++) {
        while (tmp % i == 0) {
            tmp /= i;
            p.push_back(i);
            sum += i;
        }
    }
    if (tmp > 1) {
        p.push_back(tmp);
        sum += tmp;
    }

    if (100 < sum) {
        K += 2;
        ans.push_back(1);
        ans.push_back(0);
        ans.push_back(0);
        ans.push_back(0);
        ans.push_back(0);
        ans.push_back(0);
        ans.push_back(0);
        ans.push_back(1);
        group2(rem - 7);
    }
    else {
        K += sz(p) + 1;
        ans.push_back(1);
        for (auto& x : p) {
            for (ll i = 0; i < x - 1; i++) 
                ans.push_back(0);
            ans.push_back(1);
        }
    }
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

        if (X == 0) {
            K = 2;
            ans.push_back(1);
            ans.push_back(0);
        }
        else if (X <= 100) {
            K = 2;
            ans.push_back(1);
            for (int i = 0; i < X - 1; i++) 
                ans.push_back(0);
            ans.push_back(1);
        }
        else if (X <= 100'000) {
            group2(X);
        }
        else {
            K = 2;
            ans.push_back(1);
            ans.push_back(0);
        }

        print();

        cout << flush;
    }
}