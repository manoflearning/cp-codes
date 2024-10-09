#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
vector<string> a;
int m;
vector<string> b;

string query(const string& s, const string& t) {
    string ret;
    vector<int> vis(26);
    for (auto& c : s) vis[c - 'a']++;
    for (int i = 0; i < 5; i++) {
        if (s[i] == t[i]) ret.push_back('*');
        else if (vis[t[i] - 'a']) ret.push_back('!');
        else ret.push_back('X');
    }
    return ret;
}

int main(){
    cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    cin >> m;
    b.resize(m);
    for (auto& i : b) cin >> i;

    int sec = -1;
    for (int i = 0; i < n; i++) {
        set<string> st;
        for (int j = 0; j < n; j++) {
            string res = query(a[i], a[j]);
            st.insert(res);
        }

        bool yes = 1;
        for (auto& i : b) {
            if (!st.count(i)) { yes = 0; break; }
        }

        if (yes) { sec = i; break; }
    }

    assert(sec != -1);

    map<string, ll> mp;
    for (int j = 0; j < n; j++) {
        string res = query(a[sec], a[j]);
        mp[res]++;
    }

    for (auto& i : b) {
        cout << mp[i] << '\n';
    }
}
