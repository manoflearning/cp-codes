#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

string s, t, ans;
int cnt[10], psum[10][1010];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> s >> t;
    for (int i = 0; i < sz(t); i++) {
        cnt[t[i] - '0']++;
    }

    for (int i = sz(s) - 1; i >= 0; i--) {
        psum[s[i] - '0'][i]++;
        for (int j = 0; j < 10; j++) {
            psum[j][i] += psum[j][i + 1];
        }
    }

    for (int i = 0; i < sz(s); i++) {
        if (!cnt[s[i] - '0']) {
            ans.push_back(s[i]);
            continue;
        }
        else if (psum[s[i] - '0'][i] == cnt[s[i] - '0']) {
            cnt[s[i] - '0']--;
            continue;
        }

        vector<int> cnt2(10);
        cnt2[s[i] - '0']++;
        for (int j = i + 1; j < sz(s); j++) {
            if (s[j] > s[i]) {
                for (int k = 0; k < 10; k++) cnt[k] -= cnt2[k];
                i = j - 1;
                break;
            }
            else if (s[j] == s[i]) {
                int now = 0;
                for (int k = j + 1; k < sz(s); k++) {
                    if (s[k] < s[k - j + i]) { now = 1; break; }
                    if (s[k] > s[k - j + i]) break;
                }

                if (now) {
                    ans.push_back(s[i]);
                    break;
                }
                else {
                    for (int k = 0; k < 10; k++) cnt[k] -= cnt2[k];
                    i = j - 1;
                    break;
                }
            }
            else {
                if (cnt[s[j] - '0'] == cnt2[s[j] - '0']) {
                    ans.push_back(s[i]);
                    break;
                }
                else cnt2[s[j] - '0']++;
            }
        }
    }

    cout << ans;

    return 0;
}