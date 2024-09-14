#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

vector<ll> x;
vector<int> a;
unordered_set<ll> st, ans;
vector<pair<ll, int>> mp;

void inserts(int i, ll x) {
    if (i == mp.size()) {
        ans.insert(x);
        return;
    }

    for (int j = 0; j <= mp[i].second; j++) {
        inserts(i + 1, x);
        x *= mp[i].first;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int n; cin >> n;
    x.resize(n);
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> a[i];
    }

    // case 1
    {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (a[i] == a[j]) continue;
                st.insert(abs(x[i] - x[j]));
            }
        }

        for (ll l : st) {
            mp.clear();
            for (ll p = 2; p * p <= l; p++) {
                while (l % p == 0) {
                    if (mp.empty() || mp.back().first != p) mp.push_back({ p, 0 });
                    mp.back().second++;
                    l /= p;
                }
            }
            if (l > 0) mp.push_back({ l, 1 });
            inserts(0, 1);
        }
    }
    // case 2
    {
        
    }

    ll sum = 0;
    for (auto& i : ans) sum += i;
    cout << sz(ans) << ' ' << sum;
}
