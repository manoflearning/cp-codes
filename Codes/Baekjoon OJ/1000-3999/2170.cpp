#include <iostream>
#include <vector>
#include <algorithm>
#define pii pair<int, int>
using namespace std;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N; cin >> N;

	vector<pii> arr(N);
	for (pii& i : arr) {
		cin >> i.first >> i.second;
		if (i.first > i.second) swap(i.first, i.second);
	}

	sort(arr.begin(), arr.end());

	int ans = 0;
	for (int i = 0; i < arr.size(); i++) {
		if (i + 1 < arr.size() && arr[i].second >= arr[i + 1].first) {
			arr[i + 1].first = arr[i].first;
			if (arr[i + 1].second < arr[i].second) 
				arr[i + 1].second = arr[i].second;
		}
		else {
			ans += arr[i].second - arr[i].first;
		}
	}

	cout << ans << '\n';

	return 0;
}