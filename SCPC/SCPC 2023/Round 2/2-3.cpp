#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define fr first
#define sc second

const int MAXN = 1010101;

int n;
string s;

void init() {}

void input() { cin >> n >> s; }

int cnt[2 * MAXN];
int stk[MAXN], pos[MAXN];
int po = 0;
ll group3() {
    // solve
    ll ret = 0;

    int sum = MAXN;
    cnt[sum]++;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(' || s[i] == '{') {
            stk[po] = i;
            pos[po] = sum;
            po++;
            sum++;
        }
        else {
            ret += (ll)cnt[sum] * (cnt[sum] - 1) / 2;
            cnt[sum] = 0;
            sum--;
            if (po == 0 || abs(s[i] - s[stk[po - 1]]) > 2) {
                for (int i = 0; i < po; i++) {
                    ret += (ll)cnt[pos[i]] * (cnt[pos[i]] - 1) / 2;
                    cnt[pos[i]] = 0;
                }
                po = 0;
            }
            else po--;
        }
        cnt[sum]++;
    }
    
    for (int i = 0; i < po; i++) {
        ret += (ll)cnt[pos[i]] * (cnt[pos[i]] - 1) / 2;
        cnt[pos[i]] = 0;
    }
    po = 0;
    ret += (ll)cnt[sum] * (cnt[sum] - 1) / 2;
    cnt[sum] = 0;

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        cout << group3() << '\n';

        cout << flush;
    }
}