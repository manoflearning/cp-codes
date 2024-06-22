#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <math.h>
using namespace std;
#define fast_io() cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
typedef pair<int, int> pii;

const double r2 = sqrt(2.0l);
vector<pii> peak;
int q,w;

int main(){
    fast_io();

    cin >> q >> w;

    int x, y;

    for(int i=0; i<q; i++){
        cin >> x >> y;
        int tmp;
        if(!peak.empty() && peak[tmp=lower_bound(peak.begin(), peak.end(), make_pair(x-y, x+y))-peak.begin()]==make_pair(x-y, x+y)){
            peak.erase(peak.begin()+tmp);
        }else{
            peak.push_back({x-y, x+y});
            sort(peak.begin(), peak.end());
        }
        int len=0, last=0;
        for(int j=0; j<peak.size(); j++){
            int f=peak[j].first<0?0:peak[j].first;
            int s=peak[j].second>w?w:peak[j].second;
            if(s<last) continue;
            if(f<=last) len+=s-last;
            else len+=s-f;

            last=peak[j].second;
        }

        cout << fixed;
        cout.precision(6);

        cout << (double)len*r2 << '\n';
    }

    return 0;
}