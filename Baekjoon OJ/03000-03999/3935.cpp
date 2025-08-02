#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 365;
const int NUM_CELL = 16;

const vector<vector<int>> IDXS = {
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9, 10, 11},
    {12, 13, 14, 15}
};
const vector<vector<int>> RIDXS = {
    {0, 0},
    {0, 1},
    {0, 2},
    {0, 3},
    {1, 0},
    {1, 1},
    {1, 2},
    {1, 3},
    {2, 0},
    {2, 1},
    {2, 2},
    {2, 3},
    {3, 0},
    {3, 1},
    {3, 2},
    {3, 3}
};

const int Y[] = {-1, 0, 0, 0, 1, 1, 1, 2, 2, 2};
const int X[] = {-1, 0, 1, 2, 0, 1, 2, 0, 1, 2};

const int POW10[] = {1, 10, 100, 1'000, 10'000, 100'000, 1'000'000, 10'000'000};

int n;
int a[N][NUM_CELL];
vector<vector<bool>> dp;

void init() {
    dp.clear();
}

void input() {
    cin >> n;
    if (!n) exit(0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < NUM_CELL; j++) {
            cin >> a[i][j];
        }
    }

    dp.resize(n, vector<bool>(POW10[6]));
}

bool is_valid(int i, int bit) {
    int now = bit % POW10[1];

    if (a[i][IDXS[Y[now]][X[now]]]) return 0;
    if (a[i][IDXS[Y[now] + 1][X[now]]]) return 0;
    if (a[i][IDXS[Y[now]][X[now] + 1]]) return 0;
    if (a[i][IDXS[Y[now] + 1][X[now] + 1]]) return 0;

    return 1;
}

void bottomup() {
    set<int> bits;
    // base case
    if (is_valid(0, 5)) {
        dp[0][5] = 1;
        bits.insert(5);
    }

    // inductive step
    for (int i = 0; i + 1 < n; i++) {
        set<int> nbits;
        for (int bit : bits) {
            int vis = 0;
            for (int j = 0; j < 6; j++) {
                int pos = bit % POW10[j + 1] / POW10[j];
                if (pos == 0) continue;
                vis |= (1 << IDXS[Y[pos]][X[pos]]);
                vis |= (1 << IDXS[Y[pos] + 1][X[pos]]);
                vis |= (1 << IDXS[Y[pos]][X[pos] + 1]);
                vis |= (1 << IDXS[Y[pos] + 1][X[pos] + 1]);
            }

            vector<int> to_go;
            for (int j = 0; j < 16; j++) {
                if (!(vis & (1 << j))) to_go.push_back(j);
            }

            int now = bit % POW10[1];
            for (int nxt = 1; nxt < 10; nxt++) {
                if (Y[now] != Y[nxt] && X[now] != X[nxt]) continue;

                int nbit = bit * 10 % POW10[6] + nxt;
                if (!is_valid(i + 1, nbit)) continue;

                if (i + 1 >= 6) {
                    bool fuck = 1;
                    int yy = Y[nxt], xx = X[nxt];
                    for (auto &j : to_go) {
                        auto ny = RIDXS[j][0], nx = RIDXS[j][1];
                        fuck &= (yy <= ny && ny <= yy + 1);
                        fuck &= (xx <= nx && nx <= xx + 1);
                    }
                    if (!fuck) continue;
                }

                dp[i + 1][nbit] = 1;
                nbits.insert(nbit);
            }
        }
        bits = nbits;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {
        init();

        input();

        bottomup();

        bool ans = 0;
        for (int bit = 0; bit < POW10[6]; bit++) {
            ans |= dp[n - 1][bit];
        }

        cout << (ans ? 1 : 0) << '\n';
    }
}
