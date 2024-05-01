#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second


int arr[500][500][26]{{{0,}}};
int maxn[500][500]={{0}};

char maxc[500][501]{{0,}};

int cti(char c){
    return c-'A';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m, k;
    char d[501];

    int i, i2, tmpy, tmpx, tmp, ans=0;

    cin >> n >> m >> k;

    for(i=0; i<n; i++){
        cin >> d;

        for(i2=0; i2<m; i2++){
            tmp=++arr[i%k][i2%k][cti(d[i2])];
            if(tmp>maxn[i%k][i2%k]){
                maxc[i%k][i2%k]=d[i2];
                maxn[i%k][i2%k]=tmp;
            }
        }
    }

    tmpy = m/k;
    tmpx = n/k;
    tmp=tmpy*tmpx;

    for(i=0; i<k; i++){
        for(i2=0; i2<k; i2++){
            ans+=tmp-maxn[i][i2];
        }
    }
    
    cout << ans << '\n';
    for(i=0; i<n; i++){
        int ii = i % k;
        for(i2=0; i2<m; i2++){
            int ii2 = i2 % k;
            cout << maxc[ii][ii2];
        }
        cout << '\n';
    }
}