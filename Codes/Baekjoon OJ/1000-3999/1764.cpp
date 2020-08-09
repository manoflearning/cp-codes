#include <iostream>
#include <map>
using namespace std;

map<string, int> arr1, arr2;

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m; cin >> n >> m;

    while (n--) {
        string s; cin >> s;
        arr1.insert({ s, 1 });
    }

    int cnt = 0;

    while (m--) {
        string s; cin >> s;
        map<string, int>::iterator it = arr1.find(s);
        if (it != arr1.end()) {
            arr2.insert({ s, 1 });
            cnt++;
        }
    }

    cout << cnt << '\n';

    map<string, int>::iterator it = arr2.begin();
    while (it != arr2.end()) {
        cout << it->first << '\n';
        it++;
    }

    return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: map을 통한 O(lgn)시간의 삽입, 탐색
결정적 깨달음		: 
시간복잡도		: O(nlgn + mlgn)
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////