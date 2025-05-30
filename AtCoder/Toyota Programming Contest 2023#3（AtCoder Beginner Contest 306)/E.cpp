#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int n, k, q;
vector<pair<int, int>> qu;
int a[505050];

multiset<int> smx, smn;
long long sum = 0;

void delsmx(int val) {
    auto it = smx.find(val);
    smx.erase(it);
    sum -= val;
}
void addsmx(int val) {
    smx.insert(val);
    sum += val;
}
void delsmn(int val) {
    auto it = smn.find(val);
    smn.erase(it);
}
void addsmn(int val) {
    smn.insert(val);
}

int biggest(multiset<int>& s) {
    if (s.empty()) return -INF;
    auto it = s.end();
    return *(--it);
}
int smallest(multiset<int>& s) {
    if (s.empty()) return INF;
    return *s.begin();
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k >> q;
    qu.resize(q);
    for (auto& i : qu)
        cin >> i.first >> i.second;

    for (int i = 0; i < k; i++) smx.insert(0);
    for (int i = 0; i < n - k; i++) smn.insert(0);

    for (auto& i : qu) {
        auto [idx, y] = i;
        int x = a[idx];
        a[idx] = y;

        int mxExist = (smx.find(x) != smx.end());
        int mnExist = (smn.find(x) != smn.end());
        
        if (mxExist && mnExist) {
            if (x <= y) { delsmx(x); addsmx(y); }
            else { 
                int tmp = biggest(smn);
                delsmx(x);
                addsmx(tmp);
                delsmn(tmp);
                addsmn(y);
            }
        }
        else if (mxExist) {
            if (biggest(smn) <= y) {
                delsmx(x);
                addsmx(y);
            }
            else {
                int tmp = biggest(smn);
                delsmx(x);
                addsmx(tmp);
                delsmn(tmp);
                addsmn(y);
            }
        }
        else if (mnExist) {
            if (y <= smallest(smx)) {
                delsmn(x);
                addsmn(y);
            }
            else {
                int tmp = smallest(smx);
                delsmx(tmp);
                addsmx(y);
                delsmn(x);
                addsmn(tmp);
            }
        }

        cout << sum << '\n';

        assert(smx.size() == k);
        assert(smn.size() == n - k);
    }
}