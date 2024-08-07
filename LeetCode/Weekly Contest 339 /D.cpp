//#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        vector<int> dist(n, -1);
        vector<int> vi(n);
        for (auto& i : banned) vi[i] = 1;
        
        vector<set<int>> idx(2);
        for (int i = 0; i < n; i++) {
            if (!vi[i]) idx[i & 1].insert(i);
        }
        
        queue<int> q;
        q.push(p);
        dist[p] = 0;
                
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            
            int bit = (k - 1) & 1;
            if (v & 1) bit = !bit;
            auto it = idx[bit].lower_bound(v - (k - 1));
            
            vector<int> res;
            
            while (it != idx[bit].end() && *it <= v + (k - 1)) {
                int u = *it; it++;
                
                int len = abs(u - v) + 1, left = (k - len) / 2;
                if (min(u, v) - left < 0 || n <= max(u, v) + left) continue;
                
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    q.push(u);
                    res.push_back(u);
                }
            }
            
            for (auto& i : res)
                idx[bit].erase(i);
            
            /*for (int s = max(0, v - (k - 1)); s <= v; s++) {
                int e = s + (k - 1);
                if (n <= e) break;
                int u = e - (v - s);
                if (u < 0 || n <= u) continue;
                if (!vi[u] && dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    q.push(u);
                }
            }*/
        }
        
        return dist;
    }
};