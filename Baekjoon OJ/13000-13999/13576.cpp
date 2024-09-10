#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

vector<int> buildsa(const string& s) {
    int n = sz(s);
    vector<int> sa(n), r(n + 1), nr(n + 1);
    for (int i = 0; i < n; i++) sa[i] = i, r[i] = s[i];
    for (int d = 1; d < n; d <<= 1) {
        auto cmp = [&](int i, int j) {
            if (r[i] ^ r[j]) return r[i] < r[j];
            return r[i + d] < r[j + d];
        };
        sort(sa.begin(), sa.end(), cmp);
        nr[sa[0]] = 1;
        for (int i = 1; i < n; i++)
            nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        r = nr;
    }
    return sa;
}
vector<int> buildlcp(const string& s, const vector<int>& sa) {
    int n = sz(s);
    vector<int> lcp(n), isa(n);
    for (int i = 0; i < n; i++) isa[sa[i]] = i;
    for (int k = 0, i = 0; i < n; i++) if (isa[i]) {
        for (int j = sa[isa[i] - 1]; s[i + k] == s[j + k]; k++);
        lcp[isa[i]] = (k ? k-- : 0);
    }
    return lcp;
}

int n;
string s;
int prefix_pos = -1;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> s;
    n = sz(s);

    vector<int> sa = buildsa(s);
    vector<int> lcp = buildlcp(s, sa);

    for (int i = 0; i < n; i++) {
        if (sa[i] == 0) { prefix_pos = i; break; }
    }

    vector<int> ls;
    vector<int> ssum(n + 1);

    ssum[n]++;
    int len = n;
    for (int i = prefix_pos - 1; i >= 0; i--) {
        len = min(len, lcp[i + 1]);
        ssum[len]++;
        if (n - sa[i] == len) ls.push_back(n - sa[i]);
    }
    len = n;
    for (int i = prefix_pos + 1; i < n; i++) {
        len = min(len, lcp[i]);
        ssum[len]++;
        if (n - sa[i] == len) ls.push_back(n - sa[i]);
    }
    ls.push_back(n);

    sort(all(ls));

    for (int i = n - 1; i >= 0; i--) {
        ssum[i] += ssum[i + 1];
    }

    cout << sz(ls) << '\n';
    for (auto& i : ls) {
        cout << i << ' ' << ssum[i] << '\n';
    }
}
