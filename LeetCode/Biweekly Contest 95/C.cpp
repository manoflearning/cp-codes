class Solution {
public:
    int xorBeauty(vector<int>& nums) {
        int n = nums.size();
        
        int T = 0;
        for (auto& i : nums) T ^= i;
        
        int ret = 0;
        for (auto& i : nums) ret ^= (i & T);
        
        return ret;
    }
};