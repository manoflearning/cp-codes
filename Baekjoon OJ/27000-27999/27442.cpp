#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

string S, T[26];
int n, q;
array<ll, 3> qu[101010];
ll ans[101010];
ll psum[101010];

ll pcnt[26][101010];
ll ppcnt[101010];

inline ll get_llen(ll s, ll ss) { return psum[ss - 1] - s + 1; }
inline ll get_rlen(ll e, ll ee) { return e - psum[ee]; }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> S >> n;
    S = "*" + S;
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        cin >> T[c - 'A'];
    }

    for (int i = 1; i < sz(S); i++) {
        psum[i] = sz(T[S[i] - 'A']) + psum[i - 1];
    }

    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> qu[i][0] >> qu[i][1] >> qu[i][2];
    }

    for (int k = 0; k < 26; k++) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < sz(T[i]); j++) {
                pcnt[i][j] = (T[i][j] == ('a' + k)) + (j > 0 ? pcnt[i][j - 1] : 0);
            }
        }

        for (int i = 1; i < sz(S); i++) {
            int idx = S[i] - 'A';
            ppcnt[i] = ppcnt[i - 1] + pcnt[idx][sz(T[idx]) - 1];
        }

        for (int qq = 1; qq <= q; qq++) {
            int op = qu[qq][0];
            if (op == 1) continue;
            ll s = qu[qq][1], e = qu[qq][2];

            if (lower_bound(psum + 1, psum + sz(S), s) == lower_bound(psum + 1, psum + sz(S), e)) {
                int idx = lower_bound(psum + 1, psum + sz(S), e) - psum;
                s -= psum[idx - 1], e -= psum[idx - 1];
                s--, e--;

                idx = S[idx] - 'A';
                auto res = pcnt[idx][e];
                if (s > 0) res = res - pcnt[idx][s - 1];
                ans[qq] = max(ans[qq], res);
            } else {
                int ss = lower_bound(psum + 1, psum + sz(S), s) - psum;
                int ee = upper_bound(psum + 1, psum + sz(S), e) - psum;
                if (psum[ss - 1] + 1 < s) ss++;
                ee--;

                auto res = ppcnt[ee] - ppcnt[ss - 1];
                int llen = get_llen(s, ss), rlen = get_rlen(e, ee);
                if (llen > 0) {
                    int idx = S[ss - 1] - 'A';
                    res = res + (pcnt[idx][sz(T[idx]) - 1] - pcnt[idx][sz(T[idx]) - 1 - llen]);
                }
                if (rlen > 0) res += pcnt[S[ee + 1] - 'A'][rlen - 1];

                ans[qq] = max(ans[qq], res);
            }
        }
    }

    for (int qq = 1; qq <= q; qq++) {
        int op = qu[qq][0];
        ll s = qu[qq][1], e = qu[qq][2];

        if (lower_bound(psum + 1, psum + sz(S), s) == lower_bound(psum + 1, psum + sz(S), e)) {
            int idx = lower_bound(psum + 1, psum + sz(S), e) - psum;
            s -= psum[idx - 1], e -= psum[idx - 1];
            s--, e--;

            idx = S[idx] - 'A';
            if (op == 1) {
                for (int i = s; i <= e; i++)
                    cout << T[idx][i];
                cout << '\n';
            }
            if (op == 2) cout << ans[qq] << '\n';

            continue;
        }

        int ss = lower_bound(psum + 1, psum + sz(S), s) - psum;
        int ee = upper_bound(psum + 1, psum + sz(S), e) - psum;
        if (psum[ss - 1] + 1 < s) ss++;
        ee--;

        if (op == 1) {
            int llen = get_llen(s, ss), rlen = get_rlen(e, ee);
            for (int i = sz(T[S[ss - 1] - 'A']) - llen; i < sz(T[S[ss - 1] - 'A']); i++) {
                cout << T[S[ss - 1] - 'A'][i];
            }
            for (int i = ss; i <= ee; i++) cout << T[S[i] - 'A'];
            for (int i = 0; i < rlen; i++) cout << T[S[ee + 1] - 'A'][i];
            cout << '\n';
        }
        if (op == 2) cout << ans[qq] << '\n';
    }
}
