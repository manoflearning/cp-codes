// 한 행이 0으로만 이루어져 있다면 답은 그 행 하나.
// 
class Solution {
public:
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        for (int i = 0; i < m; i++) {
            int is1 = 0;
            for (auto& j : grid[i]) is1 += j;
            if (!is1) {
                vector<int> ret(1, i);
                return ret;
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                int isAns = 1;
                for (int k = 0; k < n; k++) {
                    if (grid[i][k] + grid[j][k] > 1) {
                        isAns = 0;
                        break;
                    }
                }
                if (isAns) {
                    vector<int> ret(2);
                    ret[0] = i, ret[1] = j;
                    return ret;
                }
            }
        }
        
        vector<int> ret;
        return ret;
    }
};
