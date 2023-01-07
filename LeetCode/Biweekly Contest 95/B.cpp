class DataStream {
public:
    int x = 0, y = 0, cnt = 0;
    queue<int> q; 
    
    DataStream(int value, int k) {
        x = value, y = k;
    }
    
    bool consec(int num) {
        q.push(num);
        if (num == x) cnt++;
        while (q.size() > y) {
            if (q.front() == x) cnt--;
            q.pop();
        }
        
        return cnt == y;
    }
};

/**
 * Your DataStream object will be instantiated and called as such:
 * DataStream* obj = new DataStream(value, k);
 * bool param_1 = obj->consec(num);
 */