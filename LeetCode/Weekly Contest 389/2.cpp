class Solution {
public:
    long long countSubstrings(string s, char c) {
        long long x = 0;
        for (auto& i : s) {
            if (i == c) x++;
        }
        long long ans = 0;
        ans += x * (x - 1) / 2 + x;
        return ans;
    }
};