#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
// 확장 가능 판별은 딱 한 개의 문자를 추가하는 것으로 충분하다.
#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

string X, Y, W;
vector<int> dpx, rdpx;
vector<int> dpy, rdpy;

void init() {
    dpx.clear();
    rdpx.clear();
    dpy.clear();
    rdpy.clear();
}

void input() { cin >> X >> Y >> W; }

void bottomup(vector<int>& dp, vector<int>& rdp, const string& S) {
    dp.resize(sz(S));
    rdp.resize(sz(S));
    
    dp[0] = 0;
    for (int i = 1; i < sz(dp); i++) {
        if (dp[i - 1] == sz(W)) dp[i] = sz(W);
        else {
            char c = W[dp[i - 1]];
            dp[i] = dp[i - 1];
            if (c == S[i - 1]) dp[i]++;
        }
    }
    
    rdp[sz(S) - 1] = 0;
    for (int i = sz(rdp) - 2; i >= 0; i--) {
        if (rdp[i + 1] == sz(W)) rdp[i] = sz(W);
        else {
            char c = W[sz(W) - rdp[i + 1] - 1];
            rdp[i] = rdp[i + 1];
            if (c == S[i + 1]) rdp[i]++;
        }
    }
}

void pre() {
    bottomup(dpx, rdpx, X);
    bottomup(dpy, rdpy, Y);
}

int cutting1() {
    vector<int> cntx(26), cnty(26);
    for (auto& c : X) cntx[c - 'a']++;
    for (auto& c : Y) cnty[c - 'a']++;
    for (auto& c : W) cntx[c - 'a']--, cnty[c - 'a']--;
    
    int rem = 0;
    for (int i = 0; i < 26; i++) rem += min(cntx[i], cnty[i]);

    return (rem == 0 ? 1 : 0);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        if (cutting1()) {
            cout << 0 << '\n';
            continue;
        }

        if (sz(X) == sz(W) || sz(Y) == sz(W)) {
            cout << 0 << '\n';
            continue;
        }

        pre();

        vector<vector<int>> px(26, vector<int>(sz(W) + 1, -INF));
        vector<vector<int>> py(26, vector<int>(sz(W) + 1, -INF));
        for (int i = 0; i < sz(X); i++) {
            px[X[i] - 'a'][dpx[i]] = max(px[X[i] - 'a'][dpx[i]], rdpx[i]);
        }
        for (int i = 0; i < sz(Y); i++) {
            py[Y[i] - 'a'][dpy[i]] = max(py[Y[i] - 'a'][dpy[i]], rdpy[i]);
        }
        for (int j = sz(W) - 1; j >= 0; j--) {
            for (int i = 0; i < 26; i++) {
                px[i][j] = max(px[i][j], px[i][j + 1]);
                py[i][j] = max(py[i][j], py[i][j + 1]);
            }
        }

        int ans = 0;
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j <= sz(W); j++) {
                if (j + min(px[i][j], py[i][j]) >= sz(W)) {
                    ans = 1;
                    //cout << (char)(i + 'a') << ' ' << j << ' ' << px[i][j] << ' ' << py[i][j] << '\n';
                }
            }
        }

        cout << ans << '\n';
    }
}