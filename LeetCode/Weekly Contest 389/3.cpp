#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int> cnt(26);
        for (auto& i : word) cnt[i - 'a']++;
        
        vector<int> ord;
        for (int i = 0; i < 26; i++) {
            if (cnt[i]) ord.push_back(i);
        }
        sort(all(ord), [&](const int& p1, const int& p2) {
            return cnt[p1] < cnt[p2];
        });
        
        ll ret = INF;
        for (int del = 0; del < sz(ord); del++) {
            ll res = 0;
            for (int i = 0; i < del; i++) {
                res += cnt[ord[i]];
            }
            for (int i = del; i < sz(ord); i++) {
                res += max(0, cnt[ord[i]] - cnt[ord[del]] - k);
            }
            ret = min(ret, res);
        }
        return ret;
    }
};