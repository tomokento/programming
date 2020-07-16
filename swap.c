#include <stdio.h>

int main(){
  int x,y;

  while(1){
    scanf("%d %d",&x,&y);
    if(x == 0 && y == 0)break;
    else if(x > y){
      int emp = 0;
      emp = x;
      x = y;
      y = emp;
    }
    printf("%d %d\n",x,y);
  }

}
