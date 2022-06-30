#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct p{
    ll x, y, color, idx;
    p(){}
    p(ll x, ll y, ll color, ll idx) : x(x), y(y), color(color), idx(idx) {}
    bool operator < (const p &t) const {
        return x*t.y > y*t.x;
    }
    p operator - (p &t){
        return {x - t.x, y - t.y, this->color, this->idx};
    }
};

p pt[3030];
int ans[1010][2];
int n;

void solve(vector<int> &pidx){
	if(pidx.empty()) return;
    
	vector<p> v;
	for(int i=0; i<pidx.size(); i++){
		v.push_back(pt[pidx[i]]);
		v.back().idx = pidx[i];
	}
	for(int i=1; i<v.size(); i++){
		if(v[0].y > v[i].y || (v[0].y == v[i].y && v[0].x > v[i].x)){
			swap(v[0], v[i]);
		}
	}
	for(int i=v.size()-1; i>=0; i--) v[i] = v[i] - v[0];
	sort(v.begin() + 1, v.end());

    for (auto i : v) cout << i.x << ' ' << i.y << '\n';
    cout << '\n';

	int st = -1, fst = v[0].idx;
	v.erase(v.begin());

	if(pt[fst].color) st = fst;
	else if(pt[v[0].idx].color) st = v[0].idx;
	else if(pt[v.back().idx].color) st = v.back().idx;

	if(st != -1){
		if(st != fst){
			v.clear();
			for(int i=0; i<pidx.size(); i++){
                if(pidx[i] != st){
				    v.push_back(pt[pidx[i]] - pt[st]);
				    v.back().idx = pidx[i];
                }
			}
			sort(v.begin(), v.end());
		}
		int cnt = 0, pv = -1;
		vector<int> nxt;
		for(int i=0; i<v.size(); i++){
			cnt += pt[v[i].idx].color ? 2 : -1;
			if(cnt == pv){
				if(pv == -1) ans[st][0] = v[i].idx;
                else ans[st][1] = v[i].idx;
				solve(nxt); nxt.clear(); pv--;
				if(pv < -2) pv = 1e9+7;
			}
			else{
				nxt.push_back(v[i].idx);
			}
		}
		solve(nxt); return;
	}

	for(int asdf=0; asdf<2; asdf++){
		int cnt = 0;
		vector<int> nxt;
		for(int i=0; i<v.size(); i++){
			cnt += pt[v[i].idx].color ? 2 : -1;
			nxt.push_back(v[i].idx);
			if(cnt == 0){
				solve(nxt);
				nxt.clear();
				for(int j=i+1; j<v.size(); j++) nxt.push_back(v[j].idx);
				nxt.push_back(fst);
				solve(nxt);
				return;
			}
		}
		reverse(v.begin(), v.end()); //한 방향으로만 탐색하면 분할할 지점을 못 찾을 수 있음
	}
}

int main(){
    #ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    vector<int> v;
    for(int i=0; i<3*n; i++){
        cin >> pt[i].x >> pt[i].y;
        if(i < n) pt[i].color = 1; //blue
        else pt[i].color = 0; //red
        pt[i].idx = i;
        v.push_back(i);
    }
    solve(v);
    for(int i=0; i<n; i++) cout << ans[i][0]-n+1 << " " << ans[i][1]-n+1 << "\n";
}