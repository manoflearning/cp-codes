#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    int n; cin >> n;

    if (n == 3) {
        cout << n - 1 << '\n';
        for (int i = 2; i <= n; i++) {
            cout << 2 << ' ' << 1 << ' ' << i << '\n';
        }
        return 0;
    }
    
    vector<vector<int>> ans;
    for (int i = n / 2; i >= 1; i >>= 1) {
        for (int k = 1; k <= n; k += i) {
            vector<int> res;
            for (int j = k; j <= n; j++) {
                if (sz(res) && sz(res) % i == 0) j += i;
                
                if (j > n) break;

                res.push_back(j);
            }
            ans.push_back(res);
        }   
    }

	return 0;
}