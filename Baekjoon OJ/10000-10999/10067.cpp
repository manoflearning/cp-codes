#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;
const int MAXK = 202;

int n, k;
ll a[MAXN], psum[MAXN];
ll dp[2][MAXN];
int opt[MAXK][MAXN];

void f(int x, int l, int r, int nl, int nr) {
    if (l > r) return;
    int mid = (l + r) >> 1;

    ll& ret = dp[x & 1][mid];
    ret = -1;
    for (int i = nl; i <= min(mid - 1, nr); i++) {
        ll res = dp[!(x & 1)][i] + (psum[mid] - psum[i]) * psum[i];
        if (ret <= res) {
            ret = res;
            opt[x][mid] = i;
        }
    }

    f(x, l, mid - 1, nl, opt[x][mid]);
    f(x, mid + 1, r, opt[x][mid], nr);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        psum[i] = a[i] + psum[i - 1];
    }

    for (int i = 1; i <= k; i++) {
        f(i, 1, n, 1, n);
    }

    cout << dp[k & 1][n] << '\n';
    int x = n;
    for (int i = k; i >= 1; i--) {
        assert(opt[i][x] != 0);
        cout << opt[i][x] << ' ';
        x = opt[i][x];
    }
}

// #include <bits/stdc++.h>
// using namespace std;
// #define ll long long

// const int MAXN = 101010;
// const int MAXK = 202;

// struct Line {
//     ll p, q;
//     double s;
//     Line(): Line(1, 0) {}
//     Line(ll sp, ll sq): p(sp), q(sq), s(0) {}
// };
// double cross(const Line& u, const Line& v) {
//     return (double)(v.q - u.q) / (u.p - v.p);
// }

// int n, k;
// ll a[MAXN], psum[MAXN];

// ll dp[2][MAXN];
// int opt[MAXK][MAXN];

// Line ch[MAXN];
// int idx[MAXN];

// void cht(int x) {
//     int top = 1;
//     for (int i = 2; i <= n; i++) {
//         Line g(psum[i - 1], dp[(x - 1) & 1][i - 1] - psum[i - 1] * psum[i - 1]);
//         while (top > 1) {
//             g.s = cross(ch[top - 1], g);
//             if (ch[top - 1].s < g.s) break;
//             --top;
//         }
//         ch[top] = g;
//         idx[top++] = i - 1;

//         int l = 1, r = top - 1;
//         while (l < r) {
//             int mid = (l + r + 1) >> 1;
//             if (psum[i] < ch[mid].s) r = mid - 1;
//             else l = mid;
//         }
//         int fpos = l;
//         dp[x & 1][i] = ch[fpos].p * psum[i] + ch[fpos].q;
//         opt[x][i] = idx[fpos];
//     }
// }

// int main() {
//     #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
//     #endif

//     cin.tie(NULL); cout.tie(NULL);
//     ios_base::sync_with_stdio(false);

//     cin >> n >> k;
//     for (int i = 1; i <= n; i++) {
//         cin >> a[i];
//         psum[i] = a[i] + psum[i - 1];
//     }

//     for (int i = 1; i <= k; i++) cht(i);

//     cout << dp[k & 1][n] << '\n';
//     int x = n;
//     for (int i = k; i >= 1; i--) {
//         cout << opt[i][x] << ' ';
//         x = opt[i][x];
//     }
// }

// // dp[k][i] = max(dp[k - 1][j] + (psum[i] - psum[j]) * psum[j]) (j < i)
