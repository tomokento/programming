/*#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

//void sort(int* num,int n);

int main(){
  int n;//, num[10000];
  int a,min,max;
  long long sum;
  scanf("%d",&n);
  scanf("%d",&a);
  min=max=sum=a;
  for(int i=0;i<n;i++){
      scanf("%d",&a);
      if(min > a) min=a;
      if(max < a) max = a;
      sum+=a;
  }
  printf("%d %d %lld\n",min,max,sum);
  return 0;
}*/
// ITP1_4_D:   Min, Max and Sum
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
	int n;
	int d, min, max;
	long long sum;

	scanf("%d%d", &n, &d);
	sum = min = max = d;
  //ここのループの差で不正がわかれた。
	while (--n > 0) {
		scanf("%d", &d);
		if (d < min) min = d;
		if (d > max) max = d;
		sum += d;
	}
	printf("%d %d %lld\n", min, max, sum);
	return 0;
}
