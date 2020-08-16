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
const int MAX = 1e6;

bool isPrime[MAX + 1];
vector<int> prime(1, 2);

void getPrime() {
	fill(isPrime, isPrime + MAX + 1, true);

	for (ll i = 4; i <= MAX; i += 2)
		isPrime[i] = false;
	for (ll i = 3; i <= MAX; i++) {
		if (isPrime[i]) prime.push_back(i);
		for (ll j = i * i; j <= MAX; j += i * 2)
			isPrime[j] = false;
	}
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    getPrime();

    int N; cin>>N;

    if(N & 1) {
        //홀수인 소수가 1개 또는 3개
        if(isPrime[N-6]) {
            cout<<"2 2 2 "<<N-6;
            return 0;
        }
        
        for(int i=3; i<N-2; i+=2) {
            if(!isPrime[i]) continue;
            for(int j=i; j<=N-2-i-j; j+=2) {
                if(!isPrime[j] || !isPrime[N-2-i-j]) continue;
                cout<<"2 "<<i<<' '<<j<<' '<<N-2-i-j;
                return 0;
            }
        }
    }
    else {
        //홀수인 소수가 0개 혹은 2개 또는 4개
        if(N == 8) {
            cout<<"2 2 2 2";
            return 0;
        }

       for(int i=3; i<N-4 && i<=N-4-i; i+=2) {
            if(!isPrime[i] || !isPrime[N-4-i]) continue;
            cout<<"2 2 "<<i<<' '<<N-4-i;
            return 0;
        }

        for(int i=3; i<N; i+=2) {
            if(!isPrime[i]) continue;
            for(int j=i; i+j<N; j+=2) {
                if(!isPrime[j]) continue;
                for(int k=j; k<=N-i-j-k; k+=2) {
                    if(!isPrime[k] || !isPrime[N-i-j-k]) continue;
                    cout<<i<<' '<<j<<' '<<k<<' '<<N-i-j-k;
                    return 0;
                }
            }
        }
    }

    cout<<-1;

    return 0;
}