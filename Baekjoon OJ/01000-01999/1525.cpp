#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vvi vector<vector<int>>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

int st, en;
int p9[9];
map<int, int> dist;
vi d[9];

void init() {
    p9[0] = 1;
    for (int i = 1; i < 9; i++)
        p9[i] = 9 * p9[i - 1];
    
    for (int i = 0; i < 8; i++) {
        en += (i + 1) * p9[i];
    }
    
    for (int i = 0; i < 9; i++) {
        if (i % 3 != 2 && 0 <= i + 1 && i + 1 < 9) d[i].push_back(i + 1);
        if (0 <= i + 3 && i + 3 < 9) d[i].push_back(i + 3);
        if (i % 3 != 0 && 0 <= i - 1 && i - 1 < 9) d[i].push_back(i - 1);
        if (0 <= i - 3 && i - 3 < 9) d[i].push_back(i - 3);
        //cout << i << ' ' << d[i].size() << '\n';
    }
}

void input() {
    for (int i = 0; i < 9; i++) {
        int x; cin >> x;
        st += x * p9[i];
    }
}

int findP(int x) {
    for (int i = 0; i < 9; i++) {
        if (x / p9[i] % 9 == 0) return i;
    }
    //assert(0);
}

int bfs() {
    queue<int> q;
    
    q.push(st);
    dist.insert({ st, 0 });
    
    while (!q.empty()) {
        int v = q.front(), p = findP(v);
        q.pop();
        
        if (v == en) return dist.find(v)->second;
        
        /*if (dist.find(v)->second == 1) {
            cout << '\n';
            for (int i = 0; i < 9; i++) {
                cout << v / p9[i] % 9 << ' ';
                if (i % 3 == 2) cout << '\n';
            }
        }*/
        
        for (auto i : d[p]) {
            int x = v / p9[i] % 9;
            int u = v - x * p9[i] + x * p9[p];
            
            if (dist.find(u) != dist.end()) continue;
            
            q.push(u);
            dist.insert({ u, dist.find(v)->second + 1 });
        }
    }
    
    return -1;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	init();
	
	input();
	
	cout << bfs();
	
	return 0;
}
