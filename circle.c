#include <stdio.h>
#define pi 3.141592653589
//使う実数の値は、定数の場合はちゃんとしたものを入れて行うこと。

int main(){
  double r;
  double s,c;

  scanf("%lf",&r);

  s = (double)r*r*pi;
  c = (double)2*r*pi;
  printf("%f %f\n",s,c);

  /*int FILE *fp;
  fp = fopen ("filename.txt","r");
  if (fp!=NULL)
  {
    fscanf(fp,"Some String\n", &var);
    fclose (fp);
  }*/
}
