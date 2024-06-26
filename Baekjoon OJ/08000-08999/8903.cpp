#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n, m;
vector<vector<int>> a;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif
    
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> m;
    
        a.resize(n, vector<int>(5));
        for (auto& v : a) {
            for (int i = 0; i < 5; i++) {
                cin >> v[i];
            }
        }

        if (m == 1) {
            int ans = 0;
            for (auto& v : a) {
                ans = max(ans, v[0] + v[1] + v[2] + v[3] + v[4]);
            }
            cout << ans << '\n';
            continue;
        }
        if (m == 2) {
            int ans = 0;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    int res = 0;
                    for (int k = 0; k < 5; k++) {
                        res += max(a[i][k], a[j][k]);
                    }
                    ans = max(ans, res);
                }
            }
            cout << ans << '\n';
            continue;
        }

        if (m == 3) {
            int ans = 0;
            for (int i = 0; i < 5; i++) {
                for (int j = i + 1; j < 5; j++) {
                    for (int k = j + 1; k < 5; k++) {
                        vector<int> mx(5);

                        for (int p = 0; p < 5; p++) {
                            if (i == p || j == p || k == p) continue;
                            for (auto& v : a) 
                                mx[p] = max(mx[p], v[p]);
                        }
                        for (auto& v : a) {
                            mx[i] = max(mx[i], v[i] + v[j] + v[k]);
                        }

                        ans = max(ans, mx[0] + mx[1] + mx[2] + mx[3] + mx[4]);
                    }
                }
            }

            for (int i = 0; i < 5; i++) {
                for (int j = i + 1; j < 5; j++) {
                    for (int p = 0; p < 5; p++) {
                        for (int q = p + 1; q < 5; q++) {
                            if (i == p || i == q || j == p || j == q) continue;
                            
                            vector<int> mx(5);

                            for (int k = 0; k < 5; k++) {
                                if (i == k || j == k || p == k || q == k) continue;
                                for (auto& v : a) 
                                    mx[k] = max(mx[k], v[k]);
                            }
                            for (auto& v : a) {
                                mx[i] = max(mx[i], v[i] + v[j]);
                                mx[p] = max(mx[p], v[p] + v[q]);
                            }

                            ans = max(ans, mx[0] + mx[1] + mx[2] + mx[3] + mx[4]);
                        }
                    }
                }
            }
            cout << ans << '\n';
            continue;
        }
        if (m == 4) {
            int ans = 0;
            for (int i = 0; i < 5; i++) {
                for (int j = i + 1; j < 5; j++) {
                    vector<int> mx(5);

                    for (int k = 0; k < 5; k++) {
                        if (i == k || j == k) continue;
                        for (auto& v : a) 
                            mx[k] = max(mx[k], v[k]);
                    }
                    for (auto& v : a) {
                        mx[i] = max(mx[i], v[i] + v[j]);
                    }

                    ans = max(ans, mx[0] + mx[1] + mx[2] + mx[3] + mx[4]);
                }
            }
            cout << ans << '\n';
            continue;
        }

        if (m >= 5) {
            vector<int> mx(5);
            for (auto& v : a) {
                for (int i = 0; i < 5; i++) {
                    mx[i] = max(mx[i], v[i]);
                }
            }
            cout << mx[0] + mx[1] + mx[2] + mx[3] + mx[4] << '\n';
            continue;
        }
    }

    return 0;
}