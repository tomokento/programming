#include <stdio.h>

int main(){

  int a,b,c;
  int cnt=0;
  scanf("%d %d %d",&a,&b,&c);

  for(int i = a; i <= b; i++){
    int ans;
    ans = c % i;
    if(ans == 0){
      cnt++;
    }
  }
  printf("%d\n",cnt);

}
