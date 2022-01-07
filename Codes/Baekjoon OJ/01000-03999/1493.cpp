//greedy 1
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

ll l, w, h, n, arr[20];
ll ans, sum;

void input() {
    cin >> l >> w >> h >> n;
	
	for (int i = 0; i < n; i++) {
	    int a, b;
	    cin >> a >> b;
	    arr[a] = b;
	}
}

void f() {
    for (int i = 19; i >= 0; i--) {
        sum <<= 3;
        
        ll cnt = min(arr[i], (l >> i) * (w >> i) * (h >> i) - sum);
        
        sum += cnt;
        ans += cnt;
    }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	input();
	
	f();
	//cout << ans << '\n';
	if (sum == l * w * h) cout << ans;
	else cout << -1;

	return 0;
}

//greedy 2
/*#define _USE_MATH_DEFINES
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
struct ab {
    int a, b;
};
bool operator<(ab u, ab v) {
    return u.a > v.a;
}
int l, w, h;
int n;
vector<ab> arr;
int ex2[20];
void init() {
    ex2[0] = 1;
    for (int i = 1; i < 20; i++) {
        ex2[i] = 2 * ex2[i - 1];
    }
}
void input() {
    cin >> l >> w >> h;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
	    int a, b;
	    cin >> a >> b;
	    arr.push_back({ ex2[a], b });
	}
}
ll f(int l, int w, int h) {
    int len = min({ l, w, h }), ff, bit = 1;
    
    if (len == 0) return 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i].b > 0 && arr[i].a <= len) {
            arr[i].b--;
            ff = arr[i].a;
            bit = 0;
            break;
        }
    }
    
    if (bit) return INF;
    
    ll ret = 1;
    
    int lm = l - ff, wm = w - ff, hm = h - ff;
    
    ret += f(lm, w, h);
    ret += f(ff, wm, h);
    ret += f(ff, ff, hm);
    
    return ret;
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	init();
	
	input();
	
	sort(arr.begin(), arr.end());
	
	ll ans = f(l, w, h);
	
	if (ans >= INF) cout << -1;
	else cout << ans;
	return 0;
}*/
