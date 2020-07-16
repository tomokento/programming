#include <stdio.h>
void sort(int* num,int n);

int main(){
  int n,num[10000];

  scanf("%d",&n);
  for(int i = 0;i < n;i++){
  scanf("%d",&num[i]);
  }
  //for(int i=0;i<n;i++){
  //printf("%d ",num[i]);
  //}
  //printf("\n");
  sort(num,n);

  int sum=0;
  for(int j = 0;j<n;j++){
    sum += num[j];
  }
  printf("%d %d %d\n",num[0],num[n-1],sum);
  //for(int i=0;i<n;i++){
  //printf("%d ",num[i]);
//}
}

void sort(int *num,int n){
  int v,i,j;
  for(i=1;i < n;i++){
    v = num[i];
    j = i - 1;
      while(j >= 0 && num[j] > v){
        num[j+1] = num[j];
        j--;
      }

      /*for(j = i -1;j>=0;j--){
        if(num[j] > v){
          num[j+1] = num[j];
        }
        */

    num[j+1] = v;
  }
}
