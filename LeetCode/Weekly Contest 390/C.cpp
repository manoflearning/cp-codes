int flag;  // array size
struct Seg {  // 1-indexed
	vector<long long> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
        for (auto& i : t) i = 0;
	}
	void modify(int p, long long value) {  // add value at position p
        t[p += flag - 1] += value;
		for (; p > 1; p >>= 1) {
            t[p >> 1] = max(t[p], t[p ^ 1]);
        }
	}
	long long query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

class Solution {
public:
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
        int n = nums.size();
        
        seg.build(101010);

        vector<long long> ans;
        for (int i = 0; i < n; i++) {
            seg.modify(nums[i], freq[i]);
            long long res = seg.query(1, 101010);
            ans.push_back(res);
        }

        return ans;
    }
};