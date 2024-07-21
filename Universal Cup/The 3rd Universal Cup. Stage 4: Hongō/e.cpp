// 1. if m is e => T
// 2. if m is o & n is e => F
// 3. if m is o & n is o
// 3.1. if m = 1 & n > 1 => F
// 3.2. if m > 1 & n = 1 => T
// 3.3. if m > 1 & n > 1 => 

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

int n, m;
vector<vector<int>> ans;

void YES() {
    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
}

void NO() { cout << "No\n"; }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> m;
        
        ans.clear();
        ans.resize(n, vector<int>(m));

        if (m % 2 == 0) {
            int p = 0;
            for (int i = 0; i < m; i++) {
                if (i % 2 == 0) {
                    for (int j = 0; j < n; j++) {
                        ans[j][i] = ++p;
                    }
                }
                else {
                    for (int j = n - 1; j >= 0; j--) {
                        ans[j][i] = ++p;
                    }
                }
            }

            YES();
        }
        else if (m % 2 == 1) {
            if (n % 2 == 0) NO();
            else if (n == 1) {
                for (int i = 0; i < m; i++) ans[0][i] = i + 1;
                YES();
            }
            else if (m == 1) NO();
            else if (n % 2 == 1) {
                vector<vector<int>> du(3, vector<int>(n));
                int p = 0;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < n; j++) {
                        du[i][j] = ++p;
                    }
                }

                for (int i = 0; i < n; i++) {
                    ans[i][0] = du[0][i];
                    ans[i][1] = du[1][(i + n / 2) % n];
                    ans[i][2] = du[2][(n - 1 + (ll)i * (n - 2)) % n];
                }

                for (int i = 3; i < m; i++) {
                    if (i % 2 == 0) {
                        for (int j = 0; j < n; j++) {
                            ans[j][i] = ++p;
                        }
                    }
                    else {
                        for (int j = n - 1; j >= 0; j--) {
                            ans[j][i] = ++p;
                        }
                    }
                }

                YES();
            }
        }
    }
}