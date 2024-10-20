#include <bits/stdc++.h>
using namespace std;

map<string, int> mp1, mp2;
set<string> st;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {
        int s, e; string t;
        
        string tmp; cin >> tmp;
        if (tmp == "------") break;

        s = stoi(tmp);
        cin >> e >> t;
        mp1[t] += e - s;
        st.insert(t);
    }

    while (1) {
        int s, e; string t;
        
        string tmp; cin >> tmp;
        if (tmp == "======") break;

        s = stoi(tmp);
        cin >> e >> t;
        mp2[t] += e - s;
        st.insert(t);
    }

    bool noDiff = 1;
    for (auto& i : st) {
        int res = -mp1[i] + mp2[i];
        if (res == 0) continue;
        noDiff = 0;
        cout << i << ' ' << (res > 0 ? "+" : "") << res << '\n';
    }
    if (noDiff) cout << "No differences found.";
}