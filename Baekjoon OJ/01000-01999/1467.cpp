#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

string s, t;
vector<int> cnt(10);
int psum[10][1010];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> s >> t;
    for (auto& i : s) cnt[i - '0']++;
    for (auto& i : t) cnt[i - '0']--;

    for (int i = sz(s) - 1; i >= 0; i--) {
        psum[s[i] - '0'][i]++;
        for (int j = 0; j < 10; j++) {
            psum[j][i] += psum[j][i + 1];
        }
    }

    string ans;

    int now = 0;
    for (int i = 0; i < sz(s) - sz(t); i++) {
        for (int j = 9; j >= 0; j--) {
            if (!cnt[j]) continue;
            
            int nxt = now;
            for (; nxt < sz(s) && s[nxt] - '0' != j; nxt++);

            if (nxt == sz(s)) continue;
            
            int bit = 1;
            for (int k = 0; k < 10; k++) {
                if (psum[k][nxt] < cnt[k]) bit = 0;
            }

            if (bit) {
                ans.push_back(j + '0');
                cnt[j]--;
                now = nxt + 1;
                break;
            }
        }
    }

    cout << ans;

	return 0;
}