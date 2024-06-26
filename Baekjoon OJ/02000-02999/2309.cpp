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

int a[9], sum;
vector<int> b;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	for (int i = 0; i < 9; i++) {
	    cin >> a[i];
	    sum += a[i];
	}
	    
	    
	for (int i = 0; i < 9; i++) {
	    for (int j = i + 1; j < 9; j++) {
	        int res = sum - a[i] - a[j];
	        
	        if (res == 100) {
	            for (int k = 0; k < 9; k++) {
	                if (k == i || k == j) continue;
	                b.push_back(a[k]);
	            }
	            i = j = 9;
	            break;
	        }
	    }
	}
	
	sort(b.begin(), b.end());
	
	for (int i : b) cout << i << '\n';
	
	return 0;
}
