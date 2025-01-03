#include <bits/stdc++.h>
using namespace std;

int n;
int vi[20202];
string s[20202];
string ans;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        memset(vi, 0, sizeof(vi));
        ans.clear();

        cin >> n;
        
        queue<int> q;
        q.push(1 % n);
        vi[1 % n] = 1;
        s[1 % n] = "1";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if (v % n == 0) { ans = s[v]; break; }
            for (int i = 0; i < 2; i++) {
                int u = (v * 10 + i) % n;
                if (vi[u]) continue;
                q.push(u);
                vi[u] = 1;
                s[u] = s[v] + "01"[i];
            }
        }

        cout << (ans.empty() ? "BRAK" : ans) << '\n';
    }
}