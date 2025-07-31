#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 5050;

int n, p[N];

void init() {}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int tc; cin >> tc;
    while (tc--) {
        init();
        
        input();
        
        int ans = 0;
        for (int j = 1; j <= n; j++) {
            int lcnt = 0, rcnt = 0;
            for (int i = 1; i < j; i++) {
                if (p[i] > p[j]) lcnt++;
            }
            for (int k = j + 1; k <= n; k++) {
                if (p[j] < p[k]) rcnt++;
            }
            ans += min(lcnt, rcnt);
        }
        cout << ans << '\n';
    }
}
