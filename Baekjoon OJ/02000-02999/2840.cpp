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

int n, k;
int a[105];
char b[105], c[30];

void input() {
    cin >> n >> k;
    
    for (int i = 0; i < k; i++) {
        cin >> a[i] >> b[i];
    }
}

int f2(int idx, int z) {
    return (idx + z) % n;
}

int f3() {
    vector<int> cnt(26);
    
    for (int i = 0; i < n; i++) {
        if (c[i]) {
            cnt[c[i] - 'A']++;
            if (cnt[c[i] - 'A'] > 1) return 1;
        }
    }
    
    return 0;
}

void f() {
    int x = 0, fal = 0;
    
    c[x] = b[k - 1];
    for (int i = k - 2; i >= 0; i--) {
        x = f2(x, a[i + 1]);
        //cout << x << ' ' << a[i + 1] << '\n';
        if (!c[x]) c[x] = b[i];
        else if (c[x] != b[i]) {
            fal = 1;
            break;
        }
    }
    
    if (fal | f3()) cout << '!';
    else {
        for (int i = 0; i < n; i++) {
            if (!c[i]) cout <<'?';
            else cout << (char)c[i];
        }
    }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	input();
	
	f();
	
	return 0;
}
