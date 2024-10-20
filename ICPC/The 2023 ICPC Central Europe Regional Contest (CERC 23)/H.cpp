#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

string bitToString(int bit, int digit) {
    string ret;
    for (int i = 0; i < digit; i++) {
        if (bit & (1 << i)) ret += '1';
        else ret += '0';
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    // cin.tie(NULL); cout.tie(NULL);
    // ios_base::sync_with_stdio(false);

    string op; cin >> op;
    if (op == "ENCODE") {
        string ceo = "*";
        vector<string> managers;
        map<string, vector<string>> tree;

        string s;
        while (cin >> s) {            
            if (s.back() == ':') {
                s.pop_back();
                if (ceo == "*") ceo = s;
                managers.push_back(s);
            }
            else {
                tree[managers.back()].push_back(s);
            }
        }

        int digit = 1;
        for (int ub = 2; ub < sz(managers) + 1; ub <<= 1, digit++);

        int bit = 0;

        vector<string> ans;
        string bits;

        ans.push_back(ceo);
        bits += bitToString(bit++, digit);

        for (auto& i : managers) {
            for (auto& j : tree[i]) {
                ans.push_back(j);
                bits += bitToString(bit, digit);
            }
            bit++;
        }

        for (auto& i : ans) cout << i << '\n';
        cout << bits << '\n';
    }
    if (op == "DECODE") {
        vector<string> a;
        string bits;
        while (1) {
            string s; cin >> s;
            if (s[0] == '0' || s[0] == '1') {
                bits = s;
                break;
            }
            else a.push_back(s);
        }

        map<string, vector<string>> mp;

        int len = sz(bits) / sz(a);
        for (int i = 0; i < sz(a); i++) {
            string bit = bits.substr(i * len, len);
            mp[bit].push_back(a[i]);
        }

        vector<vector<string>> ord;
        for (auto it : mp) {
            if (sz(it.sc) == 1) ord.push_back(it.sc);
        }
        for (auto it : mp) {
            if (sz(it.sc) >= 2) ord.push_back(it.sc);
        }

        for (int i = 0; i + 1 < sz(ord); i++) {
            cout << ord[i][0] << ": ";
            for (auto& j : ord[i + 1]) cout << j << ' ';
            cout << '\n';
        }
    }
}