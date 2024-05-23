#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

const string s[] = { "top", "bottom", "left", "right", "pass" };

int R, C, K;
int mny = INF, mxy = -INF, mnx = INF, mxx = -INF;
int t_cnt, b_cnt, l_cnt, r_cnt;

void input() {
    cin >> R >> C >> K;
    for (int i = 0; i < K; i++) {
        int y, x;
        cin >> y >> x;
        mny = min(mny, y);
        mxy = max(mxy, y);
        mnx = min(mnx, x);
        mxx = max(mxx, x);
    }
}

vector<int> grundy;

inline int xor_val() { return grundy[0] ^ grundy[1] ^ grundy[2] ^ grundy[3]; }

pair<int, int> get_idx() {
    int x = xor_val();
    for (int i = 0; i < 4; i++) {
        if ((grundy[i] ^ x) <= grundy[i]) return { i, grundy[i] ^ x };
    }
    return { -1, -1 };
}

void my_turn(pair<int, int> i) {
    if (i.first == 4) cout << s[i.first] << endl;
    else {
        cout << s[i.first] << ' ' << i.second << endl;
        grundy[i.first] -= i.second;
    }
}
void other_turn() {
    string t; cin >> t;
    if (t == "yuck!") exit(0);

    int val; cin >> val;
    for (int i = 0; i < 4; i++) {
        if (t == s[i]) grundy[i] -= val;
    }
}

void solve() {
    // initial choice
    if (xor_val() == 0) my_turn({ 4, -1 });
    else my_turn(get_idx());

    other_turn();

    while (1) {
        my_turn(get_idx());
        other_turn();
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    input();

    grundy.push_back(mny - 1);
    grundy.push_back(R - mxy);
    grundy.push_back(mnx - 1);
    grundy.push_back(C - mxx);

    solve();
}