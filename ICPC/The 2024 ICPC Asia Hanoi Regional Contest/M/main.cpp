#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int B = 50;

vector<bool> bit(B);

void set_bit() {
    ll x = (ll)rand() * rand();
    for (int b = 0; b < B; b++) {
        bit[b] = ((1ll << b) & x ? 1 : 0);
    }
}

int get_x() {
    int ret; cin >> ret;
    return ret;
}

void set_x(bool x) {
    cout << "> " << x << '\n';
    cout.flush();
}

void answer(int ans) {
    cout << "! " << ans << '\n';
    cout.flush();
}

int main() {
    // #ifndef ONLINE_JUDGE
    // freopen("../input.txt", "r", stdin);
    // freopen("../output.txt", "w", stdout);
    // #endif

    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);

    srand(time(nullptr));

    int tc; cin >> tc;
    while (tc--) {
        set_bit();

        int ans = -1;
        vector<bool> res;
        for (int i = 0; ; i++) {
            int x = get_x();
            res.push_back(x);

            if (B <= sz(res)) {
                bool is_valid = 1;
                for (int j = 0; j < B; j++) {
                    is_valid &= (bit[j] == res[sz(res) - B + j]);
                }
                if (is_valid) { ans = sz(res) - B; break; };
            }

            set_x(bit[i % B]);
        }

        answer(ans);
    }
}
