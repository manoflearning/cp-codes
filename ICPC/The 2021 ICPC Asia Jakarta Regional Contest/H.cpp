#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;

int R, C;
int cnt[26], sum = 0;

void input() {
    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        string s; cin >> s;
        for (int j = 0; j < C; j++) {
            if (s[j] == '.') continue;
            cnt[s[j] - 'a']++;
            sum++;
        }
    }
}

int dp[1010101];
int acnt, bcnt;
vector<int> a, b;

void knapsack() {
    dp[0] = (1 << 26);
    for (int i = 0; i < 26; i++) {
        for (int j = 1010101 - 1; j >= 0; j--) {
            if (dp[j]) dp[j + cnt[i]] = dp[j] + (1 << i);
        }
    }

    for (int i = 0; i < 1010101; i++) {
        if (!dp[i]) continue;
        acnt = i, bcnt = sum - i;
        if (acnt < bcnt) continue;

        for (int bit = 0; bit < 26; bit++) {
            if (cnt[bit] == 0) continue;
            if ((1 << bit) & dp[i]) a.push_back(bit);
            else b.push_back(bit);
        }
        break;
    }
}

ll ansR = INF, ansC = INF;
string ans[3030];

void fillGrid(int y, int x) {
    queue<pair<char, int>> aleft, bleft;
    for (auto& i : a) aleft.push({ i + 'a', cnt[i] });
    for (auto& i : b) bleft.push({ i + 'a', cnt[i] });

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if ((i + j) % 2 == 0) {
                if (aleft.empty()) ans[i][j] = '.';
                else {
                    ans[i][j] = aleft.front().first;
                    aleft.front().second--;
                    if (aleft.front().second == 0) aleft.pop();
                }
            }
            else {
                if (bleft.empty()) ans[i][j] = '.';
                else {
                    ans[i][j] = bleft.front().first;
                    bleft.front().second--;
                    if (bleft.front().second == 0) bleft.pop();
                }
            }
        }
    }
}

void solve() {
    for (int i = 0; i < 3030; i++)
        ans[i].resize(3030, '.');

    for (int y = R; y <= 2 * R; y++) {
        // (y * x + 1) / 2 >= acnt
        for (int x = C; x <= 2 * C; x++) {
            int black = (y * x + 1) / 2;
            int white = y * x / 2;

            if (black >= acnt) {
                if (y * x < ansR * ansC) {
                    ansR = y, ansC = x;
                }

                break;
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    knapsack();

    solve();

    fillGrid(ansR, ansC);

    cout << ansR << ' ' << ansC << '\n';
    for (int i = 0; i < ansR; i++) {
        for (int j = 0; j < ansC; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
}