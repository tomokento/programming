#include  <stdio.h>

  int main(){
    int w,h,x,y,r;

    scanf("%d %d %d %d %d",&w,&h,&x,&y,&r);

   int y_u,y_h,x_r,x_l;
   y_u = y-r;
   y_h = y+r;
   x_r = x+r;
   x_l = x-r;

   if(y_u >= 0 && y_h <= h && x_l >= 0 && x_r <= w)
   printf("Yes\n");

   else printf("No\n");
   return 0;
  }
