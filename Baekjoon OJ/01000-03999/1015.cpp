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

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int N; cin>>N;
    vector<int> a(N);
    for(int& i : a) cin>>i;

    vector<pii> b(N);
    for(int i=0; i<N; i++) b[i] = {a[i], i};

    sort(b.begin(), b.end());

    vector<int> res(N);
    for(int i=0; i<N; i++) res[b[i].second] = i;
    for(int i=0; i<N; i++) cout<<res[i]<<' ';

    return 0;
}