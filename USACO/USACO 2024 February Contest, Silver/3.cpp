#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define fr first
#define sc second

const int INF = 1e9 + 7;

int n, m, k;
int even_max[303030], odd_max[303030];
int even_min[303030], odd_min[303030];
bool even_bit[303030], odd_bit[303030];
int min_loss_sum[303030];

void init() {
    for (int i = 0; i < m; i++) {
        even_bit[i] = odd_bit[i] = 0;
    }
}

void input() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        even_max[i] = odd_max[i] = 0;
        even_min[i] = odd_min[i] = INF;

        for (int j = 0; j < k; j++) {
            int x; cin >> x;
            if (x & 1) {
                even_max[i] = max(even_max[i], x);
                odd_min[i] = min(odd_min[i], x);
                odd_bit[i] = 1;
            }
            else {
                odd_max[i] = max(odd_max[i], x);
                even_min[i] = min(even_min[i], x);
                even_bit[i] = 1;
            }
        }
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        input();

        min_loss_sum[m] = 0; 
        for (int i = m - 1; i >= 0; i--) {
            if (even_bit[i] && odd_bit[i]) {
                min_loss_sum[i] = min_loss_sum[i + 1] + min(even_max[i], odd_max[i]);
            }
            else if (even_bit[i]) {
                min_loss_sum[i] = min_loss_sum[i + 1] - even_min[i];
            }
            else if (odd_bit[i]) {
                min_loss_sum[i] = min_loss_sum[i + 1] - odd_min[i];
            }
            min_loss_sum[i] = max(0, min_loss_sum[i]);
        }

        if (n <= min_loss_sum[0]) cout << -1 << '\n';
        else {
            int prev_loss = 0;
            vector<string> ans;
            for (int i = 0; i < m; i++) {
                if (even_bit[i] && odd_bit[i]) {
                    if (prev_loss + even_max[i] + min_loss_sum[i + 1] < n) {
                        ans.push_back("Even");
                        prev_loss += even_max[i];
                    }
                    else {
                        ans.push_back("Odd");
                        prev_loss += odd_max[i];
                    }
                }
                else if (even_bit[i]) {
                    ans.push_back("Even");
                    prev_loss -= even_min[i];
                }
                else if (odd_bit[i]) {
                    if (prev_loss + even_max[i] + min_loss_sum[i + 1] < n) {
                        ans.push_back("Even");
                        prev_loss += even_max[i];
                    }
                    else {
                        ans.push_back("Odd");
                        prev_loss -= odd_min[i];
                    }
                }
            }

            for (int i = 0; i < sz(ans); i++) {
                cout << ans[i];
                if (i + 1 < sz(ans)) cout << ' ';
            }
            cout << '\n';
        }

        init();
    }
}
