#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MOD = 1e9 + 7;
const ll INF = 1e18;

int n;
int a[55][55];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    struct Node {
        char c; int x, y;
    };
    vector<Node> ans;
    for (int i = 0; i < 20000; i++) {
        bool need_to_move = 0;
        for (int i = 1; i <= n; i++) {
            if (need_to_move) break;
            for (int j = 1; j <= n; j++) {
                if (need_to_move) break;

                int x = a[i][j];
                if (x != i) {
                    need_to_move = 1;
                    
                    if (a[x][j] != x) {
                        Node res;
                        res.c = 'D';
                        res.x = j;
                        res.y = x - i > 0 ? x - i : n + x - i;
                        ans.push_back(res);

                        vector<int> tmp(n + 1);
                        for (int ii = 1; ii <= n; ii++) {
                            int idx = ii + res.y;
                            if (idx > n) idx -= n;
                            tmp[idx] = a[ii][j];
                        }
                        for (int ii = 1; ii <= n; ii++) {
                            a[ii][j] = tmp[ii];
                        }
                    }
                    else {
                        for (int k = 1; k <= n; k++) {
                            if (a[x][k] != x) {
                                Node res;
                                res.c = 'R';
                                res.x = i;
                                res.y = k - j > 0 ? k - j : n + k - j;
                                ans.push_back(res);

                                vector<int> tmp(n + 1);
                                for (int ii = 1; ii <= n; ii++) {
                                    int idx = ii + res.y;
                                    if (idx > n) idx -= n;
                                    tmp[idx] = a[i][ii];
                                }
                                for (int ii = 1; ii <= n; ii++) {
                                    a[i][ii] = tmp[ii];
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }

        if (!need_to_move) break;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << sz(ans) << '\n';
    for (auto& i : ans) {
        cout << i.c << ' ' << i.x << ' ' << i.y << '\n';
    }
}