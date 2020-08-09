#include <iostream>
#include <algorithm>

#define MAX 1000

int dp[MAX+1];

void most_long(int arr[], int n);

int main()
{
	//입력 
	int n;
	std::cin>>n;
	
	int arr[n+1];
	for(int i=1; i<=n; i++)
		std::cin>>arr[i];
	//i를 1~n까지의 정수로 정의했을 때, arr[i]를 마지막으로 하는 가장 긴 부분수열 구하기 
	most_long(arr, n);
	//최댓값 찾아 출력 
	int max=dp[1];
	for(int i=2; i<=n; i++)
		max = std::max(max, dp[i]);
	
	std::cout<<max;
		
	return 0;
}

void most_long(int arr[], int n)
{	
	for(int i=1; i<=n; i++)
	{
		for(int l=1; l<=i-1; l++)
			if(arr[l]<arr[i])
				dp[i] = std::max(dp[i], dp[l]);
				
		dp[i]++;
	}
}