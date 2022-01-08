//divide & conquer
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

const int MAXN = 1e5;

int n, a[MAXN + 5];

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

int f(int l, int r) {
    if (l == r) return a[l];
    
    int mid = (l + r) / 2, ml = mid - 1, mr = mid + 2;
    int mn = min(a[mid], a[mid + 1]), sz = 2 * mn;
    
    for (int i = 3; ; i++) {
        if (l <= ml && (a[ml] >= a[mr] || r < mr)) {
            mn = min(mn, a[ml]);
            ml--;
        }
        else if (mr <= r && (a[ml] <= a[mr] || ml < l)) {
            mn = min(mn, a[mr]);
            mr++;
        }
        else break;
        
        sz = max(sz, i * mn);
    }
    
    return max({ sz, f(l, mid), f(mid + 1, r) });
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	input();
	
	cout << f(0, n - 1);
	
	return 0;
}

//stack
/*#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX = 100000;

int n;
int histo[MAX];
int leftHisto[MAX], rightHisto[MAX];

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", &histo[i]);

	for (int i = 0; i < n; i++)
		leftHisto[i] = -1, rightHisto[i] = n;

	stack<int> height;

	for (int i = 0; i < n; i++) {
		while (true) {
			if (height.empty()) break;
			else if (histo[i] > histo[height.top()]) {
				leftHisto[i] = height.top();
				break;
			}
			else if (histo[i] <= histo[height.top()]) {
				rightHisto[height.top()] = i;
				height.pop();
			}
		}
		
		height.push(i);
	}

	int ans = 0;
	for (int i = 0; i < n; i++)
		ans = max(ans, (rightHisto[i] - leftHisto[i] - 1) * histo[i]);

	printf("%d", ans);

	return 0;
}*/
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 스택의 활용
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////
