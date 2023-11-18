#include <stdio.h>
#include <stdlib.h>
int main()
{
	// input data
	int n, h;
	scanf("%d %d", &n, &h);
	int *balloons = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &balloons[i]);
	}

	int maxCount = 0;
	int bestPositon = 0;
	int smallestBestPosition=0;
	// start from balloons[0] to balloons[n]
	for (int i = 0; i < n; i++)
	{
		int headPositon = balloons[i] + h;
		int lastBalloon = i;
		while (lastBalloon < n && balloons[lastBalloon] <= headPositon)
			lastBalloon++;
		int count = lastBalloon - i;
		//update maximum count and best position
		if (count > maxCount)
		{
			maxCount = count;
			bestPositon = i;
			smallestBestPosition=balloons[bestPositon];

			//adjust to find the smallest position to satisfy the conditions
			while(smallestBestPosition+h>balloons[bestPositon+i])
			{
				smallestBestPosition--;
			}
				
			
		}
	}
	
	

	printf("%d %d", smallestBestPosition, maxCount);

	free(balloons);
	return 0;
}
