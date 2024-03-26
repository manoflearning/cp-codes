class Solution {
public:
    int maximumLengthSubstring(string s) {
        int ret = 0;
        for (int i = 0; i < s.size(); i++) {
            vector<int> cnt(26);
            for (int j = i; j < s.size(); j++) {
                cnt[s[j] - 'a']++;

                if (cnt[s[j] - 'a'] > 2) break;

                ret = max(ret, j - i + 1);
            }
        }
        return ret;
    }
};