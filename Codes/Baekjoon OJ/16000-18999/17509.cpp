// Bruteforce
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

const int MAX = 11;

struct dv {
    int d, v;
};

vector<dv> a(MAX);
int visited[MAX];

void input() {
    for(auto& i : a) 
        cin >> i.d >> i.v;
}

int f(int idx) {
    if (idx == MAX) return 0;
    
    int ret = INF;
    
    for (int i = 0; i < MAX; i++) {
        if (visited[i]) continue;
        
        visited[i] = 1;
        ret = min(ret, (idx + 1) * a[i].d + 20 * a[i].v + f(idx + 1));
        visited[i] = 0;
    }
    
    return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	input();
	
	cout << f(0);
	
	return 0;
}
