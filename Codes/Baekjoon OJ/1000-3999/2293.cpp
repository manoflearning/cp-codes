#include <iostream>
#include <algorithm>

int dp[10001];

int main()
{		
	int n, k;
	scanf("%d %d", &n, &k);
	int voc[n+1]; //value of coins
	for(int i=1; i<=n; i++)
		scanf("%d", &voc[i]);
	
	std::sort(voc+1, voc+n+1);
		
	dp[0] = 1;
	for(int i=1; i<=n; i++)
	{
		for(int l=1; l<=k; l++)
		{
			if(l-voc[i] >= 0)
				dp[l] += dp[l-voc[i]];
		}
	}
	
	printf("%d", dp[k]);
	
	return 0;
}
