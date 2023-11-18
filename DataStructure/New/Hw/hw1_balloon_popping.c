#include <stdio.h>
#include <stdlib.h>
int main(){
	int n, h;
	scanf("%d %d", &n, &h);
	int *balloons=(int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++){
		scanf("%d", &balloons[i]);
	}

	int maxcnt=0;
	int maxtmp=0;
	for(int foot=0;foot<n;foot++){
		int head=balloons[foot]+h;
		int lastone=head;
		while(balloons[lastone]<=h+balloons[foot])	lastone++;
		maxtmp=lastone-foot;
		maxcnt=(maxtmp>maxcnt)?maxcnt:maxtmp;
	}

	free(balloons);
	return 0;
}

