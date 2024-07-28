#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 10101, C = 50505;
const int INF = 1e9 + 7;

int n, c;
struct Child {
    int bit_x, bit_y;
};
vector<Child> chds[N];

void input() {
    cin >> n >> c;
    for (int i = 0; i < c; i++) {
        int e, f, l;
        cin >> e >> f >> l;
        int bit_x = 0, bit_y = 0;
        while (f--) {
            int x; cin >> x;
            if (x < e) x += n;
            if (e <= x && x <= e + 4) bit_x |= 1 << (x - e);
        }
        while (l--) {
            int y; cin >> y;
            if (y < e) y += n;
            if (e <= y && y <= e + 4) bit_y |= 1 << (y - e);
        }
        chds[e].push_back({ bit_x, bit_y });
    }
}

int dp[N][32];

int bottomup(int bit_init) {
    int ret = 0;

    // initialize
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 32; j++) {
            dp[i][j] = -INF;
        }
    }

    // base case
    dp[5][bit_init] = 0;

    // inductive step
    for (int i = 5; i <= n + 4; i++) {
        for (auto& chd : chds[i - 4]) {
            int bit_x = chd.bit_x, bit_y = chd.bit_y;

            for (int bit = 0; bit < 32; bit++) {
                if (i <= 9) {
                    int rcnt = (i - 5);
                    int lcnt = 5 - rcnt;
                    if ((bit_init >> rcnt) ^ (bit % (1 << lcnt))) continue;
                }
                if (i > n) {
                    int lcnt = 5 - (i - n);
                    int rcnt = 5 - lcnt;
                    if ((bit >> lcnt) ^ (bit_init % (1 << rcnt))) continue;
                }

                int is_chd_happy = 0;
                is_chd_happy |= (bit_x & bit);
                is_chd_happy |= (bit_y - (bit_y & bit));

                if (is_chd_happy) dp[i][bit]++;

                ret = max(ret, dp[i][bit]);
                assert(dp[i][bit] >= 0);
            }
        }

        for (int bit = 0; bit < 32; bit++) {
            if (i <= 9) {
                int rcnt = (i - 5);
                int lcnt = 5 - rcnt;
                if ((bit_init >> rcnt) ^ (bit % (1 << lcnt))) continue;
            }
            if (i > n) {
                int lcnt = 5 - (i - n);
                int rcnt = 5 - lcnt;
                if ((bit >> lcnt) ^ (bit_init % (1 << rcnt))) continue;
            }

            dp[i + 1][bit >> 1] = max(dp[i + 1][bit >> 1], dp[i][bit]);
            dp[i + 1][bit >> 1 | (1 << 4)] = max(dp[i + 1][bit >> 1 | (1 << 4)], dp[i][bit]);
        }
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    int ans = 0;
    for (int b = 0; b < 32; b++) {
        ans = max(ans, bottomup(b));
    }
    cout << ans;
}