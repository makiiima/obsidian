#include <stdio.h>
#include<time.h>
#include<math.h>
#define CLK_TCK 1000
clock_t start, stop;
double duration1, duration2, duration3;
double f1(int n, double x);
double f2(int n, double x);
double f3(int n, double x);
void time(int N, int k);
int main() {
	int N, k;//N is the pow of x，k is the number of repeating
	printf("Plese input N and k:");
	scanf("%d %d", &N, &k);
	time(N, k);
	return 0;
}
double f1(int n, double x) { 
	double p = 1;
	for (int i = 0; i < n; i++)
		p *= x;
	return p;
}
double f2(int n, double x) { 
	if (n == 0)//if n==0 return 1, the initialization
		return 1;
	if (n % 2 == 0 && n > 1)//if n is even return f(n/2,x^2)
		return f2(n / 2, x * x);
	else//if n is odd return f((n-1)/2,x^2)*x
		return f2((n - 1) / 2, x * x) * x;
}

double f3(int n, double x) { //The recursive algorithm, where you get n down to 0 in half, you can't just multiply x by x in half, you can square x in half
	double p = 1;
	for (; n > 0;) {
		if (n % 2 == 1)
			p *= x;
		x *= x;
		n /= 2;
	}
	return p;
}
void time(int N, int k) {//For convenience, the statistics time is treated as a function, and only the power N and the number of runs k need to be entered at each call
    printf("%lf\n", f1(N, 1.0001));//To check if the result of f1 is right
	printf("%lf\n", f2(N, 1.0001));//To check if the result of f2 is right
	printf("%lf\n", f3(N, 1.0001));//To check if the result of f3 is right. Check the three against each other to see if the procedure is wrong
	start = clock();
	for (int i = 0; i < k; i++)//cycle f1 k times
		f1(N, 1.0001);
	stop = clock();
	duration1 = ((double)(stop - start)) / CLK_TCK;//computing the time of cycling
	start = clock();
	for (int i = 0; i < k; i++)//cycle f2 k times 
		f2(N, 1.0001);
	stop = clock();
	duration2 = ((double)(stop - start)) / CLK_TCK;//computing the time of cycling
	start = clock();
	for (int i = 0; i < k; i++)//cycle f3 k times
		f3(N, 1.0001);
	stop = clock();
	duration3 = ((double)(stop - start)) / CLK_TCK;//computing f3 k times
	printf("duration1=%.30lf\nduration2=%.30lf\nduration3=%.30lf\n", duration1, duration2, duration3);//Show the time costs of the three functions
}
