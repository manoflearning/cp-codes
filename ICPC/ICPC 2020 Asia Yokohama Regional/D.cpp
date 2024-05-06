#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXN = 101010;

int n;
int x[MAXN], y[MAXN], c[MAXN];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i] >> c[i];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    
}