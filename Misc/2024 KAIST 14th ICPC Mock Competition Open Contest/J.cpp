#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n;
vector<pll> a;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

void init() {}

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.fr >> i.sc;
        if (i.fr > 0) i.fr = 1;
        else if (i.fr < 0) i.fr = -1;
        if (i.sc > 0) i.sc = 1;
        else if (i.sc < 0) i.sc = -1;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        map<pll, int> mp;
        for (auto& i : a) {
            mp[i]++;
        }

        set<pll> ans;
        for (auto& i : mp) {
            if (i.fr == pll(0, 0)) continue;
            else if (i.fr.fr == 0 || i.fr.sc == 0) ans.insert(i.fr);
        }

        int cnt = 0;
        for (auto& i : mp) {
            if (i.fr.fr != 0 && i.fr.sc != 0) {
                if (i.fr == pll(1, 1)) {
                    if (i.sc >= 2) {
                        ans.insert({ 0, 1 });
                        ans.insert({ 1, 0 });
                    } else {
                        ans.insert({ 0, 1 });
                            ans.insert({ 1, 0 });
                        // if (ans.count({ 0, 1 }) || ans.count({ 1, 0 })) {
                        //     ans.insert({ 0, 1 });
                        //     ans.insert({ 1, 0 });
                        // } else {
                        //     ans.insert({ 1, 1 });
                        // }
                    }
                }
                if (i.fr == pll(1, -1)) {
                    if (i.sc >= 2) {
                        ans.insert({ 0, -1 });
                        ans.insert({ 1, 0 });
                    } else {
                        ans.insert({ 0, -1 });
                            ans.insert({ 1, 0 });
                        // if (ans.count({ 0, -1 }) || ans.count({ 1, 0 })) {
                        //     ans.insert({ 0, -1 });
                        //     ans.insert({ 1, 0 });
                        // } else {
                        //     ans.insert({ 1, -1 });
                        // }
                    }
                }
                if (i.fr == pll(-1, 1)) {
                    if (i.sc >= 2) {
                        ans.insert({ 0, 1 });
                        ans.insert({ -1, 0 });
                    } else {
                        ans.insert({ 0, 1 });
                            ans.insert({ -1, 0 });
                        // if (ans.count({ 0, 1 }) || ans.count({ -1, 0 })) {
                        //     ans.insert({ 0, 1 });
                        //     ans.insert({ -1, 0 });
                        // } else {
                        //     ans.insert({ -1, 1 });
                        // }
                    }
                }
                if (i.fr == pll(-1, -1)) {
                    if (i.sc >= 2) {
                        ans.insert({ 0, -1 });
                        ans.insert({ -1, 0 });
                    } else {
                        ans.insert({ 0, -1 });
                        ans.insert({ -1, 0 });
                        // if (ans.count({ 0, -1 }) || ans.count({ -1, 0 })) {
                        //     ans.insert({ 0, -1 });
                        //     ans.insert({ -1, 0 });
                        // } else {
                        //     ans.insert({ -1, -1 });
                        // }
                    }
                }
            }
        }

        cout << sz(ans) << '\n';
        for (auto& i : ans)
            cout << i.fr << ' ' << i.sc << '\n';
    }
}
