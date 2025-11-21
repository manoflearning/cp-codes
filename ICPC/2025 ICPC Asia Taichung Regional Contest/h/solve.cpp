#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;

int k, t;
string s;

int get_move(int i, int cnt) {
    while (cnt--) {
        int msb = (i & (1 << (k - 1)) ? 1 : 0);
        i <<= 1;
        i %= (1 << k);
        i |= msb;
    }
    return i;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> k >> t >> s;

    t %= k;

    const int n = (1 << k);

    vector<int> sa(n), r(n);
    for (int i = 0; i < n; i++)
        sa[i] = i, r[i] = s[i];

    vector<int> ord(n), rord(n);
    for (int i = 0; i < n; i++) {
        ord[i] = get_move(i, t);
        rord[ord[i]] = i;
    }

    for (int d = 0; d < k; d++) {
        auto cmp = [&](int i, int j) {
            if (r[i] ^ r[j]) return r[i] < r[j];
            return r[(i + rord[1 << d]) % n] < r[(j + rord[1 << d]) % n];
        };
        sort(all(sa), cmp);

        vector<int> nr(n);
        nr[sa[0]] = 1;
        for (int i = 1; i < n; i++)
            nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        r = nr;
    }

    for (int i = 0; i < n; i++) {
        // cout << sa[i] << '\t';
        string ans(n, ' ');
        for (int j = 0; j < n; j++)
            ans[ord[j]] = s[(sa[i] + j) % n];
        cout << ans;
        // cout << '\n';
        break;
    }
}