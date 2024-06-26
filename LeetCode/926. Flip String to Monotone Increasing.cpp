// solution 2
class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int ans = 0, cnt1 = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') cnt1++;
            else if (cnt1) ans = min(cnt1, ans + 1);
        }
        return ans;
    }
};

// solution 1
class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int cnt0 = 0, cnt1 = 0;
        for (int i = 0; i < s.size(); i++) {
            cnt0 += s[i] == '0';
        }

        int ans = cnt0 + cnt1;
        for (int i = 0; i < s.size(); i++) {
            cnt0 -= s[i] == '0';
            cnt1 += s[i] == '1';
            ans = min(ans, cnt0 + cnt1);
        }

        return ans;
    }
};