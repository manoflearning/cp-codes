set<int> arr[2020];
class Solution {
public:
    int findMinimumTime(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), [&](const vector<int>& lhs, const vector<int>& rhs) {
            if (lhs[1] ^ rhs[1]) return lhs[1] < rhs[1];
            else return lhs[0] < rhs[0];
        });
        
        vector<int> vi(2020);
        
        for (int i = 0; i < tasks.size(); i++) {
            auto& it = tasks[i];
            
            for (int i = it[1]; i >= it[0]; i--)
                if (vi[i]) it[2]--;
            if (it[2] <= 0) continue;
            
            for (int i = it[1]; i >= it[0]; i--) {
                if (!it[2]) break;
                
                if (!vi[i]) { vi[i] = 1, it[2]--; }
            }
        }
        
        int ret = 0;
        for (auto& i : vi) ret += i;
        
        return ret;
    }
    /*int findMinimumTime(vector<vector<int>>& tasks) {
        for (int i = 0; i < tasks.size(); i++) {
            auto& it = tasks[i];
            for (int j = it[0]; j <= it[1]; j++) arr[j].insert(i);
        }
        
        int ret = 0;
        while (1) {
            int mx = 1;
            for (int i = 2; i <= 2000; i++) {
                if (arr[mx].size() < arr[i].size()) mx = i;
            }
            if (arr[mx].empty()) break;
            
            ret++;
            
            for (auto& i : arr[mx]) {
                assert(tasks[i][2] > 0);
                tasks[i][2]--;
                if (!tasks[i][2]) {
                    for (int j = tasks[i][0]; j <= tasks[i][1]; j++) {
                        if (j == mx) continue;
                        if (arr[j].count(i)) arr[j].erase(i);
                    }
                }
            }
            
            arr[mx].clear();
        }
        
        return ret;
    }*/
};