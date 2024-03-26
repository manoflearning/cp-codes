class Solution {
public:
    int minOperations(int k) {
        int ret = k - 1;

        for (int i = 0; i <= k - 1; i++) {
            int x = i + 1;
            int cnt1 = i;
            int cnt2 = (k + x - 1) / x - 1;

            ret = min(ret, cnt1 + cnt2);
        }
        
        return ret;
    }
};