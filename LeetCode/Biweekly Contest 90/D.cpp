// solution 1
class Solution {
public:
    vector<int> secondGreaterElement(vector<int>& nums) {
        int n = nums.size();
        
        vector<pair<int, int>> a;
        for (int i = 0; i < n; i++) {
            a.push_back({ -nums[i], i });
        }
        
        sort(a.begin(), a.end());
        
        vector<int> ans(n, -1), arr;
        
        set<int> s;
        for (int i = 0; i < n; i++) {
            if (i > 0 && a[i].first > a[i - 1].first) {
                for (auto& j : arr) s.insert(j);
                arr.clear();
            }
            
            auto it = s.upper_bound(a[i].second);
            if (it != s.end()) {
                it++;
                if (it != s.end()) {
                    ans[a[i].second] = nums[*it];
                }
            }
            
            arr.push_back(a[i].second);
        }
        
        return ans;
    }
};

// solution 2: use segment tree
/*#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

class Solution {
public:
    int INF = 1e9 + 7;
    vector<int> c;

    void cc(vector<int>& nums) {
        c.push_back(-INF);
        for (auto& i : nums)
            c.push_back(i);
        
        sort(c.begin(), c.end());
        c.erase(unique(c.begin(), c.end()), c.end());
        
        for (auto& i : nums)
            i = lower_bound(c.begin(), c.end(), i) - c.begin();
    }
    
    int n;
    pair<int, int> t[202020];

	void build(int N) {
        n = N;
		for (int i = 0; i < 202020; i++) t[i] = { INF, INF };
	}
	void modify(int p, int value) {  // set value at position p
        p += n;
        if (value < t[p].first) {
            t[p].second = t[p].first;
            t[p].first = value;
        }
        else if (value < t[p].second) {
            t[p].second = value;
        }
        
		for (; p > 1; p >>= 1) {            
            int mn1 = INF, mn2 = INF;
            
            if (t[p].first < mn1) {
                mn2 = mn1;
                mn1 = t[p].first;
            }
            else if (t[p].first < mn2) {
                mn2 = t[p].first;
            }
            
            if (t[p].second < mn1) {
                mn2 = mn1;
                mn1 = t[p].second;
            }
            else if (t[p].second < mn2) {
                mn2 = t[p].second;
            }
            
            if (t[p ^ 1].first < mn1) {
                mn2 = mn1;
                mn1 = t[p ^ 1].first;
            }
            else if (t[p ^ 1].first < mn2) {
                mn2 = t[p ^ 1].first;
            }
            
            if (t[p ^ 1].second < mn1) {
                mn2 = mn1;
                mn1 = t[p ^ 1].second;
            }
            else if (t[p ^ 1].second < mn2) {
                mn2 = t[p ^ 1].second;
            }
            
            t[p >> 1] = { mn1, mn2 };
        }
	}
    
	pair<int, int> query(int l, int r) {  // sum on interval [l, r)
		int mn1 = INF, mn2 = INF;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) {
                if (t[l].first < mn1) {
                    mn2 = mn1;
                    mn1 = t[l].first;
                }
                else if (t[l].first < mn2) {
                    mn2 = t[l].first;
                }
                
                if (t[l].second < mn1) {
                    mn2 = mn1;
                    mn1 = t[l].second;
                }
                else if (t[l].second < mn2) {
                    mn2 = t[l].second;
                }
                
                l++;
            }
			if (r & 1) {
                r--;
                
                if (t[r].first < mn1) {
                    mn2 = mn1;
                    mn1 = t[r].first;
                }
                else if (t[r].first < mn2) {
                    mn2 = t[r].first;
                }
                
                if (t[r].second < mn1) {
                    mn2 = mn1;
                    mn1 = t[r].second;
                }
                else if (t[r].second < mn2) {
                    mn2 = t[r].second;
                }
            }
		}
		return { mn1, mn2 };
	}
    
    vector<int> secondGreaterElement(vector<int>& nums) {
        cc(nums);
        
        build((int)c.size() - 1);
        
        vector<int> ans(nums.size());
        for (int i = (int)nums.size() - 1; i >= 0; i--) {
            pair<int, int> res = query(nums[i] + 1, (int)c.size());
            
            if (res.second == INF) ans[i] = -1;
            else ans[i] = c[nums[res.second]];
            
            modify(nums[i], i);
        }
        
        return ans;
    }
};*/