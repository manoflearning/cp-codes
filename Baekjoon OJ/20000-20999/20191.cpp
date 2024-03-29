#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

string a, b;

bool imp() {
    set<char> s;
    for (auto& i : b) s.insert(i);
    for (auto& i : a) 
        if (!s.count(i)) return 1;
    return 0;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> a >> b;
    if (imp()) {
        cout << -1;
        return 0;
    }

    vector<int> idx[26];
    for (int i = 0; i < sz(b); i++) {
        idx[b[i] - 'a'].push_back(i);
    }

    int now = idx[a[0] - 'a'].front(), ans = 1;
    for (int i = 1; i < sz(a); i++) {
        auto it = upper_bound(all(idx[a[i] - 'a']), now);
        if (it == idx[a[i] - 'a'].end()) {
            now = idx[a[i] - 'a'].front();
            ans++;
        }
        else now = *it;
    }

    cout << ans;
}