#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

int query(int c, int r) {
    cout << "? " << c << ' ' << r << '\n';
    cout.flush();
    int ret; cin >> ret;
    return ret;
}

void answer(int c, int r) {
    cout << "! " << c << ' ' << r << '\n';
    cout.flush();
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    if (n == 1) {
        answer(1, 1);
        exit(0);
    }

    const int sq = (int)sqrt(n);

    const int ans_c = query(n, 1);

    vector<int> f(sq + 1);
    unordered_map<int, int> mp;
    f[0] = ans_c;
    mp[f[0]] = 0;
    for (int i = 1; i <= sq; i++) {
        f[i] = query(i, ans_c);
        mp[f[i]] = i;
        
        if (f[i] == ans_c) {
            const int l = i;
            
            int p = ((l - ans_c) % l + l) % l;
            if (!p) p += l;
            const int ans_r = query(p, ans_c);
            
            answer(ans_c, ans_r);
            exit(0);
        }
    }

    for (int c = sq + 1; ; c += sq) {
        c = min(c, n);

        const int y = query(c, ans_c);
        if (mp.count(y)) {
            const int l = c - mp[y];

            int p = ((l - ans_c) % l + l) % l;
            if (!p) p += l;
            const int ans_r = query(p, ans_c);
            
            answer(ans_c, ans_r);
            exit(0);
        }

        if (c == n) assert(0);
    }
}
