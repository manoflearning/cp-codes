#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

string s;
ll n;

string t;
set<string> st;

void bt() {
    if (sz(t)) st.insert(t);
    if (sz(t) == 5) return;

    for (int i = (t.empty() ? 1 : 0); i < 10; i++) {
        t.push_back(i + '0');
        bt();
        t.pop_back();
    }
}

ll ans = 0;
void solve() {
    for (auto i : st) {
        string j = i;
        reverse(j.begin(), j.end());

        string k = i + j;
        ll res = stol(k);
        if (n >= res) ans++;

        for (int x = 0; x < 10; x++) {
            string tmp(1, x + '0');
            k = i + tmp + j;
            res = stol(k);
            if (n >= res) ans++;
        }
    }

    for (int x = 1; x < 10; x++) {
        string tmp(1, x + '0');
        ll res = stol(tmp);
        if (n >= res) ans++;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> s;
    n = stol(s);

    bt();

    solve();
    
    cout << ans;
}