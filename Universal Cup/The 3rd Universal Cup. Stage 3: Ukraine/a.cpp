#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

void YES(const string& ans) { cout << "YES\n" << ans << '\n'; }
void NO() { cout << "NO\n"; }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        string s; cin >> s;
        
        vector<int> cnt(26);
        for (auto& i : s) cnt[i - 'a']++;

        vector<int> ord;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] == 0) continue;
            else ord.push_back(i);
        }

        sort(all(ord), [&](const int& p1, const int& p2) {
            return cnt[p1] < cnt[p2];
        });

        if (cnt[ord[0]] == 1) {
            string ans;
            for (auto& i : ord) {
                while (cnt[i]--) ans.push_back(i + 'a');
            }
            YES(ans);
            continue;
        }

        if (sz(ord) >= 3) {
            string ans;
            while (1) {
                bool is_valid = 0;
                for (auto& i : ord) {
                    if (cnt[i] > 0) {
                        is_valid = 1;
                        cnt[i]--;
                        ans.push_back(i + 'a');
                    }
                }

                if (!is_valid) break;
            }

            YES(ans);
            continue;
        }

        NO();
    }
}