#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int MAX = 101010;
const ll MOD = 998244353;

int N;
pair<int, ll> arr[MAX];
pair<ll, ll> ca[MAX];
vector<ll> red;

ll fact(ll n) {
    ll ret = 1;
    for(ll i = 1; i <= n; ++i) {
        ret *= i;
        ret %= MOD;
    }
    return ret;
}

void solve(int p) {
    if(p == 0) {
        sort(arr+1, arr+N+1, [](pair<int, ll> a, pair<int, ll> b) {
            return a.second > b.second;
        });
    }
    else {
        sort(arr+1, arr+N+1, [](pair<int, ll> a, pair<int, ll> b) {
            return a.second < b.second;
        });
    }
    
    vector<int> resultv;
    vector<ll> factorials;

    ll result = 0;
    ll prv = arr[1].second;
    int j = 0;
    for(int i = 1; i <= N; ++i) {
        if(arr[i].second != prv) {
            prv = arr[i].second;
            factorials.push_back(j);
            j = 0;
        }
        resultv.push_back(arr[i].first);
        result += (ca[arr[i].first].first * (i-1) + (ca[arr[i].first].second) * (N-i));
        j++;
    }
    factorials.push_back(j);

    cout<<result<<' ';
    
    result = 1;
    for(auto &i : factorials) {
        result = (result * fact(i)) % MOD;
    }
    cout<<result<<'\n';

    for(auto &i : resultv) {
        cout<<i<<" ";
    }
    cout<<'\n';

}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(0);

    cin>>N;
    for(int i = 1; i <= N; ++i) {
        ll c, a;
        cin>>ca[i].first>>ca[i].second;
        arr[i].first = i;
        arr[i].second = (ca[i].first-ca[i].second);
    }

    solve(0);
    solve(1);

}